#include "Menu.h"

#include <iostream>

#include "App.h"
#include "Class.h"
#include "Console.h"
#include "CourseRegistrationSession.h"
#include "Student.h"
#include "Utils.h"

using std::cin;
using std::cout;

void Menu::staffMenu() {
  Console::clear();
  if (!App::pRecentSemester) {
    cout << "There's currently no semester in the system, please contact "
            "Admin!\n";
    Utils::waitForKeypress();
    App::pCurrentUser = nullptr;
    App::main();
    return;
  }
  Utils::getCurrentSemester();
  bool isRecentSemester =
      App::pCurrentSemester->_id == App::pRecentSemester->_id;
  Utils::printLine();
  cout << "1. Change password\n";
  cout << "2. Update info\n";
  cout << "3. Courses\n";
  cout << "4. Classes\n";
  cout << "5. School years / Semesters\n";
  cout << "6. Change default semester\n";
  if (isRecentSemester) {
    cout << "7. Course registration session\n";
  }
  Utils::printLine();
  cout << "0. Logout\n\n";

  int option = Utils::getOption(0, isRecentSemester ? 7 : 6);
  switch (option) {
    case 1:
      App::pCurrentUser->changePassword();
      break;
    case 2:
      App::pCurrentUser->pStaff->updateStaffInfo();
      break;
    case 3:
      Course::courseMainMenu();
      break;
    case 4:
      Class::viewMainMenu();
      break;
    case 5:
      SchoolYear::viewSchoolYearSemesterMenu();
      break;
    case 6:
      Semester::changeDefaultSemester();
      break;
    case 7:
      CourseRegistrationSession::viewMainMenu();
      break;
    case 0:
      App::pCurrentUser = nullptr;
      App::main();
      break;
  }
}

void Menu::studentMenu() {
  Console::clear();
  if (!App::pRecentSemester) {
    cout << "There's currently no semester in the system, please contact "
            "Admin!\n";
    Utils::waitForKeypress();
    App::pCurrentUser = nullptr;
    App::main();
    return;
  }
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Change password\n";
  cout << "2. Update info\n";
  cout << "3. Enroll/unenroll a course\n";
  cout << "4. View enrolled courses\n";
  cout << "5. View scoreboard\n";
  cout << "6. View schedule\n";
  Utils::printLine();
  cout << "0. Logout\n\n";

  int option = Utils::getOption(0, 6);

  switch (option) {
    case 0:
      App::pCurrentUser = nullptr;
      App::main();
      break;
    case 1:
      App::pCurrentUser->changePassword();
      break;
    case 2:
      App::pCurrentUser->pStudent->updateStudentInfo();
      break;
    case 3:
      // Enroll/Unenroll a course
      App::pCurrentUser->pStudent->enrollUnenrollCourseScene();
      break;
    case 4:
      // View enrolled courses
      App::pCurrentUser->pStudent->viewEnrolledCourses();
      break;
    case 5:
      App::pCurrentUser->pStudent->viewStudentScoreboard();
      break;
    case 6:
      App::pCurrentUser->pStudent->viewSchedule();
  }
}

void Menu::adminMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Show all users\n";
  cout << "2. Show all school years\n";
  cout << "3. Show all semesters\n";
  cout << "4. Show all courses\n";
  cout << "5. Show all classes\n";
  cout << "6. Show all students\n";
  cout << "7. Show all staffs\n";
  cout << "8. Show course registration session\n";
  cout << "9. Add new staff\n";
  if (!App::pCurrentSemester) cout << "10. Create first semester\n";
  Utils::printLine();
  cout << "0. Logout\n\n";
  int option;
  if (!App::pCurrentSemester)
    option = Utils::getOption(0, 10);
  else
    option = Utils::getOption(0, 9);
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  switch (option) {
    case 0:
      delete App::pCurrentUser;
      App::pCurrentUser = nullptr;
      App::main();
      return;
    case 1:
      for (const auto& p : App::pUsers) p->displayUser();
      break;
    case 2:
      for (const auto& p : App::pSchoolYears) p->displaySchoolYear();
      break;
    case 3:
      for (const auto& p : App::pSemesters) p->displaySemester();
      break;
    case 4:
      for (const auto& p : App::pCourses) p->displayCourse();
      break;
    case 5:
      for (const auto& p : App::pClasses) p->displayClass();
      break;
    case 6:
      for (const auto& p : App::pStudents) p->displayStudent();
      break;
    case 7:
      for (const auto& p : App::pStaffs) p->displayStaff();
      break;
    case 8:
      App::courseRegistrationSession.displayCourseRegistrationSession();
      break;
    case 9:
      Staff::createStaff();
      return;
    case 10:
      // Create first semester
      Semester::createFirstSemester();
      return;
  }
  Utils::printLine();
  Utils::waitForKeypress();
  Menu::adminMenu();
}

void Menu::welcome() {
  Console::clear();
  cout << "1. Login\n";
  cout << "2. Exit\n\n";
  int option = Utils::getOption(1, 2);
  if (option == 1)
    User::login();
  else
    Menu::exit();
}

void Menu::exit() {
  cout << "Are you sure you want to exit the program?\n";
  cout << "1. Yes\n";
  cout << "2. No\n\n";
  int option = Utils::getOption(1, 2);
  if (option == 2) {
    Menu::welcome();
    return;
  }
}