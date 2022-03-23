#pragma once

#include <string>

#include "Class.h"
#include "List.h"
#include "Semester.h"

using std::string;

class SchoolYear {
 public:
  string id;
  string name;
  List<Semester> semesters;
  List<Class> classes;


  SchoolYear() {}
  ~SchoolYear() {}
};