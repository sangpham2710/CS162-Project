#pragma once

#include <string>

#include "ID.h"

using std::string;

enum UserType { ADMIN, STUDENT, ACADEMIC_STAFF };

class User {
 public:
  string _id;
  string username;
  string password;
  UserType userType;
  User() : _id(ID::gen()), username(""), password(""), userType(ADMIN) {}
  User(string _username, string _password, UserType _userType)
      : _id(ID::gen()),
        username(_username),
        password(_password),
        userType(_userType) {}
};