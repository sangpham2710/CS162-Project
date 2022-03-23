#include <iostream>

#include "App.h"
#include "Console.h"

using namespace std;

int main() {
  Console::setup();
  App::run();
  return 0;
}