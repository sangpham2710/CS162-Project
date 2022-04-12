#pragma once

#include <sstream>
#include <string>

#include "List.h"

using std::string;

using std::stringstream;

namespace CSV {
enum State { Initial, Data, Quote, QuoteInQuote };

enum Error {
  Success,
  ImproperQuote,
  UnpairedQuote,
  UnclosedQuote,
  InsufficientColumns,
};

Error _readLine(const string &line, List<string> &values) {
  string value = "";
  auto state = State::Initial;

  for (const char &c : line) {
    switch (state) {
      case State::Initial: {
        switch (c) {
          case ',':
            values.push_back("");
            break;
          case '"':
            state = State::Quote;
            break;
          default:
            value += c;
            state = State::Data;
            break;
        }
        break;
      }
      case State::Data: {
        switch (c) {
          case ',':
            values.push_back(value);
            value = "";
            state = State::Initial;
            break;
          case '"':
            return Error::ImproperQuote;
          default:
            value += c;
            break;
        }
        break;
      }
      case State::Quote: {
        switch (c) {
          case '"':
            state = State::QuoteInQuote;
            break;
          default:
            value += c;
            break;
        }
        break;
      }
      case State::QuoteInQuote: {
        switch (c) {
          case ',':
            values.push_back(value);
            value = "";
            state = State::Initial;
            break;
          case '"':
            value += c;
            state = State::Quote;
            break;
          default:
            return Error::UnpairedQuote;
        }
        break;
      }
    }
  }

  switch (state) {
    case State::Initial:
    case State::Data:
    case State::QuoteInQuote:
      values.push_back(value);
      break;
    case State::Quote:
      return Error::UnpairedQuote;
  }

  return Error::Success;
}
string _writeLine(const List<string> &values) {
  string line = "";
  bool first = true;
  for (const string &value : values) {
    if (first) {
      first = false;
    } else {
      line += ',';
    }

    bool enclosed = false;
    for (const char &c : value) {
      if (c == ',' || c == '"') {
        enclosed = true;
      }
    }

    if (!enclosed) {
      line += value;
    } else {
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
Error readLine(const string &line, Ts &...args) {
  auto res = Error::Success;

  List<string> values;
  _readLine(line, values);

  int index = 0;
  auto fn = [&](auto &v) {
    if (index == values.size()) {
      res = Error::InsufficientColumns;
      return;
    }
    if constexpr (std::is_same_v<decltype(v), string &>) {
      v = values[index++];
    } else {
      stringstream ss(values[index++]);
      ss >> v;
    }
  };
  (fn(args), ...);

  return res;
}
