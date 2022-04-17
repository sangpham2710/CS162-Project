#include "Class.h"

#include <fstream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

using std::ifstream;
using std::ofstream;

std::istream& operator>>(std::istream& stream, Class& _class) {
  int n;
  stream >> _class._id;
  stream.ignore();
  getline(stream, _class.classCode);
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string studentID;
    stream >> studentID;
    _class.pStudents.push_back(*App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->_id == studentID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Class& _class) {
  stream << _class._id << '\n';
  stream << _class.classCode << '\n';
  stream << _class.pStudents.size() << '\n';
  for (const auto& p : _class.pStudents) stream << p->_id << '\n';
  return stream;
}

void Class::updateClass() {
  Console::clear();
  cout << "1. Change class code" << '\n';
  cout << "2. Add one student" << '\n';
  cout << "--------------------" << '\n';
  cout << "0. Return\n";
  int option = Utils::getOption(0, 2);

  switch (option) {
    case 0: {
      this->classChooseMenu();
      return;
    }
    case 1: {
      string classCode;
      cout << "New class code: ";
      getline(cin, classCode);
      this->classCode = classCode;
      cout << "Successfully updated!\n";
      Utils::waitForKeypress();
      this->classChooseMenu();
      return;
    }
    case 2: {
      this->addStudent();
      break;
    }
  }
}

void Class::addStudent() {
  string studentCode, firstName, lastName, gender, dateOfBirth, socialID,
      classCode;
  cin.ignore();
  cout << "Input student ID: ";
  getline(cin, studentCode);
  auto itStudent = App::pStudents.find_if(
      [&](const auto& p) -> bool { return p->studentCode == studentCode; });
  if (itStudent != App::pStudents.end()) {
      (*itStudent)->pClass = this;
      cout << "Successfully added student\n";     
      Utils::waitForKeypress();
      this->updateClass();
      return;
  }
  cout << "Input first name: ";
  getline(cin, firstName);
  cout << "Input last name: ";
  getline(cin, lastName);
  cout << "Input gender (Male/Female): ";
  getline(cin, gender);
  cout << "Input date of birth: ";
  getline(cin, dateOfBirth);
  cout << "Input social ID: ";
  getline(cin, socialID);
  Student* pStudent = new Student();
  User* pUser = new User();
  pStudent->studentCode = studentCode;
  pStudent->firstName = firstName;
  pStudent->lastName = lastName;
  pStudent->gender = gender;
  pStudent->dateOfBirth = dateOfBirth;
  pStudent->socialID = socialID;
  pStudent->pClass = this;
  pStudent->pUser = pUser;

  pUser->username = studentCode;
  pUser->password = "123456";
  pUser->userType = User::Type::STUDENT;
  pUser->pStudent = pStudent;

  this->pStudents.push_back(pStudent);
  App::pStudents.push_back(pStudent);
  App::pUsers.push_back(pUser);
  cout << "Successfully added student\n";
  Utils::waitForKeypress();
  this->updateClass();
}

void Class::deleteClassScene() {
  Console::clear();
  cout << "Are you sure?, " << this->classCode << " will be deleted in "
       << App::pCurrentSemester->pSchoolYear->yearName << '\n';
  cout << "1. Yes\n";
  cout << "2. No\n \n";

  int option = Utils::getOption(1, 2);
  if (option == 2) {
    this->classChooseMenu();
    return;
  }
  string tmp = this->classCode;
  this->deleteClass();
  cout << "Class " << tmp << " has been deleted successfully!\n";

  Utils::waitForKeypress();
  Class::viewMainMenu();
}

void Class::deleteClass() {
    App::pStudents.for_each([&](const auto& p) {
        if (p->pClass->classCode == this->classCode) p->pClass = nullptr;
        });
    App::pCurrentSemester->pSchoolYear->pClasses.remove_if(
        [&](const auto& p) { return p->classCode == this->classCode; });
    auto itDeletingClass = App::pClasses.find_if(
        [&](const auto& p) { return p->classCode == this->classCode; });

    delete* itDeletingClass;
    App::pClasses.remove(itDeletingClass);
}

void Class::viewStudents() {
  Console::clear();
  cout << "List students of class " << this->classCode << '\n';
  for (const auto& p : this->pStudents) {
    cout << p->studentCode << ' ' << p->lastName << ' ' << p->firstName << '\n';
  }
  Utils::waitForKeypress();
  this->classChooseMenu();
}

void Class::viewScoreboard() {
  Console::clear();
  for (const auto& p : this->pStudents) {
    cout << p->studentCode << ' ' << p->lastName << ' ' << p->firstName << '\n';
    p->courseMarks.for_each([](const auto& courseMark) {
      if (courseMark.pCourse->pSemester->_id == App::pCurrentSemester->_id) {
        cout << courseMark.pCourse->courseCode << ' ';
        cout << courseMark.totalMark << "; ";
      }
    });
    cout << '\n';
    cout << "Semester GPA: " << p->getSemesterGPA() << "; "
         << "Overall GPA: " << p->getOverallGPA() << '\n';
    cout << string(20, '-') << '\n';
  }
  Utils::waitForKeypress();
  this->classChooseMenu();
}

void Class::classChooseMenu() {
  Console::clear();
  cout << "Class: " << this->classCode << '\n';
  cout << "--------------------------" << '\n';
  cout << "1. Update class" << '\n';
  cout << "2. Delete class" << '\n';
  cout << "3. View list students" << '\n';
  cout << "4. View scoreboard" << '\n';
  cout << "5. Import list new students to class" << '\n';
  cout << "6. Export scoreboard of students" << '\n';
  cout << "7. Export list students in class" << '\n';
  cout << "0. Go back" << '\n';
  cout << "--------------------------" << '\n';
  int option = Utils::getOption(0, 7);
  switch (option) {
    case 0: {
      Class::viewMainMenu();
      return;
    }
    case 1: {
      this->updateClass();
      break;
    }
    case 2: {
      this->deleteClassScene();
      break;
    }
    case 3: {
      this->viewStudents();
      break;
    }
    case 4: {
      this->viewScoreboard();
      break;
    }
    case 5: {
      this->importNewStudents();
      break;
    }
    case 6: {
      this->exportScoreboard();
      break;
    }
    case 7: {
      this->exportStudents();
      break;
    }
  }
}

void Class::createClass() {
  cout << "This class will be created in "
       << App::pCurrentSemester->pSchoolYear->yearName << '\n';
  cout << "Input class code: ";
  string classCode;
  cin.ignore();
  getline(cin, classCode);

  if (App::pClasses.find_if([&](const auto& p) -> bool {
        return p->classCode == classCode;
      }) != App::pClasses.end()) {
    cout << "This class already exists!";
    Class::viewMainMenu();
    return;
  }

  Class* pClass = new Class();
  pClass->classCode = classCode;
  App::pClasses.push_back(pClass);
  App::pCurrentSemester->pSchoolYear->pClasses.push_back(pClass);
  Class::viewMainMenu();
}

void Class::viewMainMenu() {
  Console::clear();
  int i = 1;
  for (const auto& p : App::pClasses) {
    cout << i << ". " << p->classCode << '\n';
    ++i;
  }
  cout << i << ". "
       << "Create class " << '\n';
  cout << "0. Go back" << '\n';

  int option = Utils::getOption(0, i);
  if (option == i) {
    Class::createClass();
  } else if (0 < option && option < i) {
    App::pClasses[option - 1]->classChooseMenu();
  } else {
    Menu::staffMenu();
    return;
  }
}

void Class::exportScoreboard() {
  Console::clear();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ofstream ofs(path);
  if (!ofs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    Course::courseMainMenu();
    return;
  }
  int no = 0;
  string line;
  line = CSV::writeLine("No", "Student ID", "Last Name", "First Name",
                        "Semester GPA", "Overall GPA");
  ofs << line << '\n';
  for (const auto& p : this->pStudents) {
    line = CSV::writeLine(++no, p->studentCode, p->lastName, p->firstName,
                          p->getSemesterGPA(), p->getOverallGPA());
    ofs << line << '\n';
  }
  ofs.close();
  cout << "Exported successfully\n";
  Utils::waitForKeypress();
  this->classChooseMenu();
}

void Class::exportStudents() {
  Console::clear();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ofstream ofs(path);
  if (!ofs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->classChooseMenu();
    return;
  }
  int no = 0;
  string line;
  line = CSV::writeLine("No", "Student ID", "Last Name", "First Name", "Gender",
                        "Date of birth", "Social ID");
  ofs << line << '\n';
  for (const auto& p : this->pStudents) {
    line = CSV::writeLine(++no, p->studentCode, p->lastName, p->firstName,
                          p->gender, p->dateOfBirth, p->socialID);
    ofs << line << '\n';
  }
  ofs.close();
  cout << "Exported successfully\n";
  Utils::waitForKeypress();
  this->classChooseMenu();
}

void Class::importNewStudents() {
  Console::clear();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ifstream ifs(path);
  if (!ifs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->classChooseMenu();
    return;
  }
  string line;
  getline(ifs, line);
  while (getline(ifs, line)) {
    int no;
    string studentCode, lastName, firstName, gender, dateOfBirth, socialID;
    CSV::readLine(line, no, studentCode, lastName, firstName, gender,
                  dateOfBirth, socialID);
    auto itStudent = App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->studentCode == studentCode; });
    if (itStudent != App::pStudents.end()) {
      (*itStudent)->pClass = this;
      continue;
    }
    Student* pStudent = new Student();
    User* pUser = new User();
    pStudent->studentCode = studentCode;
    pStudent->lastName = lastName;
    pStudent->firstName = firstName;
    pStudent->gender = gender;
    pStudent->dateOfBirth = dateOfBirth;
    pStudent->socialID = socialID;
    pStudent->pClass = this;
    pStudent->pUser = pUser;

    pUser->userType = User::Type::STUDENT;
    pUser->username = studentCode;
    pUser->password = "123456";
    pUser->pStudent = pStudent;

    this->pStudents.push_back(pStudent);
    App::pStudents.push_back(pStudent);
    App::pUsers.push_back(pUser);
  }
  ifs.close();
  cout << "Imported successfully\n";
  Utils::waitForKeypress();
  this->classChooseMenu();
}