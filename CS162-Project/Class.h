#pragma once

#include <string>

#include "ID.h"
#include "List.h"
#include "Student.h"

using std::string;

class Class {
 public:
  string _id;
  string classCode;
  List<Student> students;

  Class() : _id(ID::gen()) {}
};