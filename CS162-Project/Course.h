#pragma once

#include <string>

#include "List.h"

using std::string;

class Student;
class Semester;

class Course {
 private:
  Semester* pSemester;
  string courseId;
  string courseName;
  string lecturer;
  string startDate;
  string endDate;
  int maxNumberOfStudents;
  int numberOfCredits;
  string schedule;
  List<Student> listStudents;

 public:
  Course() {}
  ~Course() {}
  void viewScorebroad();
  void importScoreboard();
  void exportScoreboard();
};