#pragma once

#include <string>

#include "ID.h"
#include "List.h"

using std::string;

class Student;
class CourseMark;

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
  List<Student*> students;
  List<CourseMark> coursMarks;

  Course() : _id(ID::gen()) {}
  ~Course() {}
  void viewScoreboard();
  void importScoreboard();
  void exportScoreboard();
};