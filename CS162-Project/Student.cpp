#include "Student.h"

#include <iostream>

using std::cout;

std::ostream& operator<<(std::ostream& stream, const Student& student) {
  stream << student._id << '\n';
  stream << student.studentCode << '\n';
  stream << student.firstName << '\n';
  stream << student.lastName << '\n';
  stream << student.gender << '\n';
  stream << student.dateOfBirth << '\n';
  stream << student.socialID << '\n';
  stream << student.pClass->_id << '\n';
  stream << student.pUser->_id << '\n';
  stream << student.courseMarks.size() << '\n';
  for (const auto& courseMark : student.courseMarks)
    stream << courseMark << '\n';
  return stream;
}

double Student::getSemesterGPA(Semester* const& semester) {
  cout << "Not implemented\n";
  return 0;
}
double Student::getOverallGPA() {
  cout << "Not implemented\n";
  return 0;
}