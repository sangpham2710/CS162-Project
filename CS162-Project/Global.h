#pragma once

#include <string>

#include "Class.h"
#include "Course.h"
#include "List.h"
#include "SchoolYear.h"
#include "Semester.h"
#include "Student.h"
#include "User.h"

using std::string;

class Global {
 public:
  static List<User>::iterator currentUser;
  static List<Semester>::iterator currentSemester;
  static List<User> allUsers;
  static List<SchoolYear> allSchoolYears;

  // these two lists are for matching iterators as the program starts
  static List<List<Student>::iterator> pStudents;
  static List<List<Course>::iterator> pCourses;
};