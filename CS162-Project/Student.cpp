#include "Student.h"

#include <iostream>

#include "App.h"

using std::cout;

std::istream& operator>>(std::istream& stream, Student& student) {
  int n;
  stream >> student._id;
  stream.ignore();
  getline(stream, student.studentCode);
  getline(stream, student.lastName);
  getline(stream, student.firstName);
  getline(stream, student.gender);
  getline(stream, student.dateOfBirth);
  getline(stream, student.socialID);
  string classID;

  stream >> classID;
  student.pClass = *App::pClasses.find_if(
      [&](const auto& p) -> bool { return p->_id == classID; });
  string userID;
  stream >> userID;
  student.pUser = *App::pUsers.find_if(
      [&](const auto& p) -> bool { return p->_id == userID; });

  stream >> n;
  for (int i = 0; i < n; ++i) {
    CourseMark tmp;
    stream >> tmp;
    student.courseMarks.push_back(tmp);
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Student& student) {
  stream << student._id << '\n';
  stream << student.studentCode << '\n';
  stream << student.lastName << '\n';
  stream << student.firstName << '\n';
  stream << student.gender << '\n';
  stream << student.dateOfBirth << '\n';
  stream << student.socialID << '\n';
  stream << student.pClass->_id << '\n';
  stream << student.pUser->_id << '\n';
  stream << student.courseMarks.size() << '\n';
  for (const auto& courseMark : student.courseMarks) stream << courseMark;
  return stream;
}

double Student::getSemesterGPA() {
  auto currentSemesterCourseMarks =
      this->courseMarks.filter([&](const auto& courseMark) -> bool {
        return courseMark.pCourse->pSemester->_id == App::pCurrentSemester->_id;
      });
  if (currentSemesterCourseMarks.empty()) return -1;
  return currentSemesterCourseMarks
             .map<double>([&](const auto& courseMark) -> double {
               return courseMark.finalMark;
             })
             .reduce([&](const auto& sum, const auto& mark) -> double {
               return sum + mark;
             }) /
         (double)currentSemesterCourseMarks.size();
}

double Student::getOverallGPA() {
  if (this->courseMarks.empty()) return -1;
  return this->courseMarks
             .map<double>([&](const auto& courseMark) -> double {
               return courseMark.finalMark;
             })
             .reduce([&](const auto& sum, const auto& mark) -> double {
               return sum + mark;
             }) /
         (double)this->courseMarks.size();
}