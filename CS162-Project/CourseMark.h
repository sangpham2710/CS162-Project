#pragma once

#include <string>

using std::string;

class Course;

class CourseMark {
 public:
  List<Course>::iterator pCourse;
  double midtermMark, finalMark, otherMark, totalMark;
};