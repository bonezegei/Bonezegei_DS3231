/*
  Set Time And Date
  Author: Bonezegei (Jofel Batutay)
  Date: Jan 26 2024
*/

#include <Bonezegei_DS3231.h>

Bonezegei_DS3231 rtc(0x68);

void setup() {
  Serial.begin(115200);
  rtc.begin();
  rtc.setFormat(12);        //Set 12 Hours Format
  rtc.setAMPM(1);           //Set AM or PM    0 = AM  1 =PM
  rtc.setTime("11:59:30");  //Set Time    Hour:Minute:Seconds
  rtc.setDate("1/27/24");   //Set Date    Month/Date/Year
}

void loop() {
  char d[32];
  if (rtc.getTime()) {
    //Serial.printf("Time %02d:%02d:%02d ", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
    sprintf(d, "Time %02d:%02d:%02d ", rtc.getHour(), rtc.getMinute(), rtc.getSeconds());
    Serial.print(d);

    if (rtc.getFormat() == 12) {  // returns 12 or 24 hour format

      if (rtc.getAMPM()) {  //return 0 = AM  1 = PM
        Serial.print("PM  ");
      } else {
        Serial.print("AM  ");
      }
    }

    //Serial.printf("Date %02d-%02d-%d \n", rtc.getMonth(), rtc.getDate(), rtc.getYear());
    sprintf(d, "Date %02d-%02d-%d \n", rtc.getMonth(), rtc.getDate(), rtc.getYear());
    Serial.print(d);
  }

  delay(1000);
}
