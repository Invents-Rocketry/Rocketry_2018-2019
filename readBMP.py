#!/usr/bin/python3
# Copyright (c) 2014 Adafruit Industries
# Author: Tony DiCola
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Can enable debug output by uncommenting:
#import logging
#logging.basicConfig(level=logging.DEBUG)

import Adafruit_BMP.BMP085 as BMP085

import time
import logging
import sys

from Adafruit_BNO055 import BNO055


# Default constructor will pick a default I2C bus.
#
# For the Raspberry Pi this means you should hook up to the only exposed I2C bus
# from the main GPIO header and the library will figure out the bus number based
# on the Pi's revision.
sensor = BMP085.BMP085()

# Optionally you can override the bus number:
#sensor = BMP085.BMP085(busnum=2)


# Create and configure the BNO sensor connection.  Make sure only ONE of the
# below 'bno = ...' lines is uncommented:
# Raspberry Pi configuration with serial UART and RST connected to GPIO 18:
bno = BNO055.BNO055(serial_port='/dev/serial0', rst=18)

# Enable verbose debug logging if -v is passed as a parameter.
if len(sys.argv) == 2 and sys.argv[1].lower() == '-v':
    logging.basicConfig(level=logging.DEBUG)

# Initialize the BNO055 and stop if something went wrong.
if not bno.begin():
    raise RuntimeError('Failed to initialize BNO055! Is the sensor connected?')

# Print BNO055 software revision and other diagnostic data.
sw, bl, accel, mag, gyro = bno.get_revision()



f = open("data.csv","w+")
f.write("Time, Altitude (m), Temperature (C), Pressure (Pa), Velocity (Y), Acceleration (Y), Roll Velocity, Roll Acceleration \n")

ground = sensor.read_altitude()
beginTime = int(round(time.time() * 1000)) 

f.write("{:d},{0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}a\n".format( beginTime, sensor.read_altitude(), sensor.read_temperature(), sensor.read_pressure(),
    0, 0, 0, 0)

#before launch
while(sensor.read_altitude() - ground < 8):


#after launch
prevTime = int(round(time.time() * 1000))
prevAltitude = sensor.read_altitude()

while(sensor.read_altitude() - ground >= 8):

    #linear velocity
    velocity = (sensor.read_altitude() - prevAltitude)/ ( (int(round(time.time() * 1000))) - prevTime)
    prevTime = int(round(time.time() * 1000))
    prevAltitude = sensor.read_altitude()

    #roll velocity
    x,y,z = bno.read_gyroscope()
    velocity_roll = y

    #linear acceleration
    x,y,z = bno.read_linear_acceleration()
    acceleration = y

    #roll acceleration
    acceleration_roll = 180 * atan2(y, sqrt(x*x + z*z))/PI
    
    #record data
    f.write("{:d},{0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}, {0:02f}a\n".format(prevTime, sensor.read_altitude(), sensor.read_temperature(), sensor.read_pressure(),
    velocity, acceleration, velocity_roll, acceleration_roll)

    f.flush()


f.close()
