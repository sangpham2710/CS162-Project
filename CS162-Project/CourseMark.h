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
      : pCourse(nullptr),
        midtermMark(0),
        finalMark(0),
        otherMark(0),
        totalMark(0) {}
  friend std::ostream& operator<<(std::ostream& stream,
                                  const CourseMark& courseMark);
};