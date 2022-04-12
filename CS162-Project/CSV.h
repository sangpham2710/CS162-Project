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
