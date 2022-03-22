#pragma once
#include "student.h"
#include "class.h"
#include<iostream>
using namespace std;

class StudySlot: public Student, public Class{
 private:
  StudySlot(int _studentID, string _studentName, string _gender,
            string _dayOfBirth, string _studentSpecialty, string _username,
            string _password, string _typeOfAccount, int _classID,
            int _totalStudent, int _totalMaleStudent, int _totalFemaleStudent)
      : Student(_studentID, _studentName, _gender, _dayOfBirth,
                _studentSpecialty, _username, _password, _typeOfAccount),
        Class(_classID, _totalStudent, _totalMaleStudent,
              _totalFemaleStudent) {}
};