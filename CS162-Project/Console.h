#pragma once
#pragma comment(lib, "Winmm.lib")
#include <conio.h>
#include <windows.h>

enum Color {
  BLACK,
  BLUE,
  GREEN,
  AQUA,
  RED,
  PURPLE,
  YELLOW,
  WHITE,
  GRAY,
  LIGHT_BLUE,
  LIGHT_GREEN,
  LIGHT_AQUA,
  LIGHT_RED,
  LIGHT_PURPLE,
  LIGHT_YELLOW,
  BRIGHT_WHITE
};

using namespace std;

class Console {
 private:
  static HWND window;
  static HANDLE inputHandle;
  static HANDLE outputHandle;

 public:
  Console() {}
  ~Console() {}
  static int getWindowWidth();
  static int getWindowHeight();
  static void setup();
  static void setSize(const short& width, const short& height);
  static void gotoxy(const int& x, const int& y);
  static void setConsoleColor(const int& backgroundColor, const int& textColor);
  static void setConsoleTextColor(const int& backgroundColor,
                                  const int& textColor);
  static void hideScrollBars();
  static void setFont(const wchar_t fontName[], const short& fontWeight,
                      const short& width, const short& height);
  static void setTitle(const wchar_t title[]);
  static void disableMaximize();
  static void showCursor(const bool& flag);
  static void clear();
  static void disableMouseInput();
  static void playSound(int);
};