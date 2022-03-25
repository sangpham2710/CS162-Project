#include "Menu.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Global.h"

using std::cin;
using std::cout;

void Menu::staffMenu() {
  Console::clear();
  cout << "1. New school year\n";
  cout << "2. View school year\n";

  cout << "3. New semester\n";
  cout << "4. View semester\n";

  cout << "5. New class\n";
  cout << "6. View/Edit class\n";

  cout << "7. New student\n";
  cout << "8. View/Edit student\n";

  cout << "9. New course\n";
  cout << "10. View/Edit course\n";

  cout << "11. Logout\n";

  cout << "Your option: ";
  int option = -1;
  while (option < 1 || option > 11) {
    cin >> option;
    if (option == 11) {
      Global::currentUser = User();
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