#pragma once

#include <string>
#include "Student.h"
#include "ID.h"
#include "List.h"

using std::string;

class Class {
 public:
  string _id;
  string className;

  List<Student> student;
  SchoolYear* pSchoolYear;

  Class() : _id(ID::gen()) {}

};