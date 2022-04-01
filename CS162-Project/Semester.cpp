#include "Semester.h"

#include <iostream>

#include "App.h"
#include "SchoolYear.h"
#include "Console.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Semester& semester) {
  int n;
  stream >> semester._id;
  stream.ignore();
  getline(stream, semester.semesterName);
  string schoolYearID;
  stream >> schoolYearID;
  semester.pSchoolYear = *App::pSchoolYears.find_if(
      [&](const auto& p) -> bool { return p->_id == schoolYearID; });
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string courseID;
    stream >> courseID;
    semester.pCourses.push_back(*App::pCourses.find_if(
        [&](const auto& p) -> bool { return p->_id == courseID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Semester& semester) {
  stream << semester._id << '\n';
  stream << semester.semesterName << '\n';
  stream << semester.pSchoolYear->_id << '\n';
  stream << semester.pCourses.size() << '\n';
  for (const auto& p : semester.pCourses) stream << p->_id << '\n';
  return stream;
}

void Semester::addCourse(Course* const& course) { cout << "Not implemented\n"; }
void Semester::viewCourse(const string& courseID) {
  cout << "Not implemented\n";
}


void Semester::viewSemesterMenu() {
  Console::clear();
  cout << "----------------------\n";
  int i = 0;
  for (const auto& p : App::pSemesters) {
    ++i;
    cout << i << ". " << p->pSchoolYear->yearName << ": ";
    cout << p->semesterName << endl;
  }
  cout << i + 1 << ". "
       << "Create new semester\n";
  cout << "0. Go back\n";
  cout << "----------------------\n";
  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  //choose(choice, i + 1);
}