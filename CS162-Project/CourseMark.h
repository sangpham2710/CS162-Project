#pragma once

#include <string>

#include "Course.h"

using std::string;

class Course;

class CourseMark {
 public:
  Course* pCourse;
  double midtermMark, finalMark, otherMark, totalMark;
  CourseMark()
      : pCourse{nullptr},
        midtermMark{-1},
        finalMark{-1},
        otherMark{-1},
        totalMark{-1} {}
  friend std::istream& operator>>(std::istream& stream, CourseMark& courseMark);
  friend std::ostream& operator<<(std::ostream& stream,
                                  const CourseMark& courseMark);
};