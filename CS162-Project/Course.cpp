#include "Course.h"

#include <iostream>

#include "Semester.h"
#include "Student.h"

using std::cout;

std::ostream& operator<<(std::ostream& stream, const Course& course) {
  stream << course._id << '\n';
  stream << course.courseCode << '\n';
  stream << course.courseName << '\n';
  stream << course.lecturer << '\n';
  stream << course.startDate << '\n';
  stream << course.endDate << '\n';
  stream << course.maxNumberOfStudents << '\n';
  stream << course.numberOfCredits << '\n';
  stream << course.schedule << '\n';
  stream << course.pSemester->_id << '\n';
  stream << course.pStudents.size() << '\n';
  for (auto p : course.pStudents) stream << p->_id << '\n';
  return stream;
}

void Course::viewScoreboard() {
  cout << "Not implemented\n";
}
void Course::importScoreboard() {
  cout << "Not implemented\n";
}
void Course::exportScoreboard() {
  cout << "Not implemented\n";
}