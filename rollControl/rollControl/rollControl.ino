#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Servo.h>
#include <SD.h>
#include<SPI.h>
#include <SimpleTimer.h>
#include <TimedAction.h>

#define SERVOMIN 150
#define SERVOMAX 600
   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
SimpleTimer timer = SimpleTimer();
int ledOne = 10;
int ledTwo = 11;
long interval = 20;
long previousmillis= 0;
File mySensorData;
Servo myservo;

void initSensors() {
  
  if(!bmp.begin()){
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
    
  }
}

void setup(void) 
{
  Serial.begin(9600);
  initSensors();
  timer.setTimeout(3500, rollOnce);
  pinMode(ledOne,OUTPUT);
  pinMode(ledTwo,OUTPUT);
  myservo.attach(17);
  if (!SD.begin(10))     // if you're using an UNO, you can use this line instead
      Serial.println("Card init. failed!"); /*initialize SD card dreader*/
  mySensorData = SD.open("DataLog.csv", FILE_WRITE);
  mySensorData.print("Temperature(C),Pressure(hPa),Altitude(m),Roll(deg),Pitch(deg),Heading(deg)");
  mySensorData.println();
  mySensorData.close();
  
}

/*
 * This code will run as often as possible and will log any data from the sensors
 */
void dataLog() {

  unsigned long currentmillis = millis();
  if(currentmillis - previousmillis > interval){
        previousmillis = currentmillis;
        //Setting up sensor events
        sensors_event_t event;  //For pressure and temperature
        bmp.getEvent(&event);  
        float temperature;
        bmp.getTemperature(&temperature);
        float seaLevelPressure = 1014.223;
        float Altitude = bmp.pressureToAltitude(seaLevelPressure,event.pressure);
        if(mySensorData){
              mySensorData = SD.open("DataLog.csv", FILE_WRITE);
              mySensorData.print(temperature);                        
              mySensorData.print(",");                                    
              mySensorData.print(event.pressure);              
              mySensorData.print(","); 
              mySensorData.print(Altitude);                             
              mySensorData.print(",");  

        }
        
  }
  mySensorData.println();
  mySensorData.close();  

}

TimedAction dataLogThread = TimedAction(10, dataLog);

/*
 * This function will roll the rocket as specified one time.
 */
void rollOnce() {

  //ledOne indicates clockwise
  //ledTwo indicates counterclockwise
  unsigned long currentmillis = millis();
  //Command 1
  myservo.write(75);
  digitalWrite(ledOne, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 255) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledOne, LOW);
  dataLogThread.check();
  myservo.write(100);
  digitalWrite(ledTwo, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 255) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledTwo, LOW);
  myservo.write(90);
  while(currentmillis - previousmillis < 1000) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  //Command 2
  myservo.write(100);
  digitalWrite(ledTwo, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 223) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledTwo, LOW);
  dataLogThread.check();
  myservo.write(75);
  digitalWrite(ledOne, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 223) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledOne, LOW);
  myservo.write(90);
  while(currentmillis - previousmillis < 1000) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  //Command 3
  myservo.write(100);
  digitalWrite(ledTwo, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 399) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledTwo, LOW);
  dataLogThread.check();
  myservo.write(75);
  digitalWrite(ledOne, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 399) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledOne, LOW);
  myservo.write(90);
  while(currentmillis - previousmillis < 1000) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  //Command 4
  myservo.write(75);
  digitalWrite(ledOne, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 394) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledOne, LOW);
  dataLogThread.check();
  myservo.write(100);
  digitalWrite(ledTwo, HIGH);
  dataLogThread.check();
  while(currentmillis - previousmillis < 394) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
  digitalWrite(ledTwo, LOW);
  myservo.write(90);
  while(currentmillis - previousmillis < 1000) {
    currentmillis = millis();
    dataLogThread.check();
  }
  previousmillis = currentmillis;
}

void loop(void) 
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
  unsigned long currentmillis = millis();
  /* 1005.0802552 at Kentland Farms, if unable to get actual pressure 
   *  SENSORS_PRESSURE_SEALEVELHPA as a default (inaccurate)
  */
  float seaLevelPressure = 1014.223;
  uint16_t alt = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
  bool altChange = false;
  dataLogThread.check();
  while(!altChange) {
    uint16_t initAlt = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
    while(currentmillis - previousmillis < 1000) {
      currentmillis = millis();
      dataLogThread.check();
    }
    previousmillis = currentmillis;
    uint16_t finalAlt = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
    uint16_t changeAlt = finalAlt - initAlt;
    if(changeAlt > 15) {
      altChange = true;
      dataLogThread.check();
      timer.run();
      dataLogThread.check();
    }
  } //check if change is at least 15 m/s
  dataLogThread.check();
}





