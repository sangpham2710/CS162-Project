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

namespace Paths {
const string DATA_DIR = "data/";
const string USERS_DIR = "data/users/";
const string SCHOOLYEARS_DIR = "data/schoolYears/";
const string SEMESTERS_DIR = "data/semesters/";
const string CLASSES_DIR = "data/classes/";
const string COURSES_DIR = "data/courses/";
const string STUDENTS_DIR = "data/students/";
};  // namespace Paths

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
  static bool loadData();
  static void main();
  static bool saveData();
  static void deallocate();
  static void run();
};
