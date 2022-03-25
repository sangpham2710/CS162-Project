#pragma once

#include <list>
#include <string>

#include "ID.h"
#include "List.h"
#include "Student.h"

using std::string;

class Course {
 public:
  string _id;
  string semesterID;
  string courseCode;
  string courseName;
  string lecturer;
  string startDate;
  string endDate;
  int maxNumberOfStudents = 0;
  int numberOfCredits = 0;
  string schedule;

  List<List<Student>::iterator> students;

  Course() : _id(ID::gen()) {}
  void viewScoreboard();
  void importScoreboard();
  void exportScoreboard();
};