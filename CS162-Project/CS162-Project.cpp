#include <iostream>

#include "App.h"
#include "Console.h"

using namespace std;

int main() {
  Console::setup();
  App app;
  app.run();
  return 0;
}