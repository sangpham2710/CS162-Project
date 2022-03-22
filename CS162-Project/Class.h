#pragma once

#include <string>
using std::string;

class Student;

class Class {
 private:
  string id;
  string name;
  List<Student> students;
};