#include<iostream>
#include"module.h"
#include"student.h"

using namespace std;

class ModuleRegistration : public Module
	, public Student {
  string moduleRegistrationTime;
  ModuleRegistration(int _studentID, string _studentName, string _gender,
                     string _dayOfBirth, string _studentSpecialty,
                     string _username, string _password, string _typeOfAccount,
                     int _moduleID, string _lecturerName, string _classroom,
                     string _session, int _maxSlot, int _moduleOrder,
                     string _startDateRegistration, string _endDateRegistration,
                     int _sessionOrder, int _semesterID, string _semesterName,
                     int _year, string _startDateSemester,
                     string _endDateSemester, string _moduleRegistrationTime)
      : Student(_studentID, _studentName, _gender,
                _dayOfBirth, _studentSpecialty,  _username, _password, _typeOfAccount),
        Module(_moduleID, _lecturerName, _classroom,
               _session, _maxSlot, _moduleOrder,
               _startDateRegistration, _endDateRegistration,
               _sessionOrder, _semesterID, _semesterName, _year,
               _startDateSemester, _endDateSemester),
        moduleRegistrationTime(_moduleRegistrationTime) {}
};