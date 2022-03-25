#include "App.h"

#include <iostream>
#include <string>

#include "Console.h"
#include "Global.h"
#include "List.h"
#include "Menu.h"
#include "User.h"

using std::cin;
using std::cout;
using std::string;

void App::loadData() {
  Global::allUsers.push_back(User{"admin", "admin", UserType::ADMIN});
  Global::allUsers.push_back(User{"staff", "staff", UserType::ACADEMIC_STAFF});
  Global::allUsers.push_back(User{"student", "student", UserType::STUDENT});
}

void App::saveData() {
}

void App::main() {
  Console::clear();
  User::login();
  if (Global::currentUser->userType == UserType::ACADEMIC_STAFF) {
    Menu::staffMenu();
    return;
  }
  if (Global::currentUser->userType == UserType::STUDENT) {
    Menu::studentMenu();
    return;
  }
}

void App::run() {
  Console::setup();
  App::loadData();
  App::main();
  App::saveData();
}
