#pragma once

#include <list>
#include <string>

#include "ID.h"
#include "List.h"

using std::string;

class Semester;
class Student;

class Course {
 public:
  string _id;
  string courseCode;
  string courseName;
  string lecturer;
  string startDate;
  string endDate;
  int maxNumberOfStudents;
  int numberOfCredits;
  string schedule;
  Semester* pSemester;
  List<Student*> pStudents;

  Course() : _id(ID::gen()) {}
  friend std::ostream& operator<<(std::ostream& stream, const Course& course);
  void viewScoreboard();
  void importScoreboard();
  void exportScoreboard();
};