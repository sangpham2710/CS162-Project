#pragma once

#include <string>

#include "ID.h"
#include "List.h"

using std::string;

class Student;

class Class {
 public:
  string _id;
  string className;
  List<string> listStudentIDs;

  Class() : _id(ID::gen()) {}
  ~Class() {}
};