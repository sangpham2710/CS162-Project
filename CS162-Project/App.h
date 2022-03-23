#pragma once

class App {
 private:
  static void loadData();
  static void saveData();
  static bool auth();

 public:
  static void run();
};
