#pragma once
#include "semester.h"
#include<iostream>
using namespace std;

class CourseRegistrationSession : public Semester {
 protected:
  string startDateRegistration;
  string endDateRegistration;
  int sessionOrder; //in a year
  CourseRegistrationSession(string _startDateRegistration, string _endDateRegistration, int _sessionOrder,
                            int _semesterID, string _semesterName, int _year,
                            string _startDateSemester, string _endDateSemester)
      : Semester(_semesterID, _semesterName, _year, _startDateSemester,
                 _endDateSemester),
        startDateRegistration(_startDateRegistration),
        endDateRegistration(_endDateRegistration),
        sessionOrder(_sessionOrder) {}
};