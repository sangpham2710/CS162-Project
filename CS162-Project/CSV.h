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
