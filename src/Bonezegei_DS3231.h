/*
  This Library is written for DS3231 RTC
  Author: Bonezegei (Jofel Batutay)
  Date: Jan 26 2024
*/

#ifndef _BONEZEGEI_DS3231_H_
#define _BONEZEGEI_DS3231_H_
#include <Arduino.h>
#include <Wire.h>

class Bonezegei_DS3231{
public:
  Bonezegei_DS3231();
  Bonezegei_DS3231(uint8_t addr);

  uint8_t _addr;
};

#endif
