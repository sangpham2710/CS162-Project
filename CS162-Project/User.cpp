#include "User.h"

#include <iostream>

#include "App.h"
#include "List.h"

using std::cin;
using std::cout;

std::istream& operator>>(std::istream& stream, User& user) {
  int n;
  stream >> user._id;
  stream >> user.username;
  stream >> user.password;
  stream >> n;
  user.userType = static_cast<User::Type>(n);

  if (user.userType == User::Type::STUDENT) {
    string studentID;
    stream >> studentID;
    user.pStudent = *App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->_id == studentID; });
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const User& user) {
  stream << user._id << '\n';
  stream << user.username << '\n';
  stream << user.password << '\n';
  stream << user.userType << '\n';
  if (user.userType == User::Type::STUDENT)
    stream << user.pStudent->_id << '\n';
  return stream;
}

void User::login() {
  List<User*>::iterator it;
  while (true) {
    cout << "Username: ";
    string username;
    cin >> username;
    cout << "Password: ";
    string password;
    cin >> password;
    it = App::pUsers.find_if([&](User* const& user) {
      return username == user->username && password == user->password;
    });
    if (it != App::pUsers.end()) break;
    cout << "Incorrect username or password!\n";
  }
  App::pCurrentUser = *it;
  cout << "Successfully logged in\n";
}
