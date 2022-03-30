#include "Menu.h"

#include <iostream>

#include "App.h"
#include "Console.h"

using std::cin;
using std::cout;

void Menu::staffMenu() {
  Console::clear();
  cout << "1. Courses\n";
  cout << "2. Classes\n";

  cout << "3. School years/Semester\n";
  cout << "4. Change default semester\n";

  cout << "5. log out\n"
  cout << "Your option: ";
  int option = -1;
  while (option < 1 || option > 11) {
    cin >> option;
    if (option == 1) {
        Course::courseMainMenu();
        return;
    }
    if (option == 5) {
      App::pCurrentUser = nullptr;
      App::main();
      return;
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