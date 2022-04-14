#include "Class.h"

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

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
      this->classUpdateMenu();
      return;
    }
    case 1: {
      string classCode;
      cout << "New class code: ";
      getline(cin, classCode);
      this->classCode = classCode;
      cout << "Successfully updated!\n";
      Utils::waitForKeypress();
      this->classUpdateMenu();
      return;
    }
    case 2: {
      // addStudent()
      break;
    }
  }
}

void Class::deleteClass() {
  Console::clear();
  cout << "Are you sure?, " << this->classCode << " will be deleted in "
       << App::pCurrentSemester->pSchoolYear->yearName << '\n';
  cout << "1. Yes\n";
  cout << "2. No\n \n";

  int option = Utils::getOption(1, 2);
  if (option == 2) {
    this->classUpdateMenu();
    return;
  }
  App::pStudents.for_each([&](const auto& p) {
    if (p->pClass->classCode == this->classCode) p->pClass = nullptr;
  });
  App::pCurrentSemester->pSchoolYear->pClasses.remove_if(
      [&](const auto& p) { return p->classCode == this->classCode; });
  auto itDeletingClass = App::pClasses.find_if(
      [&](const auto& p) { return p->classCode == this->classCode; });
  cout << "Class " << this->classCode << " has been deleted successfully!";
  delete *itDeletingClass;
  App::pClasses.remove(itDeletingClass);
  Utils::waitForKeypress();
  Class::viewMainMenu();
}

void Class::viewStudents() {
  Console::clear();
  cout << "List students of class " << this->classCode << '\n';
  for (const auto& p : this->pStudents) {
    cout << p->studentCode << ' ' << p->firstName << ' ' << p->lastName << '\n';
  }
  Utils::waitForKeypress();
  Class::viewMainMenu();
}

void Class::viewScoreboard() {
  for (const auto& p : this->pStudents) {
    // Print name + scoreboard of each student

    // calculate semester GPA and overall GPA
  }
}

void Class::classUpdateMenu() {
  Console::clear();
  cout << "Class: " << this->classCode << '\n';
  cout << "--------------------------" << '\n';
  cout << "1. Update Class" << '\n';
  cout << "2. Delete Class" << '\n';
  cout << "3. View List Students" << '\n';
  cout << "4. View Scoreboard" << '\n';
  cout << "5. Export Scoreboard of students" << '\n';
  cout << "6. Export list students in class" << '\n';
  cout << "0. Go back" << '\n';
  cout << "--------------------------" << '\n';
  int option = Utils::getOption(0, 6);
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
      this->deleteClass();
      break;
    }
    case 3: {
      this->viewStudents();
      break;
    }
    case 4: {
      // viewScoreboardClass(classEditCode);
      break;
    }
    case 5: {
      // exportScoreboardStudents(classEditCode);
      break;
    }
    case 6: {
      // exportListStudents(classEditCode);
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
    App::pClasses[option - 1]->classUpdateMenu();
  } else {
    Menu::staffMenu();
    return;
  }
}
