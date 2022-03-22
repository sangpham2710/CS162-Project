#pragma once

#include <string>
using std::string;

class User {
 protected:
  string username;
  string password;
  User(string _username, string _password)
      : username(_username), password(_password) {}
};