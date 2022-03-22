#pragma once
#include <string>
using namespace std;

class Account {
 protected:
  string username;
  string password;
  string typeOfAccount;
  Account(string _username, string _password, string _typeOfAccount)
      : username(_username),
        password(_password),
        typeOfAccount(_typeOfAccount) {}
};