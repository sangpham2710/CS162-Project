#pragma once

#include <string>

#include "ID.h"
#include "Staff.h"
#include "Student.h"

using std::string;

class Student;
class Staff;

class User {
 public:
  enum Type { ADMIN, STUDENT, ACADEMIC_STAFF };
  string _id;
  string username;
  string password;
  Type userType;

  Student* pStudent;
  Staff* pStaff;

  User(const string& id)
      : _id(id),
        username{},
        password{},
        userType{},
        pStudent{nullptr},
        pStaff{nullptr} {}
  User() : _id{ID::gen()} {}
  User(const string& username, const string& password, const Type& userType)
      : _id{ID::gen()},
        username{username},
        password{password},
        userType{userType} {}
  friend std::istream& operator>>(std::istream& stream, User& user);
  friend std::ostream& operator<<(std::ostream& stream, const User& user);
  static void login();
  void changePassword();

  void displayUser();
};