#pragma once
#include<iostream>
using namespace std;

class Lecturer {
 protected:
  string lecturerName;
  Lecturer(string _lecturerName) : lecturerName(_lecturerName) {}
};