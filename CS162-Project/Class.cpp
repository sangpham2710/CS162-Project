#include "Class.h"

#include "App.h"
#include "Console.h"

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

static void view() {
  int i = 1;
  for (const auto& p : App::pClasses) {
    cout << i << ". " << p << endl;
    ++i;
  }
  cout << i + 1 << ". "
       << " Create class " << endl;
  cout << "0. Go back" << endl;

  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  choose(choice, i);
}

static void create() {
  Class* pClass = new Class();
  cout << "Input class code: ";
  getline(cin, pClass->classCode);

  // Check duplicate class
  for (auto crs : App::pClasses) {
    if (crs->classCode == pClass->classCode) {
      cout << "This class is already available!";
      delete pClass;
      return;
    }
  }

  App::pClasses.push_back(pClass);
  App::pCurrentSemester->pSchoolYear->pClasses.push_back(pClass);
}

static void choose(const int& choice, const int& i) {
  if (choice == i + 1) {
    create();
  } 
  else if (choice <= i) {
    viewEditClass(App::pClasses[i]);
  } else {
    cout << "This Class does not exist";
  }
}

static void viewEditClass(Class* classEditCode) {
  Console::clear();
  cout << "Class: " << classEditCode->classCode << endl;
  cout << "--------------------------" << endl;
  cout << "1. Update Class" << endl;
  cout << "2. Delete Class" << endl;
  cout << "3. View List Students" << endl;
  cout << "4. View Scoreboard" << endl;
  cout << "5. Export Scoreboard of students" << endl;
  cout << "6. Export list students in class" << endl;
  cout << "--------------------------" << endl;
  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  if (choice == 1) {
    // updateClass(classEditCode);
  } else if (choice == 2) {
    // deleteClass(classEditCode);
  } else if (choice == 3) {
    // viewListStudents(classEditCode);
  } else if (choice == 4) {
    // viewScoreboardClass(classEditCode);
  } else if (choice == 5) {
    // exportScoreboardStudents(classEditCode);
  } else if (choice == 6) {
    // exportListStudents(classEditCode);
  }
}

static void updateClass(string classEditCode) { Console::clear(); }

static void deleteClass(string classEditCode) {
  for (auto p : App::pClasses) {
    if (p->classCode == classEditCode) {
      App::pClasses.remove(p);
      cout << "Class " << classEditCode << " has been deleted successfully!";
      break;
    }
  }
}