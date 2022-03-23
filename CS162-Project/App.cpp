#include "App.h"

#include <iostream>
#include <string>

#include "Global.h"
#include "List.h"
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

bool App::auth() {
  cout << "Username: ";
  string username;
  cin >> username;
  cout << "Password: ";
  string password;
  cin >> password;
  if (Global::allUsers.find_if([&](const User& user) {
        return username == user.username && password == user.password;
      }) == Global::allUsers.end()) {
    cout << "Incorrect username or password!\n";
    return false;
  }
  cout << "Successfully logged in\n";
  return true;
}

void App::run() {
  loadData();
  if (!App::auth()) return;
}