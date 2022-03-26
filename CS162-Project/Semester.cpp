#include "Semester.h"

#include <iostream>

#include "SchoolYear.h"

using std::cout;

std::ostream& operator<<(std::ostream& stream, const Semester& semester) {
  stream << semester._id << '\n';
  stream << semester.pSchoolYear->_id << '\n';
  stream << semester.pCourses.size() << '\n';
  for (const auto& p : semester.pCourses) cout << p->_id << '\n';
  return stream;
}

void Semester::addCourse(Course* const& course) { cout << "Not implemented\n"; }
void Semester::viewCourse(const string& courseID) {
  cout << "Not implemented\n";
}