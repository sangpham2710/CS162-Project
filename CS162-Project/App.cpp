#include "App.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Console.h"
#include "Data.h"
#include "List.h"
#include "Menu.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
namespace fs = std::filesystem;

User* App::pCurrentUser{nullptr};
Semester* App::pCurrentSemester{nullptr};
Semester* App::pRecentSemester{nullptr};
List<User*> App::pUsers{};
List<SchoolYear*> App::pSchoolYears{};
List<Semester*> App::pSemesters{};
List<Course*> App::pCourses{};
List<Class*> App::pClasses{};
List<Student*> App::pStudents{};

void App::allocate() { Console::setup(); }

void App::deallocate() {
  for (const auto& p : App::pUsers) delete p;
  for (const auto& p : App::pSchoolYears) delete p;
  for (const auto& p : App::pSemesters) delete p;
  for (const auto& p : App::pCourses) delete p;
  for (const auto& p : App::pClasses) delete p;
  for (const auto& p : App::pStudents) delete p;
  // already deallocated
  // delete App::pCurrentUser;
  // delete App::pCurrentSemester;
  // delete App::pRecentSemester;
}

void App::loadData() {
  // App::pUsers.push_back(new User{"admin", "admin", User::Type::ADMIN});
  // App::pUsers.push_back(new User{"staff", "staff",
  // User::Type::ACADEMIC_STAFF});
  //  App::pUsers.push_back(new User{"student", "student",
  //  User::Type::STUDENT});

  if (!fs::exists(Data::DATA_DIR)) return;
  if (fs::exists(Data::USERS_DIR)) Data::loadIDs(Data::USERS_DIR, App::pUsers);
  if (fs::exists(Data::SCHOOLYEARS_DIR))
    Data::loadIDs(Data::SCHOOLYEARS_DIR, App::pSchoolYears);
  if (fs::exists(Data::SEMESTERS_DIR))
    Data::loadIDs(Data::SEMESTERS_DIR, App::pSemesters);
  if (fs::exists(Data::CLASSES_DIR))
    Data::loadIDs(Data::CLASSES_DIR, App::pClasses);
  if (fs::exists(Data::COURSES_DIR))
    Data::loadIDs(Data::COURSES_DIR, App::pCourses);
  if (fs::exists(Data::STUDENTS_DIR))
    Data::loadIDs(Data::STUDENTS_DIR, App::pStudents);

  if (fs::exists(Data::USERS_DIR)) Data::loadObjs(Data::USERS_DIR, App::pUsers);
  if (fs::exists(Data::SCHOOLYEARS_DIR))
    Data::loadObjs(Data::SCHOOLYEARS_DIR, App::pSchoolYears);
  if (fs::exists(Data::SEMESTERS_DIR))
    Data::loadObjs(Data::SEMESTERS_DIR, App::pSemesters);
  if (fs::exists(Data::CLASSES_DIR))
    Data::loadObjs(Data::CLASSES_DIR, App::pClasses);
  if (fs::exists(Data::COURSES_DIR))
    Data::loadObjs(Data::COURSES_DIR, App::pCourses);
  if (fs::exists(Data::STUDENTS_DIR))
    Data::loadObjs(Data::STUDENTS_DIR, App::pStudents);

  ifstream ifs(Data::DATA_DIR + "recentSemester.txt");
  if (!ifs.is_open()) return;
  string recentSemesterID;
  ifs >> recentSemesterID;
  App::pRecentSemester = *App::pSemesters.find_if(
      [&](const auto& p) -> bool { return p->_id == recentSemesterID; });
  App::pCurrentSemester = App::pRecentSemester;
  ifs.close();
}

void App::saveData() {
  auto createIfNotExists = [](const string& path) {
    if (!fs::exists(path)) fs::create_directories(path);
  };
  createIfNotExists(Data::DATA_DIR);
  createIfNotExists(Data::USERS_DIR);
  createIfNotExists(Data::SCHOOLYEARS_DIR);
  createIfNotExists(Data::SEMESTERS_DIR);
  createIfNotExists(Data::CLASSES_DIR);
  createIfNotExists(Data::COURSES_DIR);
  createIfNotExists(Data::STUDENTS_DIR);

  Data::saveIDs(Data::USERS_DIR, App::pUsers);
  Data::saveIDs(Data::SCHOOLYEARS_DIR, App::pSchoolYears);
  Data::saveIDs(Data::SEMESTERS_DIR, App::pSemesters);
  Data::saveIDs(Data::CLASSES_DIR, App::pClasses);
  Data::saveIDs(Data::COURSES_DIR, App::pCourses);
  Data::saveIDs(Data::STUDENTS_DIR, App::pStudents);

  Data::saveObjs(Data::USERS_DIR, App::pUsers);
  Data::saveObjs(Data::SCHOOLYEARS_DIR, App::pSchoolYears);
  Data::saveObjs(Data::SEMESTERS_DIR, App::pSemesters);
  Data::saveObjs(Data::CLASSES_DIR, App::pClasses);
  Data::saveObjs(Data::COURSES_DIR, App::pCourses);
  Data::saveObjs(Data::STUDENTS_DIR, App::pStudents);

  ofstream ofs(Data::DATA_DIR + "recentSemester.txt");
  if (!ofs.is_open()) return;
  if (pRecentSemester) ofs << App::pRecentSemester->_id << '\n';
  ofs.close();
}

void App::main() {
  Console::clear();
  User::login();
  if (App::pCurrentUser->userType == User::Type::ACADEMIC_STAFF) {
    Menu::staffMenu();
    return;
  }
  if (App::pCurrentUser->userType == User::Type::STUDENT) {
    Menu::studentMenu();
    return;
  }
}

void App::run() {
  App::allocate();
  App::loadData();
  App::main();
  App::saveData();
  App::deallocate();
}
