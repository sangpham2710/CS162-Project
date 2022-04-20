#include "Course.h"

#include <fstream>
#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Semester.h"
#include "Student.h"
#include "Utils.h"

using std::cout;
using std::ifstream;
using std::ofstream;

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
  stream >> course.session1;
  stream >> course.session2;
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
  stream << course.session1 << '\n';
  stream << course.session2 << '\n';
  stream << course.pSemester->_id << '\n';
  stream << course.pStudents.size() << '\n';
  for (const auto& p : course.pStudents) stream << p->_id << '\n';
  return stream;
}

void Course::courseMainMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  int i = 1;
  Utils::printLine();
  for (const auto& crs : App::pCurrentSemester->pCourses) {
    cout << i << ". " << crs->courseCode << "\n";
    ++i;
  }
  Utils::printLine();
  cout << i << ". "
       << "Add new course \n";
  Utils::printLine();
  cout << 0 << ". "
       << "Return\n\n";

  // Handle options
  int option = Utils::getOption(0, i + 1);
  if (option >= 1 && option <= i - 1) {
    int index = option - 1;
    Course* pCourse = App::pCurrentSemester->pCourses[index];
    pCourse->courseChooseMenu();
    return;
  }
  if (option == i) {
    Course::createCourse();
    return;
  }
  if (option == 0) {
    Menu::staffMenu();
    return;
  }
}

void Course::courseChooseMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Update course \n";
  cout << "2. View students \n";
  cout << "3. Delete course \n";
  cout << "4. Import scoreboard \n";
  cout << "5. Export scoreboard \n";
  cout << "6. Export list students \n";
  cout << "7. Import list students \n";
  Utils::printLine();
  cout << "0. Return \n\n";

  int option = Utils::getOption(0, 7);
  switch (option) {
    case 0: {
      Course::courseMainMenu();
      break;
    }
    case 1: {
      this->courseUpdateMenu();
      break;
    }
    case 2: {
      this->viewStudentScoreboard();
      break;
    }
    case 3: {
      this->deleteCourseScene();
      break;
    }
    case 4: {
      this->importScoreboard();
      break;
    }
    case 5: {
      this->exportScoreboard();
      break;
    }
    case 6: {
      this->exportStudents();
    }
    case 7: {
      this->importStudents();
      break;
    }
  }
}

void Course::courseUpdateMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Update course information \n";
  cout << "2. Update student \n";
  cout << "3. Update student scoreboard \n";
  Utils::printLine();
  cout << "0. Return\n\n";

  int option = Utils::getOption(0, 3);
  switch (option) {
    case 1: {
      this->updateCourseInfo();
      break;
    }
    case 2: {
      this->courseUpdateStudentMenu();
      break;
    }
    case 3: {
      this->updateStudentScoreBoard();
      break;
    }
    case 0: {
      this->courseChooseMenu();
      break;
    }
  }
}

void Course::courseUpdateStudentMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Add student to course \n";
  cout << "2. Remove student from course \n";
  Utils::printLine();
  cout << "0. Return \n \n";

  int option = Utils::getOption(0, 2);

  switch (option) {
    case 1: {
      // add student
      this->addStudent();
      break;
    }
    case 2: {
      // remove student
      this->removeStudent();
      break;
    }
    case 0: {
      // return
      this->courseUpdateMenu();
      break;
    }
  }
}

void Course::createCourse() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  if (!App::pCurrentSemester) {
    cout << "Please create a semester first!\n";
    Utils::waitForKeypress();
    Menu::staffMenu();
    return;
  }

  cout << "This new course will be taught in ";
  cout << App::pCurrentSemester->pSchoolYear->yearName << " "
       << App::pCurrentSemester->semesterName;
  cout << "\n";

  string courseCode;
  cout << "Input course code: ";
  cin >> courseCode;
  if (App::pCurrentSemester->pCourses.find_if([&](const auto& p) -> bool {
        return p->courseCode == courseCode;
      }) != App::pCurrentSemester->pCourses.end()) {
    cout << "Current semester already has course " << courseCode << '\n';
    Utils::waitForKeypress();
    Course::courseMainMenu();
    return;
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

  cout << "\nInput schedule: ";
  Utils::getSchedule(pCourse->session1, pCourse->session2);

  pCourse->pSemester = App::pCurrentSemester;
  App::pCurrentSemester->pCourses.push_back(pCourse);
  App::pCourses.push_back(pCourse);

  cout << "\nCreated successfully!\n";
  Utils::waitForKeypress();
  courseMainMenu();
}

void Course::updateCourseInfo() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Course code: " << this->courseCode << "\n";
  cout << "2. Course name: " << this->courseName << "\n";
  cout << "3. Lecturer: " << this->lecturer << "\n";
  cout << "4. Start date: " << this->startDate << "\n";
  cout << "5. End date: " << this->endDate << "\n";
  cout << "6. Max number of students: " << this->maxNumberOfStudents << "\n";
  cout << "7. Number of credits: " << this->numberOfCredits << "\n";

  string schedule;
  Utils::convertIntScheduleToString(this->session1, this->session2, schedule);

  cout << "8. Schedule: " << schedule << "\n";
  Utils::printLine();
  cout << "0. Return\n\n";
  cout << "Which one do you want to update? \n";
  int option = Utils::getOption(0, 8);

  switch (option) {
    case 0: {
      this->courseChooseMenu();
      return;
    }
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
      Utils::getSchedule(this->session1, this->session2);
      break;
    }
  }
  cout << "\nSuccessfully changed information!\n";

  Utils::waitForKeypress();
  this->courseUpdateMenu();
}

void Course::addStudent() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  string studentCode;
  cout << "Input studentID: ";
  cin >> studentCode;

  for (const auto& p : this->pStudents) {
    cout << p->studentCode << '\n';
  }

  if (this->pStudents.find_if([&](const auto& p) -> bool {
        return p->studentCode == studentCode;
      }) != this->pStudents.end()) {
    cout << "\n" << this->courseCode << " already has this student!\n";
    Utils::waitForKeypress();
    this->courseUpdateStudentMenu();
    return;
  }
  auto itStudent = App::pStudents.find_if(
      [&](const auto& p) -> bool { return p->studentCode == studentCode; });
  if (itStudent == App::pStudents.end()) {
    cout << "\nThis student doesn't exist!\n";
    Utils::waitForKeypress();
    this->courseUpdateStudentMenu();
    return;
  }
  auto pStudent = *itStudent;
  this->pStudents.push_back(pStudent);
  CourseMark courseMark;
  courseMark.pCourse = this;
  pStudent->courseMarks.push_back(courseMark);
  cout << "\nAdd successfully!\n";
  Utils::waitForKeypress();
  this->courseUpdateStudentMenu();
}

void Course::removeStudent() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  if (!this->pStudents.size()) {
    cout << "This course is empty!";
    Utils::waitForKeypress();
    this->courseUpdateStudentMenu();
    return;
  }

  string studentCode;
  cout << "Input studentID: ";
  cin >> studentCode;

  auto itStudent = this->pStudents.find_if(
      [&](const auto& p) -> bool { return p->studentCode == studentCode; });

  if (itStudent == this->pStudents.end()) {
    cout << "\nThis student doesn't exits in this course!\n";
    Utils::waitForKeypress();
  } else {
    auto itCourseMark =
        (*itStudent)->courseMarks.find_if([&](const auto& courseMark) -> bool {
          return courseMark.pCourse->_id == this->_id;
        });

    (*itStudent)->courseMarks.remove(itCourseMark);
    this->pStudents.remove(itStudent);

    cout << "\nRemove successfully!\n";
  }
  this->courseUpdateStudentMenu();
  return;
}

void Course::updateStudentScoreBoard() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  if (!this->pStudents.size()) {
    cout << "This course is empty!";
    Utils::waitForKeypress();
    return;
  }

  string studentCode;
  cout << "Input studentID: ";
  cin >> studentCode;
  auto itStudent = this->pStudents.find_if(
      [&](const auto& p) -> bool { return p->studentCode == studentCode; });

  if (itStudent == this->pStudents.end()) {
    cout << "\nThis student doesn't exits in this course!\n";
    Utils::waitForKeypress();
    this->courseUpdateMenu();
    return;
  }
  auto pStudent = *itStudent;
  Utils::printLine();
  cout << pStudent->studentCode << "_" << pStudent->firstName << " "
       << pStudent->lastName << endl;

  auto itCourseMark =
      pStudent->courseMarks.find_if([&](const auto& courseMark) -> bool {
        return courseMark.pCourse->_id == this->_id;
      });
  cout << "1. Midterm: " << itCourseMark->midtermMark << endl;
  cout << "2. Final: " << itCourseMark->finalMark << endl;
  cout << "3. Other: " << itCourseMark->otherMark << endl;
  cout << "4. Total: " << itCourseMark->totalMark << endl;
  Utils::printLine();
  cout << "0. Return\n\n";
  cout << "Which one do you want to update? \n";
  int option = Utils::getOption(0, 4);
  switch (option) {
    case 0: {
      this->courseUpdateMenu();
      return;
    }
    case 1: {
      cout << "\nInput new midterm mark: ";
      cin >> itCourseMark->midtermMark;
      break;
    }
    case 2: {
      cout << "\nInput new final mark: ";
      cin >> itCourseMark->finalMark;
      break;
    }
    case 3: {
      cout << "\nInput new other mark: ";
      cin >> itCourseMark->otherMark;
      break;
    }
    case 4: {
      cout << "\nInput new total mark: ";
      cin >> itCourseMark->midtermMark;
      break;
    }
  }
  cout << "\nUpdate successfully!\n";

  Utils::waitForKeypress();
  this->courseUpdateMenu();
}

void Course::deleteCourseScene() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "Are you sure?, " << this->courseCode << " will be deleted in "
       << App::pCurrentSemester->pSchoolYear->yearName << "-"
       << App::pCurrentSemester->semesterName << endl;
  cout << "1. Yes\n";
  cout << "2. No\n \n";
  int option = Utils::getOption(1, 2);
  if (option == 2) {
    this->courseChooseMenu();
    return;
  }
  if (option == 1) {
    this->deleteCourse(0);

    cout << "\nDelete course successfully!\n";
    Utils::waitForKeypress();
    Course::courseMainMenu();
    return;
  }
}

void Course::deleteCourse(bool cascade) {
  for (const auto& p : this->pStudents) {
    p->courseMarks.remove_if([&](const auto& pCourseMark) -> bool {
      return pCourseMark.pCourse->_id == this->_id;
    });
  }

  if (!cascade) {
    this->pSemester->pCourses.remove_if(
        [&](const auto& p) -> bool { return p->_id == this->_id; });
  }

  auto it1 = App::pCourses.find_if(
      [&](const auto& p) -> bool { return p->_id == this->_id; });
  delete *it1;
  App::pCourses.remove(it1);
}

void Course::viewStudentScoreboard() {
  Console::clear();
  Utils::getCurrentSemester();
  int i = 1;
  Utils::printLine();
  for (const auto& p : this->pStudents) {
    cout << i << ". " << p->firstName << " " << p->lastName << "-"
         << p->studentCode << endl;
    for (const auto& pCourseMark : p->courseMarks) {
      if (pCourseMark.pCourse->_id == this->_id) {
        cout << "Midterm: " << pCourseMark.midtermMark << endl;
        cout << "Final: " << pCourseMark.finalMark << endl;
        cout << "Other: " << pCourseMark.otherMark << endl;
        cout << "Total: " << pCourseMark.totalMark << endl;
      }
    }
    Utils::printLine();
    ++i;
  }
  Utils::waitForKeypress();
  this->courseChooseMenu();
  return;
}

void Course::importScoreboard() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ifstream ifs(path);
  if (!ifs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->courseChooseMenu();
    return;
  }
  string line;
  getline(ifs, line);
  while (getline(ifs, line)) {
    int no;
    string studentCode, fullName;
    double otherMark, midtermMark, finalMark, totalMark;
    CSV::readLine(line, no, studentCode, fullName, otherMark, midtermMark,
                  finalMark, totalMark);
    for (const auto& p : this->pStudents) {
      if (p->studentCode == studentCode) {
        auto itCourseMark =
            p->courseMarks.find_if([&](const auto& courseMark) -> bool {
              return courseMark.pCourse->_id == this->_id;
            });
        if (itCourseMark == p->courseMarks.end()) continue;
        itCourseMark->otherMark = otherMark;
        itCourseMark->midtermMark = midtermMark;
        itCourseMark->finalMark = finalMark;
        itCourseMark->totalMark = totalMark;
      }
    }
  }
  ifs.close();
  cout << "Imported successfully\n";
  Utils::waitForKeypress();
  this->courseChooseMenu();
}

void Course::exportScoreboard() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ofstream ofs(path);
  if (!ofs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->courseChooseMenu();
    return;
  }
  int no = 0;
  string line;
  line = CSV::writeLine("No", "Student ID", "Full Name", "Other Mark",
                        "Midterm Mark", "Final Mark", "Total Mark");
  ofs << line << '\n';
  for (const auto& p : this->pStudents) {
    auto itCourseMark =
        p->courseMarks.find_if([&](const auto& courseMark) -> bool {
          return courseMark.pCourse->_id == this->_id;
        });
    line =
        CSV::writeLine(++no, p->studentCode, p->lastName + " " + p->firstName,
                       itCourseMark->otherMark, itCourseMark->midtermMark,
                       itCourseMark->finalMark, itCourseMark->totalMark);
    ofs << line << '\n';
  }
  ofs.close();
  cout << "Exported successfully\n";
  Utils::waitForKeypress();
  this->courseChooseMenu();
}

void Course::importStudents() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ifstream ifs(path);
  if (!ifs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->courseChooseMenu();
    return;
  }
  string line;
  getline(ifs, line);
  while (getline(ifs, line)) {
    int no;
    string studentCode, fullName;
    CSV::readLine(line, no, studentCode, fullName);
    auto itStudent = App::pStudents.find_if(
        [&](const auto& p) -> bool { return p->studentCode == studentCode; });
    if (itStudent != App::pStudents.end())
      this->pStudents.push_back(*itStudent);
  }
  ifs.close();
  cout << "Imported successfully\n";
  Utils::waitForKeypress();
  this->courseChooseMenu();
}

void Course::exportStudents() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  string path;
  cout << "Input CSV file path: ";
  cin.ignore();
  getline(cin, path);
  ofstream ofs(path);
  if (!ofs.is_open()) {
    cout << "Could not open CSV file\n";
    Utils::waitForKeypress();
    this->courseChooseMenu();
    return;
  }
  string line;
  line = CSV::writeLine("No", "Student ID", "Full Name");
  ofs << line << '\n';
  int no = 0;
  for (const auto& p : this->pStudents) {
    line =
        CSV::writeLine(++no, p->studentCode, p->lastName + " " + p->firstName);
    ofs << line << '\n';
  }
  ofs.close();
  cout << "Exported successfully\n";
  Utils::waitForKeypress();
  this->courseChooseMenu();
}

void Course::enrollUnenrollCourse() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  bool isEnrolling = App::pCurrentUser->pStudent->courseMarks.find_if(
                         [&](const auto& courseMark) -> bool {
                           return this->_id == courseMark.pCourse->_id;
                         }) == App::pCurrentUser->pStudent->courseMarks.end();
  cout << "Do you want to " << (isEnrolling ? "enroll" : "unenroll")
       << " course " << this->courseCode << "?\n";
  cout << "1. Yes\n";
  cout << "2. No\n";
  int option = Utils::getOption(1, 2);
  if (option == 1) {
    if (!App::courseRegistrationSession.isOpen()) {
      cout << "Sorry the registration session has already closed!\n";
      Utils::waitForKeypress();
      Menu::studentMenu();
      return;
    }
    if (isEnrolling) {
      auto recentSemesterCourseMarks =
          App::pCurrentUser->pStudent->courseMarks.filter(
              [&](const auto& courseMark) -> bool {
                return courseMark.pCourse->pSemester->_id ==
                       App::pRecentSemester->_id;
              });
      auto itScheduleConflictingCourseMark = recentSemesterCourseMarks.find_if(
          [&](const auto& courseMark) -> bool {
            return courseMark.pCourse->session1 == this->session1 ||
                   courseMark.pCourse->session2 == this->session1 ||
                   courseMark.pCourse->session1 == this->session2 ||
                   courseMark.pCourse->session2 == this->session2;
          });
      bool scheduleConflict =
          itScheduleConflictingCourseMark != recentSemesterCourseMarks.end();
      if (scheduleConflict) {
        cout << "Cannot enroll in this course because there is a schedule "
                "conflict with the course "
             << itScheduleConflictingCourseMark->pCourse->courseCode << "!\n";
        Utils::waitForKeypress();
        App::pCurrentUser->pStudent->enrollUnenrollCourseScene();
        return;
      }
      CourseMark courseMark;
      courseMark.pCourse = this;
      App::pCurrentUser->pStudent->courseMarks.push_back(courseMark);

      this->pStudents.push_back(App::pCurrentUser->pStudent);
      cout << "Enrolled successfully!\n";
      Utils::waitForKeypress();
      App::pCurrentUser->pStudent->enrollUnenrollCourseScene();
      return;
    } else {
      App::pCurrentUser->pStudent->courseMarks.remove_if(
          [&](const auto& courseMark) -> bool {
            return courseMark.pCourse->_id == this->_id;
          });
      this->pStudents.remove_if([&](const auto& p) -> bool {
        return p->_id == App::pCurrentUser->pStudent->_id;
      });
      cout << "Unenrolled successfully!\n";
      Utils::waitForKeypress();
      App::pCurrentUser->pStudent->enrollUnenrollCourseScene();
      return;
    }
  } else {
    Menu::studentMenu();
    return;
  }
}

void Course::displayCourse() {
  Utils::printLine();
  cout << this->courseCode << " - " << this->courseName << '\n';
  cout << "Lecturer: " << this->lecturer << '\n';
  cout << "Start date: " << this->startDate << '\n';
  cout << "End date: " << this->endDate << '\n';
  cout << "Maximum number of students: " << this->maxNumberOfStudents << '\n';
  cout << "Number of credits: " << this->numberOfCredits << '\n';
  cout << "Sessions: " << this->session1 << ' ' << this->session2 << '\n';
  cout << "Number of students: " << this->pStudents.size() << '\n';
}