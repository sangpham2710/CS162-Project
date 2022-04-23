#include "Student.h"

#include <iomanip>
#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

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

void Student::viewEnrolledCourses() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "All enrolled courses: \n";
  auto recentSemesterCourseMarks =
      this->courseMarks.filter([&](const auto& courseMark) -> bool {
        return courseMark.pCourse->pSemester->_id == App::pRecentSemester->_id;
      });
  for (const auto& courseMark : recentSemesterCourseMarks) {
    cout << courseMark.pCourse->courseCode << " - "
         << courseMark.pCourse->courseName << '\n';
  }
  Utils::waitForKeypress();
  Menu::studentMenu();
}

void Student::enrollUnenrollCourseScene() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  if (!App::courseRegistrationSession.isOpen()) {
    cout << "The course registration is not open right now!\n";
    Utils::waitForKeypress();
    Menu::studentMenu();
    return;
  }
  cout << "Course registration session is opened!\n";
  cout << "From: ";
  App::courseRegistrationSession.startTime.output();
  cout << '\n';
  cout << "To: ";
  App::courseRegistrationSession.endTime.output();
  cout << '\n';
  int i = 1;
  for (const auto& pCourse : App::pRecentSemester->pCourses) {
    auto itCourseMark =
        this->courseMarks.find_if([&](const auto& courseMark) -> bool {
          return courseMark.pCourse->_id == pCourse->_id;
        });
    if (itCourseMark != this->courseMarks.end()) {
      cout << i << ". " << pCourse->courseCode << " - " << pCourse->courseName
           << '\t' << "ENROLLED\n";
    } else {
      cout << i << ". " << pCourse->courseCode << " - " << pCourse->courseName
           << '\t' << "UNENROLLED\n";
    }
    ++i;
  }
  cout << "0. Return\n\n";
  cout << "Please choose the course that you want to enroll/unenroll\n";
  int option = Utils::getOption(0, i);
  if (option == 0) {
    Menu::studentMenu();
    return;
  } else {
    App::pRecentSemester->pCourses[option - 1]->enrollUnenrollCourse();
    return;
  }
}

void Student::updateStudentInfo() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Last name: " << this->lastName << "\n";
  cout << "2. First name: " << this->firstName << "\n";
  cout << "3. Gender: " << this->gender << "\n";
  cout << "4. Day of birth: " << this->dateOfBirth << "\n";
  cout << "5. Social ID: " << this->socialID << "\n";
  Utils::printLine();
  cout << "0. Return\n\n";
  cout << "Which one do you want to update?\n";
  int option = Utils::getOption(0, 5);
  switch (option) {
    case 0: {
      Menu::studentMenu();
      return;
    }
    case 1: {
      Utils::printLine();
      cout << "New last name: ";
      cin.ignore();
      getline(cin, this->lastName);
      break;
    }
    case 2: {
      Utils::printLine();
      cout << "New first name: ";
      cin.ignore();
      getline(cin, this->firstName);
      break;
    }
    case 3: {
      Utils::printLine();
      cout << "New gender: ";
      cin.ignore();
      getline(cin, this->gender);
      break;
    }
    case 4: {
      Utils::printLine();
      cout << "New day of birth: ";
      cin.ignore();
      getline(cin, this->dateOfBirth);
      break;
    }
    case 5: {
      Utils::printLine();
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
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "Student code: " << this->studentCode << "\n";
  cout << "Student name: " << this->lastName << " " << this->firstName << "\n";
  Utils::printLine();
  for (auto p : this->courseMarks) {
    cout << p.pCourse->courseCode << "-" << p.pCourse->courseName << "\n";
    cout << "Midterm: " << p.midtermMark << "\n";
    cout << "Final: " << p.finalMark << "\n";
    cout << "Other: " << p.otherMark << "\n";
    cout << "Total: " << p.totalMark << "\n";
    Utils::printLine();
  }
  Utils::waitForKeypress();
  Menu::studentMenu();
}

using std::setfill;
using std::setw;

void Student::viewSchedule() {
  Console::clear();
  List<string> weekdays = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
  cout << setw(10) << setfill(' ') << left << "";

  auto recentSemesterCourses =
      this->courseMarks
          .filter([&](const auto& courseMark) -> bool {
            return courseMark.pCourse->pSemester->_id ==
                   App::pRecentSemester->_id;
          })
          .map<Course*>([&](const auto& courseMark) -> Course* {
            return courseMark.pCourse;
          });

  for (const auto& weekday : weekdays)
    cout << setw(10) << setfill(' ') << weekday;
  cout << '\n';
  for (int session = 1; session <= 4; ++session) {
    string tmp = "S";
    tmp += (char)(session + '0');
    cout << setw(10) << setfill(' ') << left << tmp;
    for (int weekday = 2; weekday <= 8; ++weekday) {
      auto itCourse = recentSemesterCourses.find_if([&](const auto& p) -> bool {
        return p->session1 == weekday * 10 + session ||
               p->session2 == weekday * 10 + session;
      });
      if (itCourse != recentSemesterCourses.end()) {
        cout << setw(10) << setfill(' ') << left << (*itCourse)->courseCode;
      } else {
        cout << setw(10) << setfill(' ') << left << "";
      }
    }
    cout << '\n';
  }


  Utils::waitForKeypress();
  Menu::studentMenu();
}

void Student::displayStudent() {
  Utils::printLine();
  cout << this->studentCode << " - " << this->lastName << ' ' << this->lastName
       << " - " << this->gender << " - " << this->dateOfBirth << " - "
       << this->socialID << '\n';
  cout << "Class: " << this->pClass->classCode << '\n';
  cout << "Enrolled in " << this->courseMarks.size() << " courses\n";
}