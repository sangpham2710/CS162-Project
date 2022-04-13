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
    cout << "Invalid date !\n";  // end or start date before 1/1/1970 or end
                                 // before start
    return false;
  }
  if (start <= cur && end >= cur) {
    return true;
  } else
    return false;
}

void Date::getCurrentTime() {
  time_t now = time(0);
  localtime_s(&this->Time, &now);
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

void Date::saveToFile() {
  std::ofstream fout;
  fout.open("Date.txt");
  fout << this->Time.tm_mday << '\n';
  fout << this->Time.tm_mon + 1 << '\n';
  fout << this->Time.tm_year + 1900 << '\n';
  fout << this->Time.tm_hour << '\n';
  fout << this->Time.tm_min << '\n';
  fout << this->Time.tm_sec << '\n';
  fout << this->Time.tm_wday << '\n';
  fout << this->Time.tm_yday << '\n';
  fout << this->Time.tm_isdst << '\n';
  fout.close();
}

void Date::loadFromFile() {
  std::ifstream fin;
  int tmpMon;
  int tmpYear;
  fin.open("Date.txt");
  if (fin.is_open()) {
    while (!fin.eof()) {
      fin >> this->Time.tm_mday;
      fin >> tmpMon;
      this->Time.tm_mon = tmpMon - 1;
      fin >> tmpYear;
      this->Time.tm_year = tmpYear - 1900;
      fin >> this->Time.tm_hour;
      fin >> this->Time.tm_min;
      fin >> this->Time.tm_sec;
      fin >> this->Time.tm_wday;
      fin >> this->Time.tm_yday;
      fin >> this->Time.tm_isdst;
    }
  }
  fin.close();
}