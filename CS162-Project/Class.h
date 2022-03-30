#pragma once

#include <iostream>
#include <string>

#include "ID.h"
#include "List.h"
#include "Student.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Student;

class Class {
 public:
  string _id;
  string classCode;
  List<Student*> pStudents;

  Class(const string& id) : _id{id}, classCode{}, pStudents{} {}
  Class() : Class{ID::gen()} {}

  friend std::istream& operator>>(std::istream& stream, Class& _class);
  friend std::ostream& operator<<(std::ostream& stream, const Class& _class);

  static void viewMainMenu();
  static void create();
  static void choose(const int& choice, const int& i);
  void viewEditClass();
  void updateClass();
  void deleteClass();
  void viewListStudents();
  void viewScoreboardClass();
};