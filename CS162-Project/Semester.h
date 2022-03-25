#pragma once

#include <string>

#include "Course.h"
#include "ID.h"

using std::string;

class SchoolYear;

class Semester {
 public:
  string _id;
  List<SchoolYear>::iterator pSchoolYear;
  List<Course> courses;

  Semester() : _id(ID::gen()) {}
  void addCourse(const Course& course);
  void viewCourse(const string& courseID);
};