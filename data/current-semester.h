#pragma once
#include<iostream>
#include "semester.h"

using namespace std;

class CurrentSemester {
 private:
  string ID;
  CurrentSemester(string _ID, int _semesterID, string _semesterName, int _year,
                  string _startDateSemester, string _endDateSemester)
      : Semester(_semesterID, _year, _startDateSemester, _endDateSemester),
        ID(_ID) {}
};