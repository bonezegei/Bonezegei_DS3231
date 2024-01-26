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
  char getTime();

  uint8_t _addr;
  uint8_t _data[13];

  uint8_t _minutes;  //0 - 60 seconds
  uint8_t _seconds;  //0 - 60 minutes
  uint8_t _hour;

  uint8_t _day;     // 1-7  day of week
  uint8_t _date;    // 1-31 date 
  uint8_t _month;   // 1- 12 month
  uint8t_t _year;   // 0- 99 year
};

#endif
