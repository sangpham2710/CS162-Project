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

class App {
 public:
  static User* pCurrentUser;
  static Semester* pCurrentSemester;
  static Semester* pRecentSemester;
  static List<User*> pUsers;
  static List<SchoolYear*> pSchoolYears;
  static List<Semester*> pSemesters;
  static List<Course*> pCourses;
  static List<Class*> pClasses;
  static List<Student*> pStudents;

  static void allocate();
  static void loadData();
  static void main();
  static void saveData();
  static void deallocate();
  static void run();
};
