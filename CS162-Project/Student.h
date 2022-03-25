#pragma once

#include <string>

#include "Course.h"
#include "CourseMark.h"
#include "Semester.h"
#include "List.h"

using std::string;

class Student {
 private:
  string studentID;
  string firstName;
  string lastName;
  string gender;
  string dateOfBirth;
  string socialID;

  List<Course> courses;
  List<CourseMark> courseMarks;

 public:
	 double getSemesterGPA(Semester){
		 
  };
  double getOverallGPA();
};
