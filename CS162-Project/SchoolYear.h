#pragma once

#include <string>

#include "ID.h"
#include "List.h"
#include "Semester.h"
#include "Class.h"

using std::string;

class SchoolYear {
 public:
  string _id;
  string name;
  List<Semester> semesters;
  List<Class> classes;

  SchoolYear() : _id(ID::gen()) {}
  ~SchoolYear() {}
};