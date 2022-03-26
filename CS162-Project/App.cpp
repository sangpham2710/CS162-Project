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

bool App::loadData() {
  App::pUsers.push_back(new User{"admin", "admin", User::Type::ADMIN});
  App::pUsers.push_back(new User{"staff", "staff", User::Type::ACADEMIC_STAFF});
  App::pUsers.push_back(new User{"student", "student", User::Type::STUDENT});
  return true;
}

bool App::saveData() {
  auto createIfNotExists = [](const string& path) {
    if (!fs::exists(path)) fs::create_directories(path);
  };
  createIfNotExists(Paths::DATA_DIR);
  createIfNotExists(Paths::USERS_DIR);
  createIfNotExists(Paths::SCHOOLYEARS_DIR);
  createIfNotExists(Paths::SEMESTERS_DIR);
  createIfNotExists(Paths::CLASSES_DIR);
  createIfNotExists(Paths::COURSES_DIR);
  createIfNotExists(Paths::STUDENTS_DIR);

  bool ok = true;
  ok &= Data::saveIDs(Paths::USERS_DIR, App::pUsers);
  ok &= Data::saveIDs(Paths::SCHOOLYEARS_DIR, App::pSchoolYears);
  ok &= Data::saveIDs(Paths::SEMESTERS_DIR, App::pSemesters);
  ok &= Data::saveIDs(Paths::CLASSES_DIR, App::pClasses);
  ok &= Data::saveIDs(Paths::COURSES_DIR, App::pCourses);
  ok &= Data::saveIDs(Paths::STUDENTS_DIR, App::pStudents);

  ok &= Data::saveObjs(Paths::USERS_DIR, App::pUsers);
  ok &= Data::saveObjs(Paths::SCHOOLYEARS_DIR, App::pSchoolYears);
  ok &= Data::saveObjs(Paths::SEMESTERS_DIR, App::pSemesters);
  ok &= Data::saveObjs(Paths::CLASSES_DIR, App::pClasses);
  ok &= Data::saveObjs(Paths::COURSES_DIR, App::pCourses);
  ok &= Data::saveObjs(Paths::STUDENTS_DIR, App::pStudents);

  ofstream ofs("data/recentSemester.dat");
  if (!ofs.is_open()) return false;
  if (pRecentSemester) ofs << App::pRecentSemester->_id << '\n';
  ofs.close();
  return ok;
}

void App::main() {
  Console::clear();
  User::login();
  return;
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
