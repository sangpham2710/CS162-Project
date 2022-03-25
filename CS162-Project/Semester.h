#pragma once

#include <string>

#include "Course.h"
#include "ID.h"

using std::string;

class SchoolYear;

class Semester {
 public:
  string _id;
  SchoolYear* schoolYear;
  List<Course> courses;

  Semester() : _id(ID::gen()) {}
  ~Semester() {}
  void addCourse(const Course& course);
  void viewCourse(const string& courseID);
};