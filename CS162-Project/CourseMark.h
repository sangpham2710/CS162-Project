#pragma once

#include <string>
#include "Course.h"

using std::string;

class CourseMark {
 public:
	Course* pCourse;
	double midtermMark, finalMark, otherMark, totalMark;
};