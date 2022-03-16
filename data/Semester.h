#pragma once
#include<iostream>
using namespace std;

class Semester {
 private:
  int semesterID;
  string semesterName;
  int year;
  string startDate;
  string endDate; //need to fix
  Semester(int _semesterID, string _semesterName, int _year, string _startDate,
           string _endDate)
      : semesterID(_semesterID),
        semesterName(_semesterName),
        year(_year),
        startDate(_startDate),
        endDate(_endDate) {}
};