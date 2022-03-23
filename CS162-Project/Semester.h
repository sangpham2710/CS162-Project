#pragma once

#include <string>

#include "Course.h"

using std::string;

class Semester {
 public:
  List<Course> listCourses;
  string schoolYearID;


  void addCourse(Course* course);
  void viewCourse(Course* course);
};