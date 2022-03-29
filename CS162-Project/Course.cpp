#include "Course.h"

#include <iostream>

#include "Console.h"
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
    Console::clear();

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

void Course::choose(Course* pCourse, short screen, short option) {

    if (screen == 1) { // mainCourseMenu
        if (option >= 1 && option < App::pCurrentSemester->pCourses.size()) {
            Course* pCourse = App::pCurrentSemester->pCourses[option - 1];
            pCourse->courseChooseMenu();
        }
        if (option == App::pCurrentSemester->pCourses.size()) {
            create();
        }
        if (option == App::pCurrentSemester->pCourses.size() + 1) {
            // return;
        }
        else {
            cout << "Invalid!";
        }
    }

    if (screen == 2) { // chooseCourseMenu
        switch (option) {
            case 1: {
                // update course
                pCourse->courseUpdateMenu();
                break;
            }
            case 2: {
                // view students
                break;
            }
            case 3: {
                // delete course
                break;
            }
            case 4: {
                // import scoreboard
                break;
            }
            case 5: {
                // export scoreboard
                break;
            }
            case 6: {
                // export list students
            }
            case 7: {
                // import list students
                break;
            }
            case 8: {
                // return previous menu
                courseMainMenu();
                break;
            }
        }
    }

    if (screen == 3) { // updateCourseMenu
        switch (option) {
            case 1: {
                // update course information
                pCourse->updateCourseInfo();
                break;
            }
            case 2: {
                // update student
                pCourse->courseUpdateStudentMenu();
                break;
            }
            case 3: {
                // update student scoreboard
                pCourse->updateStudentScoreBoard();
                break;
            }
        }
    }

    if (screen == 4) { // updateStudentMenu
        switch (option) {
            case 1: {
                // add student

                break;
            }
            case 2: {
                // remove student

                break;
            }
        }
    }

    if (screen == 5) { // deleteCourseMenu
        switch (option) {
            case 1: {
                // delete Course
                pCourse->deleteCourse();
                break;
            }
            case 2 :{
                // return
                pCourse->courseChooseMenu();
                break;
            }
        }
    }
}

void Course::updateCourseInfo() {
    Console::clear();

    cout << "1. Course code: " << this->courseCode << "\n";
    cout << "2. Course name: " << this->courseName << "\n";
    cout << "3. Lecturer: " << this->lecturer << "\n";
    cout << "4. Start date: " << this->startDate << "\n";
    cout << "5. End date: " << this->endDate << "\n";
    cout << "6. Max number of students: " << this->maxNumberOfStudents << "\n";
    cout << "7. Number of credits: " << this->numberOfCredits << "\n";
    cout << "8. Schedule: " << this->schedule << "\n" << "\n";

    cout << "Which one do you want to update? \n";
    cout << "Your choice: ";
    short option;
    cin >> option;
    switch (option) {
        case 1: {
            cout << "New course code: ";
            cin >> this->courseCode;
            break;
        }
        case 2: {
            cout << "New course name: ";
            cin >> this->courseName;
            break;
        }
        case 3: {
            cout << "New lecturer: ";
            cin.ignore();
            getline(cin, this->lecturer);
            break;
        }
        case 4: {
            cout << "New start date: ";
            cin >> this->startDate;
            break;
        }
        case 5: {
            cout << "New end date: ";
            cin >> this->endDate;
            break;
        }
        case 6: {
            cout << "New max number of students: ";
            cin >> this->maxNumberOfStudents;
            break;
        }
        case 7: {
            cout << "New number of credits: ";
            cin >> this->numberOfCredits;
            break;
        }
        case 8: {
            cout << "New schedule: ";
            cin >> this->schedule;
            break;
        }
    }
    cout << "\nsuccessfully changed information! \n";
    return;
}

void Course::courseMainMenu() {
    Console::clear();

    int i = 1;
    for (auto crs : App::pCurrentSemester->pCourses) {
        cout << i << ". " << crs->courseCode << "\n";
        ++i;
    }
    cout << "\n" << i << ". " << "Add new course \n";
    cout << i + 1 << ". " << "return \n \n";
    cout << "Your choice: ";

    short option;
    cin >> option;
    choose(NULL, 1, option);
}

void Course::courseChooseMenu() {
    Console::clear();

    cout << "1. Update course \n";
    cout << "2. View students \n";
    cout << "3. Delete course \n";
    cout << "4. Import scoreboard \n";
    cout << "5. Export scoreboard \n";
    cout << "6. Export list students \n";
    cout << "7. Import list students \n";
    cout << "8. Return \n \n";
    
    cout << "Your choice: ";
    short option;
    cin >> option;
    choose(this, 2, option);
}

void Course::courseUpdateMenu() {
    Console::clear();

    cout << "1. Update course information \n";
    cout << "2. Update student \n";
    cout << "3. Update student scoreboard \n";

    cout << "\nYour choice: ";
    short option;
    cin >> option;
    choose(this, 3, option);
}

void Course::courseUpdateStudentMenu() {

}

void Course::viewScoreboard() { cout << "Not implemented\n"; }
void Course::importScoreboard() { cout << "Not implemented\n"; }
void Course::exportScoreboard() { cout << "Not implemented\n"; }