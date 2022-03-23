#pragma once

#include <string>

#include "List.h"

using std::string;

class Student;
class Semester;

class Course {
 public:
  string semesterID;
  string courseID;
  string courseName;
  string lecturer;
  string startDate;
  string endDate;
  int maxNumberOfStudents = 0;
  int numberOfCredits = 0;
  string schedule;
  List<string> studentIDs;

  Course() {}
  ~Course() {}
  void viewScorebroad();
  void importScoreboard();
  void exportScoreboard();
};