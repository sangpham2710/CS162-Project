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
  cout << "1. Courses\n";
  cout << "2. Classes\n";
  cout << "3. School years / Semesters\n";
  cout << "4. Change default semester\n";
  cout << "5. Course registration session\n";
  cout << "0. Log out\n";
  cout << "Your option: ";
  int option = -1;
  while (option < 1 || option > 5) {
    cin >> option;
    switch (option) {
      case 1:
        // Courses scene
        Course::courseMainMenu();
        break;
      case 2:
        // Classes scene
        Class::viewMainMenu();
        break;
      case 3:
        // ------------------HOA------------------------
        SchoolYear::viewSchoolYearSemesterMenu();
        break;
      case 4:
        // Change default semester
        Semester::changeDefaultSemester();
        break;
      case 5:
        CourseRegistrationSession::viewMainMenu();
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
      Menu::welcome();
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
  Console::clear();
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