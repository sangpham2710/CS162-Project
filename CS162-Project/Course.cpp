#include "Course.h"

#include <iostream>

#include "App.h"
#include "Semester.h"
#include "Student.h"

using std::string;
using std::cout;
using std::cin;

std::istream& operator>>(std::istream& stream, Course& course) {
  int n;
  stream >> course._id;
  stream.ignore();
  getline(stream, course.courseCode);
  getline(stream, course.courseName);
  getline(stream, course.lecturer);
  getline(stream, course.startDate);
  getline(stream, course.endDate);
  stream >> course.maxNumberOfStudents;
  stream >> course.numberOfCredits;
  stream.ignore();
  getline(stream, course.schedule);
  string semesterID;
  stream >> semesterID;
  course.pSemester = *App::pSemesters.find_if(
      [&](const auto& p) -> bool { return p->_id == semesterID; });
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string studentID;
    stream >> studentID;
    course.pStudents.push_back(*App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->_id == studentID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Course& course) {
  stream << course._id << '\n';
  stream << course.courseCode << '\n';
  stream << course.courseName << '\n';
  stream << course.lecturer << '\n';
  stream << course.startDate << '\n';
  stream << course.endDate << '\n';
  stream << course.maxNumberOfStudents << '\n';
  stream << course.numberOfCredits << '\n';
  stream << course.schedule << '\n';
  stream << course.pSemester->_id << '\n';
  stream << course.pStudents.size() << '\n';
  for (const auto& p : course.pStudents) stream << p->_id << '\n';
  return stream;
}

void Course::create() {
    //clearScreen();

    if (!App::pCurrentSemester) {
        cout << "Please create a semester first \n";
        return;
    }

    cout << "This new course will be taught in ";
    cout << App::pCurrentSemester->pSchoolYear->yearName << " " << App::pCurrentSemester->semesterName;
    cout << "\n";

    string courseCode;
    cout << "Input course code: ";
    cin >> courseCode;
    for (auto crs : App::pCurrentSemester->pCourses) {
        if (crs->courseCode == courseCode) {
            cout << "Current semester already has course " << crs->courseCode;
            return;
        }
    }

    Course* pCourse = new Course();
    pCourse->courseCode = courseCode;
    cout << "Input course name: ";
    cin.ignore();
    getline(cin, pCourse->courseName);
    cout << "Input lecturer's name: ";
    getline(cin, pCourse->lecturer);
    cout << "Input start date: ";
    getline(cin, pCourse->startDate);
    cout << "Input end date: ";
    getline(cin, pCourse->endDate);
    cout << "Input max number of students: ";
    cin >> pCourse->maxNumberOfStudents;
    cout << "Input number of credits: ";
    cin >> pCourse->numberOfCredits;
    cout << "Input schedule (Ex: MON:S1/TUE:S2): ";
    cin >> pCourse->schedule;

    App::pCurrentSemester->pCourses.push_back(pCourse);
    App::pCourses.push_back(pCourse);
}

void Course::choose(Course* pCourse, short option) {
    if (option == 1) {
        updateCourseInfo(pCourse);
    }
}

void Course::updateCourseInfo(Course* pCourse) {
    cout << "1. Course code: " << pCourse->courseCode << "\n";
    cout << "2. Course name: " << pCourse->courseName << "\n";
    cout << "3. Lecturer: " << pCourse->lecturer << "\n";
    cout << "4. Start date: " << pCourse->startDate << "\n";
    cout << "5. End date: " << pCourse->endDate << "\n";
    cout << "6. Max number of students: " << pCourse->maxNumberOfStudents << "\n";
    cout << "7. Number of credits: " << pCourse->numberOfCredits << "\n";
    cout << "8. Schedule: " << pCourse->schedule << "\n" << "\n";

    cout << "Which one do you want to update? \n";
    cout << "Your choice: ";
    short option;
    cin >> option;
    switch (option) {
        case 1: {
            cout << "New course code: ";
            cin >> pCourse->courseCode;
            break;
        }
        case 2: {
            cout << "New course name: ";
            cin >> pCourse->courseName;
            break;
        }
        case 3: {
            cout << "New lecturer: ";
            cin.ignore();
            getline(cin, pCourse->lecturer);
            break;
        }
        case 4: {
            cout << "New start date: ";
            cin >> pCourse->startDate;
            break;
        }
        case 5: {
            cout << "New end date: ";
            cin >> pCourse->endDate;
            break;
        }
        case 6: {
            cout << "New max number of students: ";
            cin >> pCourse->maxNumberOfStudents;
            break;
        }
        case 7: {
            cout << "New number of credits: ";
            cin >> pCourse->numberOfCredits;
            break;
        }
        case 8: {
            cout << "New schedule: ";
            cin >> pCourse->schedule;
            break;
        }
    }
}

void Course::viewScoreboard() { cout << "Not implemented\n"; }
void Course::importScoreboard() { cout << "Not implemented\n"; }
void Course::exportScoreboard() { cout << "Not implemented\n"; }