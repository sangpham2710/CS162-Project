#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct Teacher {
    int No;
    string TeaID;
    string Fname;
    string Lname;
    string Gen;
    int SocID;
    string Faculty;
    string Pass;
};

struct Student {
    int No;
    string StuID;
    string Fname;
    string Lname;
    string Gen;
    int Day, Month, Year;
    int SocID;
    string Class;
    string Pass;
};

struct Course {
    int NumCre;
    int MaxMem;
    int DayStart;
    int MonthStart;
    int DayEnd;
    int MonthEnd;
    string ID;
    string CName;
    string TName;
    string Day1;
    string Session1;
    string Day2;
    string Session2;
};

int countStu();
int countTea();
int countCou();
int convertStringToNum(string s);

void loadStudentFromFile(vector <Student>& S, int& n);
void loadTeacherFromFile(vector <Teacher>& T, int& n);
void loadCourseFromFile(vector <Course>& C, int& n);