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

void App::saveData() {}

void App::auth() {
  List<User>::iterator it;
  while (true) {
    cout << "Username: ";
    string username;
    cin >> username;
    cout << "Password: ";
    string password;
    cin >> password;
    it = Global::allUsers.find_if([&](const User& user) {
      return username == user.username && password == user.password;
    });
    if (it != Global::allUsers.end()) break;
    cout << "Incorrect username or password!\n";
  }
  Global::currentUser = *it;
  cout << "Successfully logged in\n";
}

void App::run() {
  loadData();

  auth();
  if (Global::currentUser.userType == UserType::ACADEMIC_STAFF) {
    cout << Global::currentUser._id << '\n';
    return;
  }
  if (Global::currentUser.userType == UserType::STUDENT) {
    return;
  }
}
