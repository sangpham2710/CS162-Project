#pragma once

#include <iostream>
#include <string>

#include "App.h"
#include "Console.h"

class Utils {
 public:
  static void waitForKeypress() {
    cout << "Press any key to continue\n";
    char ch = _getch();
    if (ch == 0 || ch == 224) ch = _getch();
  }
  static int getOption(int minOption, int maxOption) {
    int option;
    cout << "Your choice: ";
    cin >> option;
    while (option < minOption || option > maxOption) {
      cout << "\nInvalid!\n";
      cout << "Your choice: ";
      cin >> option;
    }
    return option;
  }
  static void getSchedule(int& session1, int& session2) {
    cout << "\nFirst session: \n";
    cout << "Day of week: 1.MON    2.TUE   3.WED   4.THU   5.FRI   6.SAT   "
            "7.SUN\n";
    int option = Utils::getOption(1, 7);
    session1 = option + 1;
    cout << "Session: 1.S1 (07:30)    2.S2 (09:30)    3.S3 (13:30)    4.S4 "
            "(15:30)\n";
    option = Utils::getOption(1, 4);
    session1 = session1 * 10 + option;
    cout << "\nSecond session: \n";
    cout << "Day of week: 1.MON    2.TUE   3.WED   4.THU   5.FRI   6.SAT   "
            "7.SUN\n";
    option = Utils::getOption(1, 7);
    session2 = option + 1;
    cout << "Session: 1.S1 (07:30)    2.S2 (09:30)    3.S3 (13:30)    4.S4 "
            "(15:30)\n";
    option = Utils::getOption(1, 4);
    session2 = session2 * 10 + option;
  }
  static void convertIntScheduleToString(int session1, int session2,
                                         string& schedule) {
    string day[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    string time[4] = {"S1", "S2", "S3", "S4"};
    schedule.resize(13);
    schedule = day[session1 / 10 - 2];
    schedule = schedule + ":";
    schedule = schedule + time[session1 % 10 - 1];
    schedule = schedule + "/";
    schedule = schedule + day[session2 / 10 - 2];
    schedule = schedule + ":";
    schedule = schedule + time[session2 % 10 - 1];
  }

  static void getCurrentSemester() {
    if (!App::pCurrentSemester) {
      cout << "Current Semester: None";
      Console::gotoxy(80, 0);
      cout << "Signed in as " << App::pCurrentUser->username;
      Console::gotoxy(0, 0);
      return;
    }
    cout << "Current Semester: " << App::pCurrentSemester->pSchoolYear->yearName
         << " - " << App::pCurrentSemester->semesterName << '\n';
    Console::gotoxy(80, 0);
    cout << "Signed in as " << App::pCurrentUser->username;
    Console::gotoxy(0, 1);
  }

  static void printLine() { cout << string(40, '-') << '\n'; }
};