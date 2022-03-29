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
    std::cout << i << ". " << p << std::endl;
    ++i;
  }
  std::cout << "C. Create class";
  std::cout << "Choose class"
}

static void create() {
  Class* pClass = new Class();
  std::cout << "Input class code: ";
  getline(std::cin, pClass->classCode);
  App::pClasses.push_back(pClass);
}

static void choose() {

}