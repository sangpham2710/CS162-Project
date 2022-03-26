#pragma once

#include <string>

#include "ID.h"
#include "List.h"
#include "Student.h"

using std::string;

class Student;

class Class {
 public:
  string _id;
  string classCode;
  List<Student*> pStudents;

  Class() : _id(ID::gen()) {}
  friend std::ostream& operator<<(std::ostream& stream, const Class& _class);
};