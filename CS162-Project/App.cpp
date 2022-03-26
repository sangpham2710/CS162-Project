#include "App.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Console.h"
#include "List.h"
#include "Menu.h"

using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;

User* App::pCurrentUser{nullptr};
Semester* App::pCurrentSemester{nullptr};
Semester* App::pRecentSemester{nullptr};
List<User*> App::pUsers{};
List<SchoolYear*> App::pSchoolYears{};
List<Semester*> App::pSemesters{};
List<Course*> App::pCourses{};
List<Class*> App::pClasses{};
List<Student*> App::pStudents{};

void App::allocate() {
  Console::setup();
}

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
  auto saveIDs = [](const string& path, const auto& list) -> bool {
    ofstream ofs(path + "IDs.dat");
    if (!ofs.is_open()) return false;
    for (const auto& p : list) ofs << p->_id << '\n';
    ofs.close();
    return true;
  };

  auto saveObjs = [](const string& path, const auto& list) -> bool {
    for (const auto& p : list) {
      ofstream ofs(path + p->_id + ".dat");
      if (!ofs.is_open()) return false;
      ofs << p << '\n';
      ofs.close();
    }
    return true;
  };
  bool ok = true;
  ok &= saveIDs("data/users/", App::pUsers);
  ok &= saveIDs("data/schoolYears/", App::pSchoolYears);
  ok &= saveIDs("data/semesters/", App::pSemesters);
  ok &= saveIDs("data/classes/", App::pClasses);
  ok &= saveIDs("data/courses/", App::pCourses);
  ok &= saveIDs("data/students/", App::pStudents);

  ok &= saveObjs("data/users/", App::pUsers);
  ok &= saveObjs("data/schoolYears/", App::pSchoolYears);
  ok &= saveObjs("data/semesters/", App::pSemesters);
  ok &= saveObjs("data/classes/", App::pClasses);
  ok &= saveObjs("data/courses/", App::pCourses);
  ok &= saveObjs("data/students/", App::pStudents);

  ofstream ofs("data/app/recentSemester.dat");
  if (!ofs.is_open()) return false;
  if (pRecentSemester) ofs << App::pRecentSemester->_id << '\n';
  ofs.close();
  return ok;
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
