#pragma once
#include <iostream>

#include "account.h"
using namespace std;

class StudentManager {
 private:
  int managerID;
  string managerName;
  string gender;
  string dayOfBirth;  // Need to fix
  StudentManager(int _managerID, string _managerName, string _gender,
                 string _dayOfBirth, string _username)
      : Account(_username, _password, _typeOfAccount),
        managerID(_managerID),
        managerName(_managerName),
        gender(_gender),
        dayOfBirth(_dayOfBirth) {}
};