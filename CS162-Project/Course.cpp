#include "Course.h"

#include <iostream>

#include "App.h"
#include "Semester.h"
#include "Student.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Course& course) {
  int n;
  stream >> course._id;
  stream >> course.courseCode;
  stream >> course.courseName;
  stream >> course.lecturer;
  stream >> course.startDate;
  stream >> course.endDate;
  stream >> course.maxNumberOfStudents;
  stream >> course.numberOfCredits;
  stream >> course.schedule;
  stream >> course.pSemester->_id;
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string studentID;
    stream >> studentID;
    course.pStudents.push_back(*App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->_id == studentID; }));
  }
  return stream;
}

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
  for (const auto& p : course.pStudents) stream << p->_id << '\n';
  return stream;
}

void Course::viewScoreboard() { cout << "Not implemented\n"; }
void Course::importScoreboard() { cout << "Not implemented\n"; }
void Course::exportScoreboard() { cout << "Not implemented\n"; }