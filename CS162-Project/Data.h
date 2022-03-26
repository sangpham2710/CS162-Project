#pragma once

#include <string>

#include "List.h"

using std::string;

class Data {
 public:
  template <class T>
  static bool saveIDs(const string& path, const List<T*>& list) {
    ofstream ofs;
    if (!ofs.is_open()) return false;
    for (const auto& p : list) ofs << p->_id << '\n';
    ofs.close();
    return true;
  }
  template <class T>
  static bool saveObjs(const string& path, const List<T*>& list) {
    for (auto p : list) {
      ofstream ofs(path + p->_id + ".dat");
      if (!ofs.is_open()) return false;
      ofs << *p << '\n';
      ofs.close();
    }
    return true;
  };
};