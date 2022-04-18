#pragma once

#include <string>

#include "Class.h"
#include "Course.h"
#include "CourseMark.h"
#include "ID.h"
#include "List.h"
#include "Semester.h"
#include "User.h"

using std::string;

class Class;
class Semester;
class User;

class Student {
 public:
  string _id;
  string studentCode;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;
  Class* pClass;
  User* pUser;
  List<CourseMark> courseMarks;

  Student(const string& id)
      : _id{id},
        studentCode{},
        firstName{},
        lastName{},
        gender{},
        dateOfBirth{},
        socialID{},
        pClass{nullptr},
        pUser{nullptr},
        courseMarks{} {}
  Student() : Student{ID::gen()} {}

  friend std::istream& operator>>(std::istream& stream, Student& student);
  friend std::ostream& operator<<(std::ostream& stream, const Student& student);

  void viewStudentScoreboard();
  void updateStudentInfo();
  double getSemesterGPA();
  double getOverallGPA();
};