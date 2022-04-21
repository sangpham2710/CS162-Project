#pragma once

#include <list>
#include <string>

#include "CSV.h"
#include "ID.h"
#include "List.h"

using std::string;

class Semester;
class Student;

class Course {
 public:
  string _id;
  string courseCode, courseName, lecturer, startDate, endDate;
  int maxNumberOfStudents, numberOfCredits, session1, session2;
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
        session1{},
        session2{},
        pSemester{nullptr},
        pStudents{} {}
  Course() : Course{ID::gen()} {}

  friend std::istream& operator>>(std::istream& stream, Course& course);
  friend std::ostream& operator<<(std::ostream& stream, const Course& course);

  static void createCourse();
  static void courseMainMenu();

  void updateCourseInfo();
  void viewStudentScoreboard();

  void importScoreboard();
  void exportScoreboard();
  void importStudents();
  void exportStudents();

  void addStudent();
  void removeStudent();
  void updateStudentScoreBoard();
  void deleteCourseScene();
  void deleteCourse(bool casacade);

  void courseChooseMenu();
  void courseUpdateMenu();
  void courseUpdateStudentMenu();

  void enrollUnenrollCourse();

  void displayCourse();
};