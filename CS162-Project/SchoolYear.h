#pragma once

#include <string>
#include "Semester.h"
#include "Class.h"
#include "ID.h"
#include "List.h"

using std::string;

class SchoolYear {
 public:
  string _id;
  string yearName;

  List<Semester> semester;
  List<Class> classes;

  SchoolYear() : _id(ID::gen()) {}
  void saveToFile() {
	  // schoolYear/:year/semester
	  for (const auto& Semester : semester) {
		  semester.saveToFile();
	  }
	  //schoolYear/:year/class
	  for (const auto& Class : classes) {
		  class.saveToFile();
	  }
  }
};