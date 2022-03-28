#include "SchoolYear.h"

#include "App.h"

std::istream& operator>>(std::istream& stream, SchoolYear& schoolYear) {
  int n;
  stream >> schoolYear._id;
  stream.ignore();
  getline(stream, schoolYear.yearName);
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string semesterID;
    stream >> semesterID;
    schoolYear.pSemesters.push_back(*App::pSemesters.find_if(
        [&](const auto& p) { return p->_id == semesterID; }));
  }
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string classID;
    stream >> classID;
    schoolYear.pClasses.push_back(*App::pClasses.find_if(
        [&](const auto& p) -> bool { return p->_id == classID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const SchoolYear& schoolYear) {
  stream << schoolYear._id << '\n';
  stream << schoolYear.yearName << '\n';
  stream << schoolYear.pSemesters.size() << '\n';
  for (const auto& p : schoolYear.pSemesters) stream << p->_id << '\n';
  stream << schoolYear.pClasses.size() << '\n';
  for (const auto& p : schoolYear.pClasses) stream << p->_id << '\n';
  return stream;
}