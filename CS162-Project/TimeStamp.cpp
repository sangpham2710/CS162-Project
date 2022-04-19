#include "TimeStamp.h"

#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std::chrono;
using std::cout;

std::istream& operator>>(std::istream& stream, TimeStamp& timeStamp) {
  int seconds, minutes, hours, day, month, year;
  stream >> seconds;
  stream >> minutes;
  stream >> hours;
  stream >> day;
  stream >> month;
  stream >> year;
  timeStamp.setSeconds(seconds)
      .setMinutes(minutes)
      .setHours(hours)
      .setDay(day)
      .setMonth(month)
      .setYear(year);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const TimeStamp& timeStamp) {
  stream << timeStamp.getSeconds() << '\n';
  stream << timeStamp.getMinutes() << '\n';
  stream << timeStamp.getHours() << '\n';
  stream << timeStamp.getDay() << '\n';
  stream << timeStamp.getMonth() << '\n';
  stream << timeStamp.getYear() << '\n';
  return stream;
}


int TimeStamp::getSeconds() const {
  return this->_tm.tm_sec;
}
int TimeStamp::getMinutes() const {
  return this->_tm.tm_min;
}
int TimeStamp::getHours() const {
  return this->_tm.tm_hour;
}
int TimeStamp::getDay() const {
  return this->_tm.tm_mday;
}
int TimeStamp::getMonth() const {
  return this->_tm.tm_mon + 1;
}
int TimeStamp::getYear() const {
  return this->_tm.tm_year + 1900;
}
TimeStamp& TimeStamp::setSeconds(int x) {
  if (x < 0 || x > 59) return *this;
  this->_tm.tm_sec = x;
  return *this;
}
TimeStamp& TimeStamp::setMinutes(int x) {
  if (x < 0 || x > 59) return *this;
  this->_tm.tm_min = x;
  return *this;
}
TimeStamp& TimeStamp::setHours(int x) {
  if (x < 0 || x > 23) return *this;
  this->_tm.tm_hour = x;
  return *this;
}
TimeStamp& TimeStamp::setDay(int x) {
  if (x < 1 || x > 31) return *this;
  this->_tm.tm_mday = x;
  return *this;
}
TimeStamp& TimeStamp::setMonth(int x) {
  if (x < 1 || x > 12) return *this;
  this->_tm.tm_mon = x - 1;
  return *this;
}
TimeStamp& TimeStamp::setYear(int x) {
  if (x < 0) return *this;
  this->_tm.tm_year = x - 1900;
  return *this;
}

void TimeStamp::output() {
  time_t tt = mktime(&this->_tm);
  cout << std::put_time(localtime(&tt), "%H:%M  %d/%h/%Y");
}

TimeStamp TimeStamp::now() {
  time_t tt = system_clock::to_time_t(system_clock::now());
  TimeStamp res;
  res._tm = *localtime(&tt);
  return res;
}

bool TimeStamp::inRange(TimeStamp start, TimeStamp end) {
  time_t startTime = mktime(&start._tm);
  time_t endTime = mktime(&end._tm);
  time_t curTime = mktime(&this->_tm);
  if (startTime == -1 || endTime == -1 || startTime >= endTime) return false;
  return startTime <= curTime && curTime <= endTime;
}