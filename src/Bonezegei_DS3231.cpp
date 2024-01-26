/*
  This Library is written for DS3231 RTC
  Author: Bonezegei (Jofel Batutay)
  Date: Jan 26 2024
*/

#include "Bonezegei_DS3231.h"

Bonezegei_DS3231::Bonezegei_DS3231() {
}

Bonezegei_DS3231::Bonezegei_DS3231(uint8_t addr) {
  _addr = addr;
}

char Bonezegei_DS3231::begin() {
  if (Wire.begin()) {
    return 1;
  } else {
    return 0;
  }
}

char Bonezegei_DS3231::getTime() {
  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.endTransmission();

  int a = 0;
  int r = Wire.requestFrom(_addr, 13);
  while (Wire.available()) {
    _data[a] = Wire.read();
    a++;
  }

  //time
  _seconds = _data[0] & 0x7F; //0 - 60 seconds
  _minutes = _data[1] & 0x7F; //0 - 60 minutes
  _hour = _data[2] & 0x1F;

  //date
  _day = _data[3];          // 1-7  day of week
  _date = _data[4;          // 1-31 date 
  _month = _data[5] &0x3f;  // 1- 12 month
  _year = _data[6];         // 0- 99 year

  return r;
}
