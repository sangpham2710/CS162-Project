#pragma once

#include <string>

#include "ID.h"
#include "List.h"

using std::string;

class Class {
 public:
  string _id;
  string className;
  List<Student> listStudents;

  Class() : _id(ID::gen()) {}
  ~Class() {}
};