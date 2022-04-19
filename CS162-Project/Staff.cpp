#include "Staff.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Staff& staff) {
  stream >> staff._id;
  stream.ignore();
  getline(stream, staff.staffCode);
  getline(stream, staff.lastName);
  getline(stream, staff.firstName);
  getline(stream, staff.gender);
  getline(stream, staff.dateOfBirth);
  getline(stream, staff.socialID);
  getline(stream, staff.faculty);
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Staff& staff) {
  stream << staff._id << '\n';
  stream << staff.staffCode << '\n';
  stream << staff.lastName << '\n';
  stream << staff.firstName << '\n';
  stream << staff.gender << '\n';
  stream << staff.dateOfBirth << '\n';
  stream << staff.socialID << '\n';
  stream << staff.faculty << '\n';
  return stream;
}

void Staff::updateStaffInfo() {
  Console::clear();
  cout << "----------------------------------------\n";
  cout << "1. Staff last name: " << this->lastName << "\n";
  cout << "2. Staff first name: " << this->firstName << "\n";
  cout << "3. Gender: " << this->gender << "\n";
  cout << "4. Day of birth: " << this->dateOfBirth << "\n";
  cout << "5. Social ID: " << this->socialID << "\n";
  cout << "6. faculty: " << this->faculty << "\n";
  cout << "----------------------------------------\n";
  cout << "0. Return\n";
  cout << "Which one do you want to update?\n";
  int option = Utils::getOption(0, 6);
  switch (option) {
    case 0: {
      Menu::staffMenu();
      return;
    }

    case 1: {
      cout << "-------------------\n";
      cout << "New last name: ";
      cin.ignore();
      getline(cin, this->lastName);
      break;
    }
    case 2: {
      cout << "-------------------\n";
      cout << "New first name: ";
      cin.ignore();
      getline(cin, this->firstName);
      break;
    }
    case 3: {
      cout << "-------------------\n";
      cout << "New gender: ";
      cin.ignore();
      getline(cin, this->gender);
      break;
    }
    case 4: {
      cout << "-------------------\n";
      cout << "New day of birth: ";
      cin.ignore();
      getline(cin, this->dateOfBirth);
      break;
    }
    case 5: {
      cout << "-------------------\n";
      cout << "New social ID: ";
      cin.ignore();
      getline(cin, this->socialID);
      break;
    }
    case 6: {
      cout << "-------------------\n";
      cout << "New faculty: ";
      cin.ignore();
      getline(cin, this->faculty);
      break;
    }
  }
  cout << "\nSuccessfully changed information!\n";

  Utils::waitForKeypress();
  Menu::staffMenu();
}

void Staff::displayStaff() {
  cout << this->staffCode << " - " << this->lastName << ' ' << this->lastName
       << " - " << this->gender << " - " << this->dateOfBirth << " - "
       << this->socialID << " - " << this->faculty << '\n';
}

void Staff::createStaff() {
  Console::clear();
  string staffCode, firstName, lastName, gender, dateOfBirth, socialID, faculty;
  cin.ignore();
  cout << "Input staff code: ";
  getline(cin, staffCode);
  cout << "Input last name: ";
  getline(cin, lastName);
  cout << "Input first name: ";
  getline(cin, firstName);
  cout << "Input gender: ";
  getline(cin, gender);
  cout << "Input date of birth: ";
  getline(cin, dateOfBirth);
  cout << "Input social ID: ";
  getline(cin, socialID);
  cout << "Input faculty: ";
  getline(cin, faculty);
  Staff* pStaff = new Staff();
  User* pUser = new User();
  pStaff->staffCode = staffCode;
  pStaff->lastName = lastName;
  pStaff->firstName = firstName;
  pStaff->gender = gender;
  pStaff->dateOfBirth = dateOfBirth;
  pStaff->socialID = socialID;
  pStaff->faculty = faculty;
  pUser->userType = User::Type::ACADEMIC_STAFF;
  pUser->username = staffCode;
  pUser->password = "123456";
  pUser->pStaff = pStaff;
  App::pStaffs.push_back(pStaff);
  App::pUsers.push_back(pUser);
  cout << "Created successfully\n";
  Utils::waitForKeypress();
  Menu::adminMenu();
}