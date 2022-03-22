#pragma once
#include "study-slot.h"
#include<iostream>
using namespace std;

class Class{
 protected:
  int classID;
  int totalStudent;
  int totalMaleStudent;
  int totalFemaleStudent;
  Class(int _classID, int _totalStudent, int _totalMaleStudent,
        int _totalFemaleStudent)
      : classID(_classID),
        totalStudent(_totalStudent),
        totalMaleStudent(_totalMaleStudent),
        totalFemaleStudent(_totalFemaleStudent) {}
};