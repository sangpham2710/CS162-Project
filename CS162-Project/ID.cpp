#include "ID.h"

std::random_device ID::rd;
std::mt19937_64 ID::rng(ID::rd());
std::uniform_int_distribution<int> ID::dis(0, 15);
std::uniform_int_distribution<int> ID::dis2(8, 11);