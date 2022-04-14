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

  static void createCourse();    // done
  static void courseMainMenu();  // done

  void updateCourseInfo();       // done
  void viewStudentScoreboard();  // done

  void importScoreboard();
  void exportScoreboard();
  void importStudents();
  void exportStudents();

  void addStudent();               // done
  void removeStudent();            // done
  void updateStudentScoreBoard();  // done
  void deleteCourse();

  void courseChooseMenu();         // done
  void courseUpdateMenu();         // done
  void courseUpdateStudentMenu();  // done
};