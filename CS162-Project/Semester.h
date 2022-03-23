#pragma once

#include <string>

#include "Course.h"
#include "ID.h"

using std::string;

class Semester {
 public:
  string _id;
  string schoolYearID;
  List<string> listCourseIDs;

  Semester() : _id(ID::gen()) {}
  ~Semester() {}
  void addCourse(const Course& course);
  void viewCourse(const Course& course);
};