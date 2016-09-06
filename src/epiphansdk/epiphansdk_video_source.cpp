#include "epiphansdk_video_source.h"
#include <iostream>

namespace gg
{

VideoSourceEpiphanSDK::VideoSourceEpiphanSDK(
    const std::string device_id, V2U_INT32 colour_space)
    : IVideoSource(),
      _frame_grabber(nullptr),
      _flags(0)
{
    FrmGrab_Init();

    _frame_grabber = FrmGrabLocal_OpenSN(device_id.c_str());
    if (not _frame_grabber)
    {
        // TODO - exception GiftGrab#42
        std::cerr << "Could not open " << device_id << std::endl;
        return;
    }

    if (colour_space != V2U_GRABFRAME_FORMAT_I420 and colour_space != V2U_GRABFRAME_FORMAT_BGR24)
    {
        // TODO - exception GiftGrab#42
        std::cerr << "Colour space " << colour_space << " not supported" << std::endl;
        return;
    }
    _flags |= colour_space;

    VideoFrame_I420 frame;
    _full.x = 0;
    _full.y = 0;
    /* TODO - e.g. EpiphanSDK_MAX_RES_X and
     * EpiphanSDK_MAX_RES_Y after
     * EpiphanSDK#6
     */
    _full.width = 1920;
    _full.height = 1080;
    get_full_frame();
    // TODO - exception GiftGrab#42
    if (not get_frame(frame)) return;
}

VideoSourceEpiphanSDK::~VideoSourceEpiphanSDK()
{
    if (_frame_grabber) FrmGrab_Close(_frame_grabber);
    FrmGrab_Deinit();
}

bool VideoSourceEpiphanSDK::get_frame_dimensions(int & width, int & height)
{
    width = _roi.width;
    height = _roi.height;
    return true;
}

bool VideoSourceEpiphanSDK::get_frame(VideoFrame_BGRA & frame)
{
    // TODO - exception GiftGrab#42
    return false;
}

bool VideoSourceEpiphanSDK::get_frame(VideoFrame_I420 & frame)
{
    _buffer = FrmGrab_Frame(_frame_grabber, _flags, &_roi);
    if (_buffer)
    {
        frame = VideoFrame_I420(
                    static_cast<unsigned char*>(_buffer->pixbuf),
                    _buffer->imagelen,
                    /* TODO #54 specified _roi not always
                     * respected by FrmGrab_Frame, hence
                     * constructing with _buffer->crop
                     * instead of _roi to avoid alignment
                     * problems when saving to video files
                     */
                    _buffer->crop.width, _buffer->crop.height,
                    false
                    );
        FrmGrab_Release(_frame_grabber, _buffer);
        return true;
    }
    else
        return false;
}

double VideoSourceEpiphanSDK::get_frame_rate()
{
    if (_frame_grabber)
    {
#if defined(EpiphanSDK_DVI) and \
    defined(EpiphanSDK_SDI) and \
    defined(EpiphanSDK_DVI_MAX_FRAME_RATE) and \
    defined(EpiphanSDK_SDI_MAX_FRAME_RATE)
        std::string port_id = FrmGrab_GetId(_frame_grabber);
        if (port_id == EpiphanSDK_DVI)
            return EpiphanSDK_DVI_MAX_FRAME_RATE;
        else if (port_id == EpiphanSDK_SDI)
            return EpiphanSDK_SDI_MAX_FRAME_RATE;
#endif
    }

    // TODO - exception GiftGrab#42
    return 0;
}

void VideoSourceEpiphanSDK::set_sub_frame(int x, int y, int width, int height)
{
    if (x >= _full.x and x + width <= _full.x + _full.width and
        y >= _full.y and y + height <= _full.y + _full.height)
    {
        _roi.x = x;
        _roi.y = y;
        _roi.width = width;
        _roi.height = height;
    }
    // TODO - exception GiftGrab#42
//    else
//        throw VideoSourceError("ROI " + std::to_string(x) + ", " +
//                               std::to_string(y) + ", " +
//                               std::to_string(width) + ", " +
//                               std::to_string(height) + ", " +
//                               "not within full frame");
}

void VideoSourceEpiphanSDK::get_full_frame()
{
    _roi.x = _full.x;
    _roi.y = _full.y;
    _roi.width = _full.width;
    _roi.height = _full.height;
}

}
