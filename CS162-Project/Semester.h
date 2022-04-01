#pragma once

#include <string>

#include "Course.h"
#include "ID.h"

using std::string;

class SchoolYear;

class Semester {
 public:
  string _id;
  string semesterName;
  SchoolYear* pSchoolYear;
  List<Course*> pCourses;

  Semester(const string& id)
      : _id{id}, semesterName{}, pSchoolYear{}, pCourses{} {}
  Semester() : Semester{ID::gen()} {}

  friend std::istream& operator>>(std::istream& stream, Semester& semester);
  friend std::ostream& operator<<(std::ostream& stream,
                                  const Semester& semester);
  void addCourse(Course* const& course);
  void viewCourse(const string& courseID);
  static void viewSemesterMenu();
  static void choose(const int& choice, const int& i);
  static void create();
  void viewEditSemester();
  void updateSemester();
};