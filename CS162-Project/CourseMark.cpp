#include "CourseMark.h"

#include "App.h"

std::istream& operator>>(std::istream& stream, CourseMark& courseMark) {
  string courseID;
  stream >> courseID >> courseMark.midtermMark >> courseMark.finalMark >>
      courseMark.otherMark >> courseMark.totalMark;
  courseMark.pCourse = *App::pCourses.find_if(
      [&](const auto& p) -> bool { return p->_id == courseID; });
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const CourseMark& courseMark) {
  stream << courseMark.pCourse->_id << ' ' << courseMark.midtermMark << ' '
         << courseMark.finalMark << ' ' << courseMark.otherMark << ' '
         << courseMark.totalMark << '\n';
  return stream;
}