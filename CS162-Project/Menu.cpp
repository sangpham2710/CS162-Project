#include "Menu.h"

#include <iostream>

#include "App.h"
#include "Class.h"
#include "Console.h"
#include "Student.h"
#include "Utils.h"

using std::cin;
using std::cout;

void Menu::staffMenu() {
  Console::clear();
  cout << "-------------------------------\n";
  cout << "1. Change password\n";
  cout << "2. Update info\n";
  cout << "3. Courses\n";
  cout << "4. Classes\n";
  cout << "5. School years / Semesters\n";
  cout << "6. Change default semester\n";
  cout << "--------------------------------\n";
  cout << "0. Return\n";
  cout << "--------------------------------\n";
  int option = Utils::getOption(0, 6);
    switch (option) {
    case 1: {
      App::pCurrentUser->changePassword();
      break;
    }
    case 2: {
      App::pCurrentUser->pStaff->updateStaffInfo();
      break;
    }
      case 3:
        // Courses scene
        Course::courseMainMenu();
        break;
      case 4:
        // Classes scene
        Class::viewMainMenu();
        break;
      case 5:
        // ------------------HOA------------------------
        SchoolYear::viewSchoolYearSemesterMenu();
        break;
      case 6:
        // Change default semester
        Semester::changeDefaultSemester();
        break;
      case 0:
        App::pCurrentUser = nullptr;
        App::main();
        return;
        break;
      default:
        break;
    }
  }

void Menu::studentMenu() {
  Console::clear();
  cout << "---------------------------\n";
  cout << "1. Change password\n";
  cout << "2. Update info\n";
  cout << "3. Enroll in a course\n";
  cout << "4. View/Unenroll courses\n";
  cout << "5. View scoreboard\n";
  cout << "---------------------------\n";
  cout << "0. Return\n";
  cout << "---------------------------\n";
  // Handle options
  int option = Utils::getOption(0, 5);

  switch (option) {
      // Return
    case 0: {
      App::pCurrentUser = nullptr;
      App::main();
      return;
      break;
    }

      // Change password
    case 1: {
      App::pCurrentUser->changePassword();
      break;
    }

      // Update info
    case 2: {
      App::pCurrentUser->pStudent->updateStudentInfo();
      break;
    }
    case 3: {
      // Enroll in course
    }
    case 4: {
      // View/Unenroll courses
    }
    case 5: {
      App::pCurrentUser->pStudent->viewStudentScoreboard();
      break;
    }
    default:
      break;
  }
}

void Menu::welcome() {
  cout << "1. Login\n";
  cout << "2. Exit\n";
  int option = Utils::getOption(1, 2);
  if (option == 1)
    User::login();
  else
    Menu::exit();
}

void Menu::exit() {
  cout << "Are you sure you want to exit the program?\n";
  cout << "1. Yes\n";
  cout << "2. No\n";
  int option = Utils::getOption(1, 2);
  if (option == 2) {
    Menu::welcome();
    return;
  }
}