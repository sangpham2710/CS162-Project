#pragma once

#include <string>

#include "ID.h"
#include "Student.h"

using std::string;

class Student;

class User {
 public:
  enum Type { ADMIN, STUDENT, ACADEMIC_STAFF };
  string _id;
  string username;
  string password;
  Type userType;

  Student* pStudent;

  User() : _id(ID::gen()), username(""), password(""), userType(ADMIN) {}
  User(const string& username, const string& password, const Type& userType)
      : _id(ID::gen()),
        username(username),
        password(password),
        userType(userType) {}

  friend std::ostream& operator<<(std::ostream& stream, const User& user);
  static void login();
};