#pragma once

#include <string>

#include "Course.h"
#include "ID.h"

using std::string;

class SchoolYear;

class Semester {
 public:
  string _id;
  SchoolYear* pSchoolYear;
  List<Course*> pCourses;

  Semester() : _id(ID::gen()), pSchoolYear(nullptr), pCourses() {}
  friend std::ostream& operator<<(std::ostream& stream,
                                  const Semester& semester);
  void addCourse(Course* const& course);
  void viewCourse(const string& courseID);
};