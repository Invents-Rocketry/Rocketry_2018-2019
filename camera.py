from picamera import PiCamera
from time import sleep
import datetime

camera = PiCamera()

while(1)
    filename = '/home/pi/'
    filename = filename + str(datetime.datetime.now()) + '.h264'
    camera.start_recording(filename)
    sleep(10)
camera.stop_preview()
