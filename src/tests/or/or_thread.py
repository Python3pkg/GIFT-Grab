#!/usr/bin/env python

from threading import Thread
from time import sleep, time
import pygiftgrab


class ORThread(Thread):
    def __init__(self, port, frame_rate, file_path):
        print 'init'
        self.port = port
        # TODO - exception
        self.file = pygiftgrab.Factory.writer(pygiftgrab.Storage.File_H265)
        # TODO - filename health checks
        self.file_path = file_path
        self.recording_index = 0
        # TODO - frame_rate health checks
        self.frame_rate = frame_rate
        self.is_running = True
        self.is_recording = False
        Thread.__init__(self)

    def run(self):
        self.is_recording = True
        inter_frame_duration = 1.0 / self.frame_rate # sec
        filename = self.__next_filename()
        print 'filename: ' + filename
        # TODO - exception
        device = pygiftgrab.Factory.connect(self.port)
        frame = pygiftgrab.VideoFrame_BGRA(False)
        self.file.init(filename, self.frame_rate)
        print 'inter-frame duration: ' + str(inter_frame_duration) + ' sec'
        while self.is_running:
            current_processing_start = time()
            # print 'run'
            # TODO
            if self.is_recording:
                # TODO
                device.get_frame(frame)
                self.file.append(frame)
            sleep_duration = inter_frame_duration - (time() - current_processing_start)
            print 'sleeping ' + str(sleep_duration) + ' sec'
            if sleep_duration > 0:
                sleep(sleep_duration)

    def stop(self):
        print 'stop'
        self.pause_recording()
        self.is_running = False
        pygiftgrab.Factory.disconnect(self.port)

    def pause_recording(self):
        # TODO - exception
        self.file.finalise()
        self.is_recording = False

    def resume_recording(self):
        filename = self.__next_filename()
        print 'new filename: ' + filename
        self.file.init(filename, self.frame_rate)
        self.is_recording = True

    def __next_filename(self):
        self.recording_index += 1
        return self.file_path + '-' + '{0:06d}'.format(self.recording_index) + '.mp4'
