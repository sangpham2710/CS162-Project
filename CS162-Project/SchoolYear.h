#pragma once

#include <string>

#include "Class.h"
#include "List.h"
#include "Semester.h"

using std::string;

class SchoolYear {
 private:
  string name;
  List<Semester> semesters;
  List<Class> classes;

 public:
  SchoolYear() {}
  ~SchoolYear() {}
};