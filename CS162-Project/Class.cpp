#include "Class.h"

#include "App.h"

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
  cout << "1. Create class" << endl;
  cout << "2. Choose class" << endl;
  cout << "0. Go back" << endl;

  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  choose(choice);
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
}

static void choose(int choice) {
  if (choice == 1) {
    create();
  } 
  else if (choice == 2) 
  {
      //system("cls");

    string classEditCode;
      bool check = false; //check if class available

    cout << "Input code of the class you want to edit: ";
    getline(cin, classEditCode);
    for (const auto& p : App::pClasses) {
      if (p->classCode == classEditCode) {
        check = true;
        break;
      }
    }

    if (check) {
      viewEditClass();
    } else {
      cout << "This class does not exist!";
    }
  }
}

static void viewEditClass() {

}