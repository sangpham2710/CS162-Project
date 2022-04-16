#include "Student.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Utils.h"
#include "Menu.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Student& student) {
  int n;
  stream >> student._id;
  stream.ignore();
  getline(stream, student.studentCode);
  getline(stream, student.lastName);
  getline(stream, student.firstName);
  getline(stream, student.gender);
  getline(stream, student.dateOfBirth);
  getline(stream, student.socialID);
  string classID;

  stream >> classID;
  student.pClass = *App::pClasses.find_if(
      [&](const auto& p) -> bool { return p->_id == classID; });
  string userID;
  stream >> userID;
  student.pUser = *App::pUsers.find_if(
      [&](const auto& p) -> bool { return p->_id == userID; });

  stream >> n;
  for (int i = 0; i < n; ++i) {
    CourseMark tmp;
    stream >> tmp;
    student.courseMarks.push_back(tmp);
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Student& student) {
  stream << student._id << '\n';
  stream << student.studentCode << '\n';
  stream << student.lastName << '\n';
  stream << student.firstName << '\n';
  stream << student.gender << '\n';
  stream << student.dateOfBirth << '\n';
  stream << student.socialID << '\n';
  stream << student.pClass->_id << '\n';
  stream << student.pUser->_id << '\n';
  stream << student.courseMarks.size() << '\n';
  for (const auto& courseMark : student.courseMarks) stream << courseMark;
  return stream;
}

double Student::getSemesterGPA() {
  auto currentSemesterCourseMarks =
      this->courseMarks.filter([&](const auto& courseMark) -> bool {
        return courseMark.pCourse->pSemester->_id == App::pCurrentSemester->_id;
      });
  if (currentSemesterCourseMarks.empty()) return -1;
  return currentSemesterCourseMarks
             .map<double>([&](const auto& courseMark) -> double {
               return courseMark.finalMark;
             })
             .reduce([&](const auto& sum, const auto& mark) -> double {
               return sum + mark;
             }) /
         (double)currentSemesterCourseMarks.size();
}

double Student::getOverallGPA() {
  if (this->courseMarks.empty()) return -1;
  return this->courseMarks
             .map<double>([&](const auto& courseMark) -> double {
               return courseMark.finalMark;
             })
             .reduce([&](const auto& sum, const auto& mark) -> double {
               return sum + mark;
             }) /
         (double)this->courseMarks.size();
}

void Student::updateStudentInfo() { Console::clear();
  cout << "----------------------------------------\n";
  cout << "1. Student last name: " << this->lastName << "\n";
  cout << "2. Student first name: " << this->firstName << "\n";
  cout << "3. Gender: " << this->gender << "\n";
  cout << "4. Day of birth: " << this->dateOfBirth << "\n";
  cout << "5. Social ID: " << this->socialID << "\n";
  cout << "----------------------------------------\n";
  cout << "0. Return\n";
  cout << "Which one do you want to update?\n";
  int option = Utils::getOption(0, 5);
  switch (option) {
    case 0: {
      Menu::studentMenu();
      break;
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
  }
  cout << "\nSuccessfully changed information!\n";

  Utils::waitForKeypress();
  Menu::studentMenu();
}

void Student::viewStudentScoreboard() {
  Console::clear();
  cout << "Student code: " << this->studentCode << "\n";
  cout << "Student name: " << this->lastName << " " << this->firstName << "\n";
  cout << "-----------------------\n";
  for (auto p : this->courseMarks) {
    cout << p.pCourse->courseCode << "-" << p.pCourse->courseName << "\n";
    cout << "Midterm: " << p.midtermMark << "\n";
    cout << "Final: " << p.finalMark << "\n";
    cout << "Other: " << p.otherMark << "\n";
    cout << "Total: " << p.totalMark << "\n";
    cout << "------------------------------------\n";
  }
  Utils::waitForKeypress();
  Menu::studentMenu();
}
