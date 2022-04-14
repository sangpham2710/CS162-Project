#pragma once
#include <iostream>

class Utils {
 public:
  static void waitForKeypress() {
    cout << "Press any key to continue\n";
    // cin.ignore();
    cin.get();
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