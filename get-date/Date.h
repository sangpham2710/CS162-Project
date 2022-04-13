#pragma once
#include <ctime>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Date {
 public:
  tm Time;
  Date()
      : Time{0, 0, 0, 1, 0, 100, 0, 0, 0} {}  // Default date: 1/1/2000 at 00:00

  void saveToFile();
  void loadFromFile();
  void getCurrentTime();
  void printDate();
  void getDay();
  void getMonth();
  void getYear();
  bool compareDate(Date startDate, Date endDate);
};