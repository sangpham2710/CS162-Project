#pragma once

#include <string>

#include "ID.h"
#include "List.h"

using std::string;

class SchoolYear {
 public:
  string _id;
  string name;
  List<string> semesterIDs;
  List<string> classIDs;

  SchoolYear() : _id(ID::gen()) {}
  ~SchoolYear() {}
};