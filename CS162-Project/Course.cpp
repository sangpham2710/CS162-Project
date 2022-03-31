#include "Course.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Semester.h"
#include "Student.h"

using std::cout;

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

void Course::choose(Course* pCourse, short screen, short option) {
  if (screen == 1) {  // mainCourseMenu
    if (option >= 1 && option <= App::pCurrentSemester->pCourses.size()) {
      Course* pCourse = App::pCurrentSemester->pCourses[option - 1];
      pCourse->courseChooseMenu();
      return;
    }
    if (option == App::pCurrentSemester->pCourses.size() + 1) {
      create();
      return;
    }
    if (option == App::pCurrentSemester->pCourses.size() + 2) {
      // return;
      Menu::staffMenu();
      return;
    }
  }

  if (screen == 2) {  // chooseCourseMenu
    switch (option) {
      case 1: {
        // update course
        pCourse->courseUpdateMenu();
        break;
      }
      case 2: {
        // view students
        pCourse->viewStudentScoreboard();
        break;
      }
      case 3: {
        // delete course
        pCourse->deleteCourse();
        break;
      }
      case 4: {
        // import scoreboard
        // pCourse->importScoreboard();
        break;
      }
      case 5: {
        // export scoreboard
        // pCourse->exportScoreboard();
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

  if (screen == 3) {  // updateCourseMenu
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
      case 4: {
        // back to courseChooseMenu
        pCourse->courseChooseMenu();
        break;
      }
    }
  }

  if (screen == 4) {  // updateStudentMenu
    switch (option) {
      case 1: {
        // add student
        pCourse->addStudent();
        break;
      }
      case 2: {
        // remove student
        pCourse->removeStudent();
        break;
      }
      case 3: {
        // retrun
        pCourse->courseUpdateMenu();
        break;
      }
    }
  }
}

void Course::courseMainMenu() {
  Console::clear();

  int i = 1;
  cout << "---------------------------------------\n";
  for (const auto& crs : App::pCurrentSemester->pCourses) {
    cout << i << ". " << crs->courseCode << "\n";
    ++i;
  }
  cout << "---------------------------------------\n";
  cout << i << ". "
       << "Add new course \n";
  cout << i + 1 << ". "
       << "return \n \n";
  cout << "Your choice: ";

  short option;
  cin >> option;
  while (option < 1 || option > i + 1) {
    cout << "\nInvalid!\n";
    cout << "Your choice: ";
    cin >> option;
  }
  choose(NULL, 1, option);
}

void Course::courseChooseMenu() {
  Console::clear();
  cout << "---------------------------------------\n";
  cout << "1. Update course \n";
  cout << "2. View students \n";
  cout << "3. Delete course \n";
  cout << "4. Import scoreboard \n";
  cout << "5. Export scoreboard \n";
  cout << "6. Export list students \n";
  cout << "7. Import list students \n";
  cout << "---------------------------------------\n";
  cout << "8. Return \n\n";

  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option < 1 || option > 8) {
    cout << "\nInvalid!\n";
    cout << "Your choice: ";
    cin >> option;
  }
  choose(this, 2, option);
}

void Course::courseUpdateMenu() {
  Console::clear();
  cout << "---------------------------------------\n";
  cout << "1. Update course information \n";
  cout << "2. Update student \n";
  cout << "3. Update student scoreboard \n";
  cout << "---------------------------------------\n";
  cout << "4. Return";

  cout << "\nYour choice: ";
  short option;
  cin >> option;
  while (option < 1 || option > 4) {
    cout << "\nInvalid!\n";
    cout << "Your choice: ";
    cin >> option;
  }
  choose(this, 3, option);
}

void Course::courseUpdateStudentMenu() {
  Console::clear();
  cout << "---------------------------------------\n";
  cout << "1. Add student to course \n";
  cout << "2. Remove student from course \n";
  cout << "---------------------------------------\n";
  cout << "3. Return \n \n";

  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option < 1 || option > 3) {
    cout << "\nInvalid!\n";
    cout << "Your choice: ";
    cin >> option;
  }
  choose(this, 4, option);
}

void Course::create() {
  Console::clear();

  if (!App::pCurrentSemester) {
    cout << "Please create a semester first \n";
    cin.ignore();
    cin.get();
    return;
  }

  cout << "This new course will be taught in ";
  cout << App::pCurrentSemester->pSchoolYear->yearName << " "
       << App::pCurrentSemester->semesterName;
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
  cout << "\nInput lecturer's name: ";
  getline(cin, pCourse->lecturer);
  cout << "\nInput start date: ";
  getline(cin, pCourse->startDate);
  cout << "\nInput end date: ";
  getline(cin, pCourse->endDate);
  cout << "\nInput max number of students: ";
  cin >> pCourse->maxNumberOfStudents;
  cout << "\nInput number of credits: ";
  cin >> pCourse->numberOfCredits;
  cout << "\nInput schedule (Ex: MON:S1/TUE:S2): ";
  cin >> pCourse->schedule;

  App::pCurrentSemester->pCourses.push_back(pCourse);
  App::pCourses.push_back(pCourse);

  cout << "\nCreated successfully!";
  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option;
  }
  courseMainMenu();
}

void Course::updateCourseInfo() {
  Console::clear();

  cout << "---------------------------------------\n";
  cout << "1. Course code: " << this->courseCode << "\n";
  cout << "2. Course name: " << this->courseName << "\n";
  cout << "3. Lecturer: " << this->lecturer << "\n";
  cout << "4. Start date: " << this->startDate << "\n";
  cout << "5. End date: " << this->endDate << "\n";
  cout << "6. Max number of students: " << this->maxNumberOfStudents << "\n";
  cout << "7. Number of credits: " << this->numberOfCredits << "\n";
  cout << "8. Schedule: " << this->schedule << "\n\n";
  cout << "---------------------------------------\n";
  cout << "Which one do you want to update? \n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option < 1 || option > 8) {
    cout << "\nInvalid!\n";
    cout << "Your choice: ";
    cin >> option;
  }

  // convert all to getline
  switch (option) {
    case 1: {
      cout << "New course code: ";
      cin.ignore();
      getline(cin, this->courseCode);
      break;
    }
    case 2: {
      cout << "New course name: ";
      cin.ignore();
      getline(cin, this->courseName);
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
  cout << "\nsuccessfully changed information!\n";

  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option1;
  cin >> option1;
  while (option1 != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option1;
  }
  this->courseUpdateMenu();
}

void Course::addStudent() {
  Console::clear();

  string studentID;
  cout << "Input studentID: ";
  cin >> studentID;
  for (auto crs : this->pStudents) {
    if (studentID == crs->studentCode) {
      cout << "\n" << this->courseCode << " already has this student!\n";
      cout << "\n1. Return\n";
      cout << "Your choice: ";
      short option;
      cin >> option;
      while (option != 1) {
        cout << "\nInvalid!";
        cout << "Your choice: ";
        cin >> option;
      }
      this->courseUpdateStudentMenu();
      return;
    }
  }
  for (auto stu : App::pStudents) {
    if (studentID == stu->studentCode) {
      this->pStudents.push_back(stu);
      CourseMark courseMark = CourseMark();
      courseMark.pCourse = this;
      stu->courseMarks.push_back(courseMark);
      cout << "\nAdd successfully!";

      cout << "\n1. Return\n";
      cout << "Your choice: ";
      short option;
      cin >> option;
      while (option != 1) {
        cout << "\nInvalid!";
        cout << "Your choice: ";
        cin >> option;
      }
      this->courseUpdateStudentMenu();
      return;
    }
  }
  cout << "\nThis student doesn't exist!";

  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option;
  }
  this->courseUpdateStudentMenu();
}

void Course::removeStudent() {
  Console::clear();

  if (!this->pStudents.size()) {
    cout << "This course is empty!";
    cout << "\n1. Return\n";
    cout << "Your choice: ";
    short option;
    cin >> option;
    while (option != 1) {
      cout << "\nInvalid!";
      cout << "Your choice: ";
      cin >> option;
    }
    this->courseUpdateStudentMenu();
    return;
  }

  string studentID;
  cout << "Input studentID: ";
  cin >> studentID;

  auto it = this->pStudents.find_if(
      [&](const auto& p) -> bool { return p->studentCode == studentID; });

  if (it == this->pStudents.end()) {
    cout << "\nThis student doesn't exits in this course!\n";
  }

  else {
    auto it1 = (*it)->courseMarks.find_if([&](const auto& courseMark) -> bool {
      return courseMark.pCourse->_id == this->_id;
    });

    (*it)->courseMarks.remove(it1);
    this->pStudents.remove(it);

    cout << "\nRemove successfully!\n";
  }
  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option;
  }
  this->courseUpdateStudentMenu();
  return;
}

void Course::updateStudentScoreBoard() {
  Console::clear();

  if (!this->pStudents.size()) {
    cout << "This course is empty!";
    return;
  }

  string studentID;
  cout << "Input studentID: ";
  cin >> studentID;
  for (auto p : this->pStudents) {
    if (p->studentCode == studentID) {
      cout << "---------------------------------------\n";
      cout << p->studentCode << "_" << p->firstName << " " << p->lastName
           << endl;
      for (auto& pCourseMarks : p->courseMarks) {
        if (pCourseMarks.pCourse == this) {
          cout << "1. Midterm: " << pCourseMarks.midtermMark << endl;
          cout << "2. Final: " << pCourseMarks.finalMark << endl;
          cout << "3. Other: " << pCourseMarks.otherMark << endl;
          cout << "4. Total: " << pCourseMarks.totalMark << endl;
          cout << "---------------------------------------\n";
          cout << "Which one do you want to update? \n";
          cout << "Your choice: ";
          short option;
          cin >> option;
          while (option < 1 || option > 4) {
            cout << "Invalid! \n";
            cout << "Your choice: ";
            cin >> option;
          }
          switch (option) {
            case 1: {
              cout << "\nInput new midterm mark: ";
              cin >> pCourseMarks.midtermMark;
              break;
            }
            case 2: {
              cout << "\nInput new final mark: ";
              cin >> pCourseMarks.finalMark;
              break;
            }
            case 3: {
              cout << "\nInput new other mark: ";
              cin >> pCourseMarks.otherMark;
              break;
            }
            case 4: {
              cout << "\nInput new total mark: ";
              cin >> pCourseMarks.midtermMark;
              break;
            }
          }
          cout << "\nUpdate successfully!\n";

          cout << "\n1. Return\n";
          cout << "Your choice: ";
          short option1;
          cin >> option1;
          while (option1 != 1) {
            cout << "\nInvalid!";
            cout << "Your choice: ";
            cin >> option1;
          }
          this->courseUpdateMenu();
          return;
        }
      }
    }
  }
  cout << "\nThis student doesn't exits in this course!";

  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option;
  }
  this->courseUpdateMenu();
}

void Course::deleteCourse() {
  Console::clear();

  cout << "Are you sure?, " << this->courseCode << " will be deleted in "
       << App::pCurrentSemester->pSchoolYear->yearName << "-"
       << App::pCurrentSemester->semesterName << endl;
  cout << "1. Yes\n";
  cout << "2. No\n \n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option < 1 || option > 2) {
    cout << "Invalid! \n";
    cout << "Your choice: ";
    cin >> option;
  }
  if (option == 2) {
    this->courseChooseMenu();
    return;
  }
  if (option == 1) {
    for (auto p : this->pStudents) {
      p->courseMarks.remove_if([&](const auto& pCourseMark) -> bool {
        return pCourseMark.pCourse->_id == this->_id;
      });
    }

    auto it = App::pCurrentSemester->pCourses.find_if(
        [&](const auto& p) -> bool { return p->_id == this->_id; });
    App::pCurrentSemester->pCourses.remove(it);

    auto it1 = App::pCourses.find_if(
        [&](const auto& p) -> bool { return p->_id == this->_id; });
    delete *it1;
    App::pCourses.remove(it1);

    cout << "\nDelete course successfully!\n";

    cout << "\n1. Return\n";
    cout << "Your choice: ";
    short option1;
    cin >> option1;
    while (option1 != 1) {
      cout << "\nInvalid!";
      cout << "Your choice: ";
      cin >> option1;
    }
    this->courseMainMenu();
    return;
  }
}

void Course::viewStudentScoreboard() {
  Console::clear();

  int i = 1;
  cout << "--------------------------------------" << endl;
  for (auto p : this->pStudents) {
    cout << i << ". " << p->firstName << " " << p->lastName << "-"
         << p->studentCode << endl;
    for (auto pCourseMark : p->courseMarks) {
      if (pCourseMark.pCourse == this) {
        cout << "Midterm: " << pCourseMark.midtermMark << endl;
        cout << "Final: " << pCourseMark.finalMark << endl;
        cout << "Other: " << pCourseMark.otherMark << endl;
        cout << "Total: " << pCourseMark.totalMark << endl;
      }
    }
    cout << "--------------------------------------" << endl;
    ++i;
  }
  cout << "\n1. Return\n";
  cout << "Your choice: ";
  short option;
  cin >> option;
  while (option != 1) {
    cout << "\nInvalid!";
    cout << "Your choice: ";
    cin >> option;
  }
  this->courseChooseMenu();
  return;
}

void Course::importScoreboard() { cout << "Not implemented\n"; }
void Course::exportScoreboard() { cout << "Not implemented\n"; }