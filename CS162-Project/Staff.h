#pragma once
#pragma once
#include <string>

#include "ID.h"
#include "User.h"

using std::string;

class Staff {
 public:
  string _id;
  string staffCode;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;
  string falcuty;
  Staff(const string& id)
      : _id{id},
        staffCode{},
        firstName{},
        lastName{},
        gender{},
        dateOfBirth{},
        socialID{},
        falcuty{} {}
  Staff() : Staff(ID::gen()) {}

  friend std::istream& operator>>(std::istream& stream, Staff& staff);
  friend std::ostream& operator<<(std::ostream& stream, const Staff& staff);

  void updateStaffInfo();
};
