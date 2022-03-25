#include "User.h"

#include <iostream>

#include "Global.h"
#include "List.h"

using std::cin;
using std::cout;

void User::login() {
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
  Global::currentUser = it;
  cout << "Successfully logged in\n";
}