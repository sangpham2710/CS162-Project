#pragma once
#include<iostream>
using namespace std;

class Semester {
 protected:
  int semesterID;
  string semesterName;
  int year;
  string startDateSemester;
  string endDateSemester; //need to fix
  Semester(int _semesterID, string _semesterName, int _year, string _startDateSemester,
           string _endDateSemester)
      : semesterID(_semesterID),
        semesterName(_semesterName),
        year(_year),
        startDateSemester(_startDateSemester),
        endDateSemester(_endDateSemester) {}
};