#pragma once

#include <string>
#include "List.h"

using std::string;

class Student;

class Class {
 public:
  string classID;
  string className;
  List<string> listStudentIDs;
};