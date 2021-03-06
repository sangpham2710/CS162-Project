#pragma once
#include <iostream>
#include "course-registration-session.h"
#include "lecturer.h"
using namespace std;

class Module : public CourseRegistrationSession, public Lecturer{
 protected:
  int moduleID;
  string lecturerName;
  string classroom;
  string session;
  int maxSlot;
  int moduleOrder;
  Module(int _moduleID, string _lecturerName, string _classroom,
         string _session, int _maxSlot, int _moduleOrder,
         string _startDateRegistration, string _endDateRegistration,
         int _sessionOrder, int _semesterID, string _semesterName, int _year,
         string _startDateSemester, string _endDateSemester)
      : CourseRegistrationSession(_startDateRegistration, _endDateRegistration,
                                  _sessionOrder, _semesterID, _semesterName,
                                  _year, _startDateSemester, _endDateSemester),
        Lecturer(_lecturerName),
        moduleID(_moduleID),
        classroom(_classroom),
        session(_session),
        maxSlot(_maxSlot),
        moduleOrder(_moduleOrder) {}
};