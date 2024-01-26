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

uint8_t Bonezegei_DS3231::convert(uint8_t data) {
  uint8_t result = data & 0x0f;
  result += ((data & 0xf0) >> 4) * 10;
  return result;
}

char Bonezegei_DS3231::getTime() {
  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.endTransmission();

  int a = 0;
  int r = (uint8_t)Wire.requestFrom((int)_addr, 13);
  while (Wire.available()) {
    _data[a] = Wire.read();
    a++;
  }

  //time
  _seconds = convert(_data[0]);  //0 - 60 seconds
  _minutes = convert(_data[1]);  //0 - 60 minutes
  _hour =  convert(_data[2] & 0x1F);

  //date
  _day = _data[3];           // 1-7  day of week
  _date = _data[4];          // 1-31 date
  _month = _data[5] & 0x3f;  // 1- 12 month
  _year = _data[6];          // 0- 99 year

  return r;
}

uint8_t Bonezegei_DS3231::getSeconds() {
  return _seconds;
}

uint8_t Bonezegei_DS3231::getMinute() {
  return _minutes;
}

uint8_t Bonezegei_DS3231::getHour() {
  return _hour;
}

uint8_t Bonezegei_DS3231::getDay() {
  return _day;
}

uint8_t Bonezegei_DS3231::getDate() {
  return _date;
}

uint8_t Bonezegei_DS3231::getMonth() {
  return _month;
}

uint8_t Bonezegei_DS3231::getYear() {
  return _year;
}
