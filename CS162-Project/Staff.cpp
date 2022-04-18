#include "Staff.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Staff& staff) {
  int n;
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