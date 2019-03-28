#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

void setup() {

  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);
  uint16_t pulselen = map(0, 0, 180, SERVOMIN, SERVOMAX)

  pwm.setPWM(0, 0, pulselen);
  pwm.setPWM(1, 0, pulselen);
  pwm.setPWM(2, 0, pulselen);
  delay(10);
  
}

void loop() {
  
  uint16_t pulselen = map(0, 0, 180, SERVOMIN, SERVOMAX);
  uint16_t alt = 1;
  if(1000 < alt && alt < 6000) {
    
  }

}
