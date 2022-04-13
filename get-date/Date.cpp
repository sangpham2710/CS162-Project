#include "Date.h"

void Date::printDate() {
  cout << "Date: " << this->Time.tm_mday << "/" << this->Time.tm_mon + 1 << "/"
       << this->Time.tm_year + 1900 << std::endl;
  cout << "Time: " << this->Time.tm_hour << ":" << this->Time.tm_min << ":"
       << this->Time.tm_sec << endl;
}

bool Date::compareDate(Date startDate, Date endDate) {
  time_t start = mktime(&startDate.Time);
  time_t end = mktime(&endDate.Time);
  time_t cur = mktime(&this->Time);
  if (end == -1 || start == -1 || start >= end) {
    cout << "Invalid date !\n";  // end or start date before 1/1/1970 
                                 // or end before start
    return false;
  }
  if (start <= cur && end >= cur) {
    return true;
  } else
    return false;
}

void Date::getCurrentTime() {
  time_t now = time(0);
  this->Time = *localtime(&now);
}

void Date::getDay() {
  cout << "Day: ";
  cin >> this->Time.tm_mday;
}

void Date::getMonth() {
  int tmpMonth;
  cout << "Month: ";
  cin >> tmpMonth;
  this->Time.tm_mon = tmpMonth - 1;
}
void Date::getYear() {
  int tmpYear;
  cout << "Year: ";
  cin >> tmpYear;
  this->Time.tm_year = tmpYear - 1900;
}
