#pragma once

#include <string>
using std::string;

enum UserType {
    ADMIN,
    STUDENT,
    ACADEMIC_STAFF
};

class User {
 public:
  string username;
  string password;
  bool userType; 
  User() : username(""), password(""), userType(ADMIN) {}
  User(string _username, string _password, UserType _userType)
      : username(_username), password(_password), userType(_userType) {}
};