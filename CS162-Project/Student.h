#pragma once

#include <string>

#include "Course.h"
#include "CourseMark.h"
#include "ID.h"
#include "List.h"

using std::string;

class Student {
 private:
  string _id;
  string studentCode;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;
  List<CourseMark> listCourseMarks;

 public:
  Student() : _id(ID::gen()) {}
  ~Student() {}
  double getSemesterGPA(Semester);
  double getOverallGPA();
};