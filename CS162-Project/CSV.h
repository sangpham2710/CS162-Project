#pragma once

#include <sstream>
#include <string>

#include "List.h"

using std::string;

using std::stringstream;

class CSV {
 public:
  static void _readLine(const string &line, List<string> &values) {
    string value = "";
    int state = 0;

    for (const char &c : line) {
      switch (state) {
        case 0: {
          switch (c) {
            case ',':
              values.push_back("");
              break;
            case '"':
              state = 2;
              break;
            default:
              value += c;
              state = 1;
              break;
          }
          break;
        }
        case 1: {
          switch (c) {
            case ',':
              values.push_back(value);
              value = "";
              state = 0;
              break;
            case '"':
              return;
            default:
              value += c;
              break;
          }
          break;
        }
        case 2: {
          switch (c) {
            case '"':
              state = 3;
              break;
            default:
              value += c;
              break;
          }
          break;
        }
        case 3: {
          switch (c) {
            case ',':
              values.push_back(value);
              value = "";
              state = 0;
              break;
            case '"':
              value += c;
              state = 2;
              break;
            default:
              return;
          }
          break;
        }
      }
    }

    switch (state) {
      case 0:
      case 1:
      case 3:
        values.push_back(value);
        break;
      case 2:
        return;
    }
  }
  static string _writeLine(const List<string> &values) {
    string line = "";
    bool first = true;
    for (const string &value : values) {
      if (first)
        first = false;
      else
        line += ',';

      bool enclosed = false;
      for (const char &c : value)
        if (c == ',' || c == '"') enclosed = true;

      if (!enclosed)
        line += value;
      else {
        string escaped = "";
        escaped += '"';
        for (char c : value) {
          if (c == '"') {
            escaped += '"';
            escaped += '"';
          } else {
            escaped += c;
          }
        }
        escaped += '"';
        line += escaped;
      }
    }

    return line;
  }

  template <class... Ts>
  static void readLine(const string &line, Ts &...args) {
    auto res = 0;

    List<string> values;
    _readLine(line, values);

    int index = 0;
    auto fn = [&](auto &v) {
      if (index == values.size()) return;
      if constexpr (std::is_same_v<decltype(v), string &>) {
        v = values[index++];
      } else {
        stringstream ss(values[index++]);
        ss >> v;
      }
    };
    (fn(args), ...);
  }

  template <class... Ts>
  static string writeLine(Ts... args) {
    List<string> values;

    auto fn = [&](auto &v) {
      stringstream ss;
      ss << v;
      values.push_back(ss.str());
    };
    (fn(args), ...);

    return _writeLine(values);
  }
};
