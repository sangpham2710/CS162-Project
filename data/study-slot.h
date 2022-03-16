#pragma once
#include "student.h"
#include<iostream>
using namespace std;

class StudySlot: public Student {
 private:
  string classID;
  StudySlot(int _studentID, string _studentName, string _gender,
            string _dayOfBirth, string _studentSpecialty, string _username,
            string _password, string _typeOfAccount, string _classID)
      : Student(_studentID, _studentName, _gender, _dayOfBirth,
                _studentSpecialty, _username, _password, _typeOfAccount),
        classID(_classID) {}
};