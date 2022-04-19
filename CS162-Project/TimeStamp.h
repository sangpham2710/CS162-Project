#pragma once

#include <ctime>
#include <iostream>

using std::tm;

class TimeStamp {
 private:
  tm _tm;

 public:
  TimeStamp() : _tm{0, 0, 0, 1, 0, 100, 0, 0, 0} {}  // 00:00  01/Jan/2000

  void output();

  friend std::istream& operator>>(std::istream& stream, TimeStamp& timeStamp);
  friend std::ostream& operator<<(std::ostream& stream,
                                  const TimeStamp& timeStamp);
  // getters
  int getSeconds() const;
  int getMinutes() const;
  int getHours() const;
  int getDay() const;
  int getMonth() const;
  int getYear() const;
  // setters
  TimeStamp& setSeconds(int x);
  TimeStamp& setMinutes(int x);
  TimeStamp& setHours(int x);
  TimeStamp& setDay(int x);
  TimeStamp& setMonth(int x);
  TimeStamp& setYear(int x);


  static TimeStamp now();
  bool inRange(TimeStamp start, TimeStamp end);
};