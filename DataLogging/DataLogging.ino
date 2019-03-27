#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_9DOF.h>
#include <Adafruit_L3GD20_U.h>
#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library

//Setting up ID's for sensors
#include "Wire.h"    // imports the wire library for talking over I2C
//Adafruit_9DOF                 dof   = Adafruit_9DOF();
//Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
//Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);
//Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);


long interval = 20;
long previousmillis= 0;
File mySensorData;

void initSensors() {
  
  if(!bmp.begin()){
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
    
  }
}


void setup(){

  
  Serial.begin(9600); //I need help for choosing this correctly
  sensors_event_t event;
  //gyro.enableAutoRange(true); /* Enable auto-ranging */
  initSensors();  /* Initialise the sensors */

  if (!SD.begin(10))     // if you're using an UNO, you can use this line instead
      Serial.println("Card init. failed!"); /*initialize SD card dreader*/

 
 
  mySensorData = SD.open("DataLog.csv", FILE_WRITE);
  mySensorData.print("Temperature(C),Pressure(hPa),Altitude(m),Roll(deg)","Pitch(deg),Heading(deg)");
  mySensorData.println();

  mySensorData.close();

  
  
}
void loop(){


        unsigned long currentmillis = millis();
        if(currentmillis - previousmillis > interval){
              previousmillis = currentmillis;
              //Setting up sensor events
              //sensors_event_t accel_event; //For accelerometer
              //sensors_event_t mag_event; //For magnetometer
              //sensors_vec_t   orientation; //for orientation
              sensors_event_t event;  //For pressure and temperature
              //accel.getEvent(&accel_event);
              //mag.getEvent(&mag_event);
              bmp.getEvent(&event);  
              
              float temperature;
              bmp.getTemperature(&temperature);
            
              
              float seaLevelPressure = 1017.6099;
              float Altitude = bmp.pressureToAltitude(seaLevelPressure,event.pressure);
        
              if(mySensorData){
                    mySensorData = SD.open("DataLog.csv", FILE_WRITE);
                    mySensorData.print(temperature);                        
                    mySensorData.print(",");                                    
                    mySensorData.print(event.pressure);              
                    mySensorData.print(","); 
                      
                    mySensorData.print(Altitude);                             
                    mySensorData.print(",");  

                    Serial.print(Altitude);
                   /*
                   if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
                   {
                      float roll = orientation.roll;
                      float pitch = orientation.pitch;
                      float heading = orientation.heading;
                      
                      mySensorData.print(roll);                             
                      mySensorData.print(",");  
                      mySensorData.print(pitch);                             
                      mySensorData.print(",");  
                      mySensorData.print(heading);                             
               
                   }
                  */
              }
              
        }
        mySensorData.println();
       mySensorData.close();
}
