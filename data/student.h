#pragma once
#include "account.h"
using namespace std;

class Student : public Account {
 protected:
  int studentID;
  string studentName;
  string gender;
  string dayOfBirth;  // Need to fix
  string studentSpecialty;
  Student(int _studentID, string _studentName, string _gender,
          string _dayOfBirth, string _studentSpecialty, string _username,
          string _password, string _typeOfAccount)
      : Account(_username, _password, _typeOfAccount) {}
};