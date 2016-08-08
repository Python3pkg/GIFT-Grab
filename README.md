GiftGrab
--------

GiftGrab provides an easy-to-use Python/C++ API to capture and save video using frame-grabber hardware. It also supports hardware-accelerated video encoding.

GiftGrab was developed as part of the [GIFT-Surg][giftsurg] project at the [Translational Imaging Group][tig] in the [Centre for Medical Image Computing][cmic] at [University College London (UCL)][ucl].

System requirements
-------------------

Required:

* Linux (tested on Ubuntu 14.04 LTS)
* C++11
* [CMake](https://cmake.org/) (tested with 3.2)

Optional (depending on desired features, see "How to use" below):

* [OpenCV](http://www.opencv.org/) (tested with 2.4.12)
* [FFmpeg](https://ffmpeg.org/) (tested with 3.0.1)
* [NVENC](https://developer.nvidia.com/nvidia-video-codec-sdk) (tested with 6.0.1)
* [A GPU supporting NVENC](https://developer.nvidia.com/nvidia-video-codec-sdk)
* [x265](http://x265.org/)
* EpiphanSDK
* [Python](https://www.python.org/) (tested with 2.7)
* [Boost.Python](http://www.boost.org/doc/libs/release/libs/python/)
* [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)

Please note that there are cross-dependencies between some of these external libraries. Check out [our tips and tricks](doc/tips.md) for details.

Supported hardware
------------------

* [Epiphan DVI2PCIe Duo](http://www.epiphan.com/products/dvi2pcie-duo/)

Supported video formats
-----------------------

* [XviD](https://www.xvid.com/) (saved as [AVI](https://msdn.microsoft.com/en-us/library/windows/desktop/dd318189(v=vs.85).aspx))
* [HEVC/H.265](http://www.itu.int/ITU-T/recommendations/rec.aspx?rec=11885) (saved as [MP4](http://www.iso.org/iso/catalogue_detail.htm?csnumber=38538))

How to use
----------

Build GiftGrab from source using CMake. Check out [our tips and tricks](doc/tips.md) for troubleshooting and how to obtain the external dependencies.

Customise GiftGrab with the following options as desired:

* `-D USE_EPIPHAN_DVI2PCIE_DUO=ON` for Epiphan DVI2PCIe Duo support (requires OpenCV). Append `-D USE_I420=ON` to capture at 60 fps (requires EpiphanSDK).
* `-D USE_XVID=ON` for Xvid support (requires OpenCV).
* `-D USE_H265=ON` for H.265 (HEVC) support (requires FFmpeg, pkg-config and x265).
* `-D USE_H265=ON -D USE_NVENC=ON` for hardware-accelerated H.265 support (requires a supported GPU, FFmpeg, pkg-config and NVENC).
* `-D BUILD_PYTHON=ON` for GiftGrab Python API (requires Python and Boost.Python).

To use GiftGrab in your software projects: use `FIND_PACKAGE(GiftGrab)` in your CMake file to discover the `GiftGrab_INCLUDE_DIRS` and `GiftGrab_LIBS` CMake variables (respectively for GiftGrab headers to include and GiftGrab libraries to link against).

How to test
-----------

To quickly see whether GiftGrab works on your system, turn on tests with `-D BUILD_TESTS=ON` (requires Python and Boost.Python). Then run `ctest` or `make test` in the build directory.

Funding
-------

This work was supported through an Innovative Engineering for Health award by the [Wellcome Trust][wellcometrust] [WT101957], the [Engineering and Physical Sciences Research Council (EPSRC)][epsrc] [NS/A000027/1] and a [National Institute for Health Research][nihr] Biomedical Research Centre [UCLH][uclh]/UCL High Impact Initiative.


[tig]: http://cmictig.cs.ucl.ac.uk
[giftsurg]: http://www.gift-surg.ac.uk
[cmic]: http://cmic.cs.ucl.ac.uk
[ucl]: http://www.ucl.ac.uk
[nihr]: http://www.nihr.ac.uk/research
[uclh]: http://www.uclh.nhs.uk
[epsrc]: http://www.epsrc.ac.uk
[wellcometrust]: http://www.wellcome.ac.uk