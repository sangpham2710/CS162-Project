#pragma once

#include <iostream>
#include <string>

#include "CSV.h"
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

  static void viewMainMenu();  // done
  static void createClass();   // done
  void classChooseMenu();      // done
  void updateClass();          // done
  void deleteClass();          // done
  void viewStudents();         // done
  void viewScoreboard();
  void exportScoreboard();
  void exportStudents();
  void importNewStudents();
};