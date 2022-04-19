#pragma once

#include "TimeStamp.h"

class CourseRegistrationSession {
 public:
  TimeStamp startTime;
  TimeStamp endTime;
  CourseRegistrationSession() : startTime{}, endTime{} {}
  bool isOpen();
  static void viewMainMenu();
  static void openSession();
  static void closeSession();

  friend std::istream& operator>>(std::istream& stream,
                                  CourseRegistrationSession& session);
  friend std::ostream& operator<<(std::ostream& stream,
                                  const CourseRegistrationSession& session);
  void displayCourseRegistrationSession();
};