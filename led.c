#include <stdio.h>
#include <stdlib.h>
#include <iolib.c>

int led = 12;
int gyro = 1;
iolib_init();
iolib_setdir(8, l2, DIR_OUT);

while(gyro > 0) {

  pin_high(8, led);

}
while(gyro < 0) {

  pin_high(8, led);

}
if(gyro == 0) {

  pin_low(8, led);

}

iolib_free();
