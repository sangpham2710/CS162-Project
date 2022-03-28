#pragma once

#include <string>

#include "List.h"

using std::string;

class Data {
 public:
  static const string DATA_DIR;
  static const string USERS_DIR;
  static const string SCHOOLYEARS_DIR;
  static const string SEMESTERS_DIR;
  static const string CLASSES_DIR;
  static const string COURSES_DIR;
  static const string STUDENTS_DIR;

  template <class T>
  static bool loadIDs(const string& path, List<T*>& list);
  template <class T>
  static bool loadObjs(const string& path, List<T*>& list);

  template <class T>
  static bool saveIDs(const string& path, const List<T*>& list);
  template <class T>
  static bool saveObjs(const string& path, const List<T*>& list);
};

#include <fstream>

using std::ifstream;
using std::ofstream;

const string Data::DATA_DIR = "data/";
const string Data::USERS_DIR = "data/users/";
const string Data::SCHOOLYEARS_DIR = "data/schoolYears/";
const string Data::SEMESTERS_DIR = "data/semesters/";
const string Data::CLASSES_DIR = "data/classes/";
const string Data::COURSES_DIR = "data/courses/";
const string Data::STUDENTS_DIR = "data/students/";

template <class T>
bool Data::loadIDs(const string& path, List<T*>& list) {
  ifstream ifs(path + "IDs.txt");
  if (!ifs.is_open()) return false;
  int n;
  ifs >> n;
  for (int i = 0; i < n; ++i) {
    string id;
    ifs >> id;
    list.push_back(new T(id));
  }
  ifs.close();
  return true;
}

template <class T>
bool Data::loadObjs(const string& path, List<T*>& list) {
  for (auto p : list) {
    ifstream ifs(path + p->_id + ".txt");
    if (!ifs.is_open()) return false;
    ifs >> *p;
    ifs.close();
  }
  return true;
};

template <class T>
bool Data::saveIDs(const string& path, const List<T*>& list) {
  ofstream ofs(path + "IDs.txt");
  if (!ofs.is_open()) return false;
  ofs << list.size() << '\n';
  for (const auto& p : list) ofs << p->_id << '\n';
  ofs.close();
  return true;
}

template <class T>
bool Data::saveObjs(const string& path, const List<T*>& list) {
  for (auto p : list) {
    ofstream ofs(path + p->_id + ".txt");
    if (!ofs.is_open()) return false;
    ofs << *p << '\n';
    ofs.close();
  }
  return true;
};