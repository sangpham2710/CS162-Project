#pragma once

#include<iostream>
#include <list>
#include <string>

#include "ID.h"
#include "List.h"

using std::string;
using std::cin;
using std::cout;

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

  Course(const string& id)
      : _id{id},
        courseCode{},
        courseName{},
        lecturer{},
        startDate{},
        endDate{},
        maxNumberOfStudents{},
        numberOfCredits{},
        schedule{},
        pSemester{nullptr},
        pStudents{} {}
  Course() : Course{ID::gen()} {}

  friend std::istream& operator>>(std::istream& stream, Course& course);
  friend std::ostream& operator<<(std::ostream& stream, const Course& course);

  static void create();
  static void choose(Course* pCourse, short option);

  void updateCourseInfo(Course* pCourse);
  void viewScoreboard();
  void importScoreboard();
  void exportScoreboard();
};