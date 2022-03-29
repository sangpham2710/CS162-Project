#pragma once

#include <string>
#include<iostream>

#include "ID.h"
#include "List.h"
#include "Student.h"
#include "App.h"

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
  static void view();
  static void create();
};