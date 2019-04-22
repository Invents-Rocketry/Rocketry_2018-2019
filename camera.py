from picamera import PiCamera
from time import sleep

camera = PiCamera()

#camera.rotation = 180 #use if the view is wrong
camera.start_preview()
sleep(2) #sleep for at least 2 seconds before capturing, to give the sensor time to set its light levels.
camera.start_recording('/home/pi/video.h264')
sleep(10)
camera.stop_recording()
camera.stop_preview()
