#include "Menu.h"

#include <iostream>

#include "App.h"
#include "Class.h"
#include "Console.h"

using std::cin;
using std::cout;

void Menu::staffMenu() {
  Console::clear();
  cout << "1. Courses\n";
  cout << "2. Classes\n";
  cout << "3. School years / Semesters\n";
  cout << "4. Change default semester\n";
  cout << "5. Log out\n";
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
        // School years / Semesters
        Console::clear();
        std::cout << "---------------------\n";
        std::cout << "1. School year\n";
        std::cout << "2. Semester\n";
        std::cout << "0. Go back\n";
        std::cout << "---------------------\n";
        int choice;
        std::cout << "Input your choice: ";
        std::cin >> choice;
        if (choice == 1) {
        //viewSchoolYearMenu()
        } else if (choice == 2) {
          Semester::viewSemesterMenu();
        } else if (choice == 0) {
          Menu::staffMenu();
        }
        else {
          cout << "Invalid input!!\n";
          //return 
        }
        break;
      case 4:
        // Change default semester
        break;
      case 5:
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
  cout << "1. Change password\n";
  cout << "2. Update info\n";
  cout << "3. Enroll in a course\n";
  cout << "4. View/Unenroll courses\n";
  cout << "5. View scoreboard\n";
}