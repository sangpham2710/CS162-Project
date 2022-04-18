#pragma once
#include <iostream>

class Utils {
 public:
  static void waitForKeypress() {
#pragma push_macro("max")
#undef max
    if (cin.rdbuf()->sungetc() != std::char_traits<char>::eof() &&
        cin.get() != '\n') {
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "Press Enter to continue\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#pragma pop_macro("max")
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
  static bool convertStringScheduleToInt(string tmp, int& session1, int& session2) {
      while (tmp[6] != '/') {
          cout << "Invalid!\n";
          cout << "\nInput schedule (Ex: MON:S1/TUE:S2): ";
          getline(cin, tmp);
      }
      
      string session1_day;
      string session2_day;
      string session1_s;
      string session2_s;
      session1_day.resize(3);
      session2_day.resize(3);
      session1_s.resize(2);
      session2_s.resize(2);
      for (int i = 0; i < 3; ++i) {
          session1_day[i] = tmp[i];
          session2_day[i] = tmp[7 + i];
      }
      for (int i = 0; i < 2; ++i) {
          session1_s[i] = tmp[4 + i];
          session2_s[i] = tmp[11 + i];
      }

      bool check1 = false, check2 = false;
      string day[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
      string time[4] = { "S1", "S2", "S3", "S4" };
      for (int i = 0; i < 7; ++i) {
          if (session1_day == day[i]) {
              for (int j = 0; j < 4; ++j) {
                  if (session1_s == time[j]) {
                      session1 = (i + 2) * 10 + j + 1;
                      check1 = true;
                  }
              }
          }
          if (session2_day == day[i]) {
              for (int j = 0; j < 4; ++j) {
                  if (session2_s == time[j]) {
                      session2 = (i + 2) * 10 + j + 1;
                      check2 = true;
                  }
              }
          }
      }
      if (!check1 || !check2) return false;
      return true;
  }
  static void convertIntScheduleToString(int session1, int session2, string& schedule) {
      string day[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };
      string time[4] = { "S1", "S2", "S3", "S4" };
      schedule.resize(13);
      schedule = day[session1 / 10 - 2];
      schedule = schedule + ":";
      schedule = schedule + time[session1 % 10 - 1];
      schedule = schedule + "/";
      schedule = schedule + day[session2 / 10 - 2];
      schedule = schedule + ":";
      schedule = schedule + time[session2 % 10 - 1];
  }
};