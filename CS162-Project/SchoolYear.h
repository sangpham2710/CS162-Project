#pragma once

#include <string>

#include "Class.h"
#include "ID.h"
#include "List.h"
#include "Semester.h"

using std::string;

class SchoolYear {
 public:
  string _id;
  string name;
  List<Semester*> pSemesters;
  List<Class*> pClasses;

  SchoolYear() : _id(ID::gen()) {}
  friend std::ostream& operator<<(std::ostream& stream,
                                  const SchoolYear& schoolYear);
};