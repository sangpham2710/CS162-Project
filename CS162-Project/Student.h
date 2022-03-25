#pragma once

#include <string>

#include "Course.h"
#include "CourseMark.h"
#include "List.h"
#include "ID.h"

using std::string;

class Course;

class Student {
 public:
  string _id;
  int no;
  string studentCode;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;
  string classID;

  List<Course*> courses;
  List<CourseMark> courseMarks;

  Student() : _id(ID::gen()) {}
  ~Student() {}
  double getSemesterGPA(const string& semesterID);
  double getOverallGPA();
};