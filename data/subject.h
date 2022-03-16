#pragma once
#include<iostream>
using namespace std;

class Subject {
  string subjectID;
  string subjectName;
  int numberCredits;
  Subject(string _subjectID, string _subjectName, int _numberCredits)
      : subjectID(_subjectID),
        subjectName(_subjectName),
        numberCredits(_numberCredits) {}
};