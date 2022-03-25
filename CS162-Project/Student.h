#pragma once

#include <string>

#include "Course.h"
#include "CourseMark.h"
#include "ID.h"
#include "List.h"
#include "Semester.h"

using std::string;

class Course;
class Class;

class Student {
 public:
  string _id;
  string studentCode;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;

  List<CourseMark> courseMarks;
  List<Class>::iterator pClass;

  Student() : _id(ID::gen()) {}

  double getSemesterGPA(const List<Semester>::iterator& semester);
  double getOverallGPA();
};