/*
  This Library is written for DS3231 RTC
  Author: Bonezegei (Jofel Batutay)
  Date: Jan 26 2024
*/

#ifndef _BONEZEGEI_DS3231_H_
#define _BONEZEGEI_DS3231_H_
#include <Arduino.h>
#include <Wire.h>

class Bonezegei_DS3231 {
public:
  Bonezegei_DS3231();
  Bonezegei_DS3231(uint8_t addr);

  char begin();
  uint8_t convert(uint8_t data);
  uint8_t convertBCD(int data);
  char getTime();

  uint8_t getSeconds();  //return seconds
  uint8_t getMinute();   //return Minute
  uint8_t getHour();     //return Hour
  uint8_t getDay();      //return Day of Week
  uint8_t getDate();     //return Date
  uint8_t getMonth();    //return Month
  uint8_t getYear();     //return Year
  uint8_t getAMPM();     //return 0=AM  1=PM
  uint8_t getFormat();   //return 12 or 24 hour format

  void setFormat(uint8_t fmt);  // set time format 12 or 24
  void setAMPM(uint8_t ampm);   // set AM or PM   PM=1 AM=0
  void setTime(const char *t);  // set time Hour:Minute:Seconds
  void setDate(const char *d);  // set Date Month:Date:Year
  void setDay(uint8_t d);       // set Day of week

private:
  uint8_t _addr;
  uint8_t _data[13];

  uint8_t _minutes;  // 0 - 60 seconds
  uint8_t _seconds;  // 0 - 60 minutes
  uint8_t _hour;     // 1-12 or 0 -23
  uint8_t _ampm;     // 0=AM  1=PM
  uint8_t _hour12;   // 12 or 24  hour format

  uint8_t _day;    // 1-7  day of week
  uint8_t _date;   // 1-31 date
  uint8_t _month;  // 1- 12 month
  uint8_t _year;   // 0- 99 year
};

#endif
