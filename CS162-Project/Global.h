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
  static User currentUser;
  static Semester currentSemester;
  static List<User> allUsers;
  static List<Student> allStudents;
  static List<SchoolYear> allSchoolYears;
  static List<Semester> allSemesters;
  static List<Course> allCourses;
  static List<Class> allClasses;
};