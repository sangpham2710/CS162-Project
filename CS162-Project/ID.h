#pragma once

#include <chrono>
#include <random>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

class ID {
 public:
  static std::random_device rd;
  static std::mt19937_64 rng;
  static std::uniform_int_distribution<int> dis;
  static std::uniform_int_distribution<int> dis2;
  static string gen() {
    stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
      ss << dis(rng);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
      ss << dis(rng);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
      ss << dis(rng);
    }
    ss << "-";
    ss << dis2(rng);
    for (i = 0; i < 3; i++) {
      ss << dis(rng);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
      ss << dis(rng);
    };
    return ss.str();
  }
};  // namespace ID