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
};