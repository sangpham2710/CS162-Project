#pragma once
#include <string>

#include "uuidLib.h"

using std::string;

class ID {
 public:
  static string gen() {
    return uuids::to_string(uuids::uuid_system_generator{}());
  }
};