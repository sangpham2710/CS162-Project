#include "Console.h"

#include <sstream>
#include <string>

HWND Console::window = GetConsoleWindow();
HANDLE Console::inputHandle = GetStdHandle(STD_INPUT_HANDLE);
HANDLE Console::outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::setup() {
  setFont(L"Consolas", FW_BOLD, 10, 20);
  setConsoleColor(Color::BRIGHT_WHITE, Color::BLACK);
  setSize(80, 30);
  setTitle(L"Course Registration System");
  disableMaximize();
  disableMouseInput();
  hideScrollBars();
  showCursor(true);
}

void Console::setSize(const short& width, const short& height) {
  COORD pos{width, height};
  SMALL_RECT rect;
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

  rect = {0, 0, 1, 1};
  SetConsoleWindowInfo(hOut, TRUE, &rect);
  SetConsoleScreenBufferSize(hOut, pos);
  SetConsoleActiveScreenBuffer(hOut);

  rect = {0, 0, (short)(width - 1), (short)(height - 1)};
  SetConsoleWindowInfo(hOut, TRUE, &rect);
  SetConsoleActiveScreenBuffer(hOut);
  SetConsoleScreenBufferSize(hOut, pos);
}

int Console::getWindowWidth() {
  CONSOLE_SCREEN_BUFFER_INFO csbf;
  GetConsoleScreenBufferInfo(Console::outputHandle, &csbf);
  return csbf.dwSize.X;
}

int Console::getWindowHeight() {
  CONSOLE_SCREEN_BUFFER_INFO csbf;
  GetConsoleScreenBufferInfo(Console::outputHandle, &csbf);
  return csbf.dwSize.Y;
}

void Console::gotoxy(const int& x, const int& y) {
  SetConsoleCursorPosition(Console::outputHandle, COORD{(short)x, (short)y});
}

void Console::setConsoleColor(const int& backgroundColor,
                              const int& textColor) {
  std::stringstream ss;
  ss << std::hex << ((backgroundColor << 4) | textColor);

  std::string tmp = std::string("color ") + ss.str();
  system(tmp.c_str());
}

void Console::setConsoleTextColor(const int& backgroundColor,
                                  const int& textColor) {
  SetConsoleTextAttribute(Console::outputHandle,
                          (backgroundColor << 4) | textColor);
}

void Console::hideScrollBars() { ShowScrollBar(Console::window, SB_BOTH, 0); }

void Console::setTitle(const wchar_t title[]) { SetConsoleTitle(title); }

void Console::disableMaximize() {
  SetWindowLong(Console::window, GWL_STYLE,
                GetWindowLong(Console::window, GWL_STYLE) & ~WS_MAXIMIZEBOX &
                    ~WS_SIZEBOX);
}

void Console::showCursor(const bool& flag) {
  CONSOLE_CURSOR_INFO tmp;
  GetConsoleCursorInfo(Console::outputHandle, &tmp);
  tmp.bVisible = flag;
  SetConsoleCursorInfo(Console::outputHandle, &tmp);
}

void Console::setFont(const wchar_t fontName[], const short& fontWeight,
                      const short& width, const short& height) {
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof cfi;
  cfi.nFont = 0;
  cfi.dwFontSize = {width, height};
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = fontWeight;
  wcscpy_s(cfi.FaceName, fontName);
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::clear() { system("cls"); }

void Console::disableMouseInput() {
  DWORD prevMode;
  GetConsoleMode(Console::inputHandle, &prevMode);
  SetConsoleMode(Console::inputHandle,
                 ENABLE_EXTENDED_FLAGS | (prevMode & ~ENABLE_QUICK_EDIT_MODE));
}
