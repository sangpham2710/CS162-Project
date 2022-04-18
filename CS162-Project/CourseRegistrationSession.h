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
};