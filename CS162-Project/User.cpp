#include "User.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "List.h"
#include "Menu.h"
#include "Utils.h"

using std::cin;
using std::cout;

std::istream& operator>>(std::istream& stream, User& user) {
  int n;
  stream >> user._id;
  stream.ignore();
  getline(stream, user.username);
  getline(stream, user.password);
  stream >> n;
  user.userType = static_cast<User::Type>(n);

  if (user.userType == User::Type::STUDENT) {
    string studentID;
    stream >> studentID;
    user.pStudent = *App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->_id == studentID; });
  }
  if (user.userType == User::Type::ACADEMIC_STAFF) {
    string staffID;
    stream >> staffID;
    user.pStaff = *App::pStaffs.find_if(
        [&](const auto& p) -> bool { return p->_id == staffID; });
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
  if (user.userType == User::Type::ACADEMIC_STAFF)
    stream << user.pStaff->_id << '\n';
  return stream;
}

void User::login() {
  Console::clear();
  List<User*>::iterator it;
  cout << "Username: ";
  string username;
  cin >> username;
  cout << "Password: ";
  string password;
  cin >> password;
  if (username == "admin" && password == "admin") {
    App::pCurrentUser = new User("admin", "admin", User::Type::ADMIN);
  } else {
    it = App::pUsers.find_if([&](User* const& user) {
      return username == user->username && password == user->password;
    });
    if (it == App::pUsers.end()) {
      cout << "Incorrect username or password!\n";
      Utils::waitForKeypress();
      Menu::welcome();
      return;
    }
    App::pCurrentUser = *it;
  }
  cout << "Successfully logged in\n";
  if (App::pCurrentUser->userType == User::Type::ACADEMIC_STAFF) {
    Menu::staffMenu();
    return;
  }
  if (App::pCurrentUser->userType == User::Type::STUDENT) {
    Menu::studentMenu();
    return;
  }
  if (App::pCurrentUser->userType == User::Type::ADMIN) {
    Menu::adminMenu();
    return;
  }
}

void User::changePassword() {
  Console::clear();
  Utils::getCurrentSemester();
  string tmpPass;
  Utils::printLine();
  cout << "Input current password: ";
  cin.ignore();
  getline(cin, tmpPass);
  if (tmpPass == this->password) {
    Utils::printLine();
    cout << "Input new password: ";
    getline(cin, this->password);
    Utils::printLine();
    cout << "Successfully changed information\n";
    App::pCurrentUser = nullptr;
    Utils::waitForKeypress();
    User::login();
  } else {
    cout << "Wrong password!\n";
    Utils::waitForKeypress();
    if (this->userType == User::Type::ACADEMIC_STAFF) {
      Menu::staffMenu();
      return;
    }
    if (this->userType == User::Type::STUDENT) {
      Menu::studentMenu();
      return;
    }
  }
}

void User::displayUser() {
  List<string> type = {"Admin", "Student", "Staff"};
  cout << this->username << " - " << this->password << " - "
       << type[this->userType] << '\n';
}
