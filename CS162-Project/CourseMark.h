#pragma once

#include <string>

using std::string;

class Course;

class CourseMark {
 public:
  Course *course;
  double midtermMark, finalMark, otherMark, totalMark;
};