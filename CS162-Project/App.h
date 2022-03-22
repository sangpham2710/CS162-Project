#pragma once

class App {
 private:
  void loadData();
  void saveData();
  bool auth();

 public:
  App();
  ~App();
  void run();
};
