#include "Class.h"

#include "App.h"
#include "Console.h"
#include "Menu.h"

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
  cout << "1. Change class code" << endl;
  cout << "2. Add one student" << endl;
  cout << "--------------------" << endl;
  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  cin.ignore();
  if (choice == 1) {
    string classCode;
    cout << "New class code: ";
    getline(cin, classCode);
    this->classCode = classCode;
  } else if (choice == 2) {
    // addStudent()
  } else {
    cout << "Invalid choice!" << endl;
  }
}

void Class::deleteClass() {
  App::pCurrentSemester->pSchoolYear->pClasses.remove_if(
      [&](const auto& p) { return p->classCode == this->classCode; });
  auto pDeletingClass = *App::pClasses.find_if(
      [&](const auto& p) { return p->classCode == this->classCode; });
  cout << "Class " << this->classCode << " has been deleted successfully!";

  // NOT IMPLEMENTED: delete pClass of all students in the class

  App::pClasses.remove(pDeletingClass);
  delete pDeletingClass;
}

void Class::viewListStudents() {
  for (const auto& p : this->pStudents) {
    cout << p->firstName << " " << p->lastName << endl;
  }
}

void Class::viewScoreboardClass() {
  for (const auto& p : this->pStudents) {
    // Print name + scoreboard of each student

    // calculate semester GPA and overall GPA
  }
}

void Class::viewEditClass() {
  Console::clear();
  cout << "Class: " << this->classCode << endl;
  cout << "--------------------------" << endl;
  cout << "1. Update Class" << endl;
  cout << "2. Delete Class" << endl;
  cout << "3. View List Students" << endl;
  cout << "4. View Scoreboard" << endl;
  cout << "5. Export Scoreboard of students" << endl;
  cout << "6. Export list students in class" << endl;
  cout << "0. Go back" << endl;
  cout << "--------------------------" << endl;
  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  if (choice == 1) {
    this->updateClass();
  } else if (choice == 2) {
    this->deleteClass();
  } else if (choice == 3) {
    this->viewListStudents();
  } else if (choice == 4) {
    // viewScoreboardClass(classEditCode);
  } else if (choice == 5) {
    // exportScoreboardStudents(classEditCode);
  } else if (choice == 6) {
    // exportListStudents(classEditCode);
  } else if (choice == 0) {
    Class::viewMainMenu();
  } else {
    cout << "Invalid choice!";
  }
}

void Class::create() {
  Class* pClass = new Class();
  cin.ignore();
  cout << "Input class code: ";
  getline(cin, pClass->classCode);

  // Check duplicate class
  for (auto p : App::pClasses) {
    if (p->classCode == pClass->classCode) {
      cout << "This class is already available!";
      delete pClass;
      return;
    }
  }
  App::pClasses.push_back(pClass);
  App::pCurrentSemester->pSchoolYear->pClasses.push_back(pClass);
}

void Class::choose(const int& choice, const int& i) {
  if (choice == i) {
    Class::create();
  } else if (choice < i && choice >= 0) {
    App::pClasses[choice]->viewEditClass();
  } else if (choice == -1) {
    Menu::staffMenu();
  } else {
    cout << "This Class does not exist";
  }
}

void Class::viewMainMenu() {
  Console::clear();
  int i = 0;
  for (const auto& p : App::pClasses) {
    ++i;
    cout << i << ". " << p->classCode << endl;
  }
  cout << i + 1 << ". "
       << "Create class " << endl;
  cout << "0. Go back" << endl;

  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  Class::choose(choice - 1, i);
}
