#include <WProgram.h>
#include <Wire.h>
#include <DS1307.h> 
#include "RTClib.h"

RTC_DS1307 rtc;

void setup()
{
  Serial.begin(9600);
  RTC.stop();
  RTC.set(DS1307_SEC,1);        //set the seconds
  RTC.set(DS1307_MIN,20);     //set the minutes
  RTC.set(DS1307_HR,17);       //set the hours
  RTC.set(DS1307_DOW,4);       //set the day of the week
  RTC.set(DS1307_DATE,1);       //set the date
  RTC.set(DS1307_MTH,6);        //set the month
  RTC.set(DS1307_YR,12);         //set the year
  RTC.start();
  //pinMode(10,OUTPUT);
  
  
}
void loop()
{
  
  Serial.print(RTC.get(DS1307_HR,true)); //read the hour and also update all the values by pushing in true
  Serial.print(":");
  Serial.print(RTC.get(DS1307_MIN,false));//read minutes without update (false)
  Serial.print(":");
  Serial.print(RTC.get(DS1307_SEC,false));//read seconds
  Serial.print("      ");                 // some space for a more happy life
  Serial.print(RTC.get(DS1307_DATE,false));//read date
  Serial.print("/");
  Serial.print(RTC.get(DS1307_MTH,false));//read month
  Serial.print("/");
  Serial.print(RTC.get(DS1307_YR,false)); //read year
  Serial.println();
  delay(1000);
  
}
