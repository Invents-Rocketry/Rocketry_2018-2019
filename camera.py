from picamera import PiCamera
import time

camera = PiCamera()
while(1):
    name = str(time.time())
    video = '/home/pi/video' + name + '.h264'
    #camera.rotation = 180 #use if the view is wrong

    time.sleep(2) #sleep for at least 2 seconds before capturing, to give the sensor time to set its light levels.
    camera.start_recording(video)
    time.sleep(300)
    camera.stop_recording()

