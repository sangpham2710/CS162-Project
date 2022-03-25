#pragma once

#include <string>
#include "SchoolYear.h"
#include "Course.h"
#include "ID.h"

using std::string;

class Semester {
 public:
  string _id;
  SchoolYear* pSchoolYear;
  List<Course> courses;

  Semester() : _id(ID::gen()) {}
  ~Semester() {}
  void addCourse(const Course& course);
  void viewCourse(const string& courseID);
};