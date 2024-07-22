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
  /*
  if (Wire.begin()) {
    return 1;
  } else {
    return 0;
  }
  */
  Wire.begin();
  return 1;
}

uint8_t Bonezegei_DS3231::convert(uint8_t data) {
  uint8_t result = data & 0x0f;
  result += ((data & 0xf0) >> 4) * 10;
  return result;
}

uint8_t Bonezegei_DS3231::convertBCD(int data) {
  int tmp1;
  if (data > 10) {
    tmp1 = (int)(data / 10);
  } else {
    tmp1 = 0;
  }
  int tmp2 = data - (tmp1 * 10);

  uint8_t result = (tmp1 << 4) | tmp2;

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

  if (_data[2] & 0x40) {
    _hour = convert(_data[2] & 0x1F);
    _ampm = (_data[2] & 0x20) >> 5;
    _hour12 = 12;
  } else {
    _hour = convert(_data[2] & 0x3F);
    _hour12 = 24;
  }

  //date
  _day = _data[3];                    // 1-7  day of week
  _date = convert(_data[4]);          // 1-31 date
  _month = convert(_data[5] & 0x3f);  // 1- 12 month
  _year = convert(_data[6]);          // 0- 99 year

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

uint8_t Bonezegei_DS3231::getAMPM() {
  return _ampm;
}

uint8_t Bonezegei_DS3231::getFormat() {
  return _hour12;
}

void Bonezegei_DS3231::setFormat(uint8_t fmt) {
  getTime();

  if (fmt == 12) {
    _data[2] |= 0x40;
    Wire.beginTransmission(_addr);
    Wire.write(0x02);
    Wire.write(_data[2]);
    Wire.endTransmission();
    _hour12 = 12;
  } else {
    _data[2] &= 0x3f;
    Wire.beginTransmission(_addr);
    Wire.write(0x02);
    Wire.write(_data[2]);
    Wire.endTransmission();
    _hour12 = 24;
  }
}

void Bonezegei_DS3231::setAMPM(uint8_t ampm) {
  getTime();

  if (ampm == 1) {
    _data[2] |= 0x20;
    Wire.beginTransmission(_addr);
    Wire.write(0x02);
    Wire.write(_data[2]);
    Wire.endTransmission();
    _ampm = 1;
  } else {
    _data[2] &= 0x5f;
    Wire.beginTransmission(_addr);
    Wire.write(0x02);
    Wire.write(_data[2]);
    Wire.endTransmission();
    _ampm = 0;
  }
}

void Bonezegei_DS3231::setTime(const char *t) {
  int sec;
  int min;
  int hour;
  sscanf(t, "%d:%d:%d", &hour, &min, &sec);

  _data[0] = convertBCD(sec);
  _data[1] = convertBCD(min);
  _data[2] &= 0x60;
  _data[2] |= convertBCD(hour);

  Wire.beginTransmission(_addr);
  Wire.write(0x00);
  Wire.write(_data[0]);
  Wire.write(_data[1]);
  Wire.write(_data[2]);
  Wire.endTransmission();
}

void Bonezegei_DS3231::setDate(const char *d) {
  int date;
  int mon;
  int year;
  sscanf(d, "%d/%d/%d", &mon, &date, &year);

  _data[4] = convertBCD(date);
  _data[5] &= 0x80;
  _data[5] = convertBCD(mon);
  _data[6] |= convertBCD(year);

  Wire.beginTransmission(_addr);
  Wire.write(0x04);
  Wire.write(_data[4]);
  Wire.write(_data[5]);
  Wire.write(_data[6]);
  Wire.endTransmission();
}

void  Bonezegei_DS3231::setDay(uint8_t d){
  
}
