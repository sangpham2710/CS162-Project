#include "CourseMark.h"

std::ostream& operator<<(std::ostream& stream, const CourseMark& courseMark) {
  stream << courseMark.pCourse->_id << ' ' << courseMark.midtermMark << ' '
         << courseMark.finalMark << ' ' << courseMark.otherMark << ' '
         << courseMark.totalMark << '\n';
  return stream;
}