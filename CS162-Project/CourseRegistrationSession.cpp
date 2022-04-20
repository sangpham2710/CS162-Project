#include "CourseRegistrationSession.h"

#include <string>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

using std::string;

std::istream& operator>>(std::istream& stream,
                         CourseRegistrationSession& session) {
  stream >> session.startTime;
  stream >> session.endTime;
  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const CourseRegistrationSession& session) {
  stream << session.startTime << '\n';
  stream << session.endTime << '\n';
  return stream;
}

bool CourseRegistrationSession::isOpen() {
  return TimeStamp::now().inRange(this->startTime, this->endTime);
}

void CourseRegistrationSession::viewMainMenu() {
  bool sessionOpen = App::courseRegistrationSession.isOpen();
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "Current session status: " << (sessionOpen ? "OPEN" : "CLOSED")
       << '\n';

  if (sessionOpen) {
    // Allow staff to close
    cout << "Start time: ";
    App::courseRegistrationSession.startTime.output();
    cout << '\n';
    cout << "End time: ";
    App::courseRegistrationSession.endTime.output();
    cout << '\n';
    Utils::printLine();
    cout << "1. Close current session\n";
    Utils::printLine();
    cout << "0. Return\n\n";
    int option = Utils::getOption(0, 1);
    if (option == 0) {
      Menu::staffMenu();
      return;
    } else {
      CourseRegistrationSession::closeSession();
      return;
    }
  } else {
    Utils::printLine();
    cout << "1. Open registration session\n";
    cout << "0. Return\n\n";
    int option = Utils::getOption(0, 1);
    if (option == 0) {
      Menu::staffMenu();
      return;
    } else {
      CourseRegistrationSession::openSession();
      return;
    }
  }
}

void CourseRegistrationSession::openSession() {
  Console::clear();
  Utils::getCurrentSemester();
  int minutes, hours, day, month, year;
  auto getInput = [](const string& name, int& value, int min, int max) {
    cout << "Input " << name << ": ";
    cin >> value;
    while (value < min || value > max) {
      cout << "Invalid input! Value must be between " << min << " and " << max
           << "!\n";
      cout << "Input " << name << ": ";
      cin >> value;
    }
  };
  cout << "---------------- Input start time ----------------\n";
  getInput("year", year, 0, 1e9);
  getInput("month", month, 1, 12);
  getInput("day", day, 1, 31);
  getInput("hours", hours, 0, 23);
  getInput("minutes", minutes, 0, 59);
  App::courseRegistrationSession.startTime.setMinutes(minutes)
      .setHours(hours)
      .setDay(day)
      .setMonth(month)
      .setYear(year);

  cout << "---------------- Input end time ----------------\n";
  getInput("year", year, 0, 1e9);
  getInput("month", month, 1, 12);
  getInput("day", day, 1, 31);
  getInput("hours", hours, 0, 23);
  getInput("minutes", minutes, 0, 59);
  App::courseRegistrationSession.endTime.setMinutes(minutes)
      .setHours(hours)
      .setDay(day)
      .setMonth(month)
      .setYear(year);
  if (!App::courseRegistrationSession.isOpen()) {
    cout << "Invalid time range! Time range must include the present!\n";
    App::courseRegistrationSession.startTime = TimeStamp{};
    App::courseRegistrationSession.endTime = TimeStamp{};
    Utils::waitForKeypress();
    CourseRegistrationSession::openSession();
  } else {
    cout << "Session opened!\n";
    Utils::waitForKeypress();
    CourseRegistrationSession::viewMainMenu();
  }
}

void CourseRegistrationSession::closeSession() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  App::courseRegistrationSession.startTime = TimeStamp{};
  App::courseRegistrationSession.endTime = TimeStamp{};
  cout << "Session closed!\n";
  Utils::waitForKeypress();
  CourseRegistrationSession::viewMainMenu();
}

void CourseRegistrationSession::displayCourseRegistrationSession() {
  cout << "From: ";
  this->startTime.output();
  cout << '\n';
  cout << "To: ";
  this->endTime.output();
  cout << '\n';
}