#pragma once

#include<iostream>
#include <list>
#include <string>

#include "ID.h"
#include "List.h"

using std::string;
using std::cin;
using std::cout;

class Semester;
class Student;

class Course {
public:
    string _id;
    string courseCode;
    string courseName;
    string lecturer;
    string startDate;
    string endDate;
    int maxNumberOfStudents;
    int numberOfCredits;
    string schedule;
    Semester* pSemester;
    List<Student*> pStudents;

    Course(const string& id)
        : _id{ id },
        courseCode{},
        courseName{},
        lecturer{},
        startDate{},
        endDate{},
        maxNumberOfStudents{},
        numberOfCredits{},
        schedule{},
        pSemester{ nullptr },
        pStudents{} {}
    Course() : Course{ ID::gen() } {}

    friend std::istream& operator>>(std::istream& stream, Course& course);
    friend std::ostream& operator<<(std::ostream& stream, const Course& course);

    static void create();
    static void choose(Course* pCourse, short screen, short option); // mainMenu = 1, chooseCourseMenu =2, updateCourseMenu = 3, updateStudentMenu = 4
    static void courseMainMenu();

    void updateCourseInfo();
    void viewStudentScoreboard();
    void importScoreboard();
    void exportScoreboard();
    void addStudent();
    void removeStudent();
    void updateStudentScoreBoard();
    void deleteCourse();

    void courseChooseMenu();
    void courseUpdateMenu();
    void courseUpdateStudentMenu();
};