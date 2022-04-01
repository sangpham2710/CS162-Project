#include "Semester.h"

#include <iostream>

#include "App.h"
#include "SchoolYear.h"
#include "Console.h"
#include "Menu.h"

using std::cout;
using std::cin;

std::istream& operator>>(std::istream& stream, Semester& semester) {
  int n;
  stream >> semester._id;
  stream.ignore();
  getline(stream, semester.semesterName);
  string schoolYearID;
  stream >> schoolYearID;
  semester.pSchoolYear = *App::pSchoolYears.find_if(
      [&](const auto& p) -> bool { return p->_id == schoolYearID; });
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string courseID;
    stream >> courseID;
    semester.pCourses.push_back(*App::pCourses.find_if(
        [&](const auto& p) -> bool { return p->_id == courseID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const Semester& semester) {
  stream << semester._id << '\n';
  stream << semester.semesterName << '\n';
  stream << semester.pSchoolYear->_id << '\n';
  stream << semester.pCourses.size() << '\n';
  for (const auto& p : semester.pCourses) stream << p->_id << '\n';
  return stream;
}

void Semester::addCourse(Course* const& course) { cout << "Not implemented\n"; }
void Semester::viewCourse(const string& courseID) {
  cout << "Not implemented\n";
}

void Semester::updateSemester() {
  Console::clear();
  cout << "--------------------\n";
  cout << "1. Change semester name\n";
  cout << "0. Go back\n";
  cout << "--------------------\n";
  cout << "Input your choice: ";
  int choice;
  cin >> choice;
  switch (choice) {
    case 1: {
      Console::clear();
      cout << "--------------\n";
      cout << "1. Fall\n";
      cout << "2. Spring\n";
      cout << "3. Summer\n";
      cout << "--------------\n";
      cout << "Input your choice: ";
      int choiceName;
      cin >> choiceName;
      switch (choiceName) {
        case 1: //Fall
          /*for (auto sem: this->pSchoolYear->pSemesters) {
            if (sem->semesterName == "Fall") cout << "This semester existed!\n";
            return; 
          }*/
          this->semesterName = "Fall";
          break;
        case 2: //Spring
          /*for (auto sem : this->pSchoolYear->pSemesters) {
            if (sem->semesterName == "Spring") cout << "This semester existed!\n";
            return;
          }*/
          this->semesterName = "Spring";
          break;
        case 3: //Summer
          /*for (auto sem : this->pSchoolYear->pSemesters) {
            if (sem->semesterName == "Summer") cout << "This semester existed!\n";
            return;
          }*/
          this->semesterName = "Summer";
          break;

      }
    }
      this->viewEditSemester();
      break;
    case 0: 
      this->viewEditSemester();
      break;
    default:
      break;
  }
}

void Semester::viewEditSemester() { Console::clear();
  cout << "Semester: " << this->pSchoolYear->yearName << ": " << this->semesterName
       << '\n';
  cout << "-----------------------\n";
  cout << "1. Update semester\n";
  cout << "2. Delete semester\n";
  cout << "0. Go back\n";
  cout << "-----------------------\n";
  cout << "Input your choice: ";
  int choice;
  cin >> choice;
  switch (choice) {
    case 1:
      this->updateSemester();
      break;
    case 2:
      //this->deleteSemester();
      break;
    case 0:
      viewSemesterMenu();
      break;
  }

}

void Semester::create() {
  Console::clear();
  cout << "Which School year ? (E.g: 2021-2022)\n";
  string schoolYear;
  cin.ignore();
  getline(cin, schoolYear);
  for (auto p : App::pSchoolYears) {
    if (p->yearName == schoolYear) {
      cout << "--------------\n";
      cout << "1. Fall\n";
      cout << "2. Spring\n";
      cout << "3. Summer\n";
      cout << "--------------\n";
      cout << "Input your choice: ";
      int choice;
      cin >> choice;
      switch (choice)
      { case 1: //Fall
        {
          for (auto pSemes : p->pSemesters) {
            if (pSemes->semesterName == "Fall") {
              cout << "This semester has already existed!\n";
              cout << "Do you want to return ?\n";
              cout << "1. YES\n";
              cout << "--------------\n";
              int option;
              cin >> option;
              if (option == 1)
                viewSemesterMenu();
              else
                cout << "Invalid choice!\n";
              return;
            }
          }
          Semester* pSemester1 = new Semester();
          pSemester1->semesterName = "Fall";
          App::pSemesters.push_back(pSemester1);
          p->pSemesters.push_back(pSemester1);
          cout << "The semester has been created successfully!\n";
          break;
        }
        case 2: //Spring
        {
          for (auto pSemes : p->pSemesters) {
            if (pSemes->semesterName == "Spring") {
              cout << "This semester has already existed!\n";
              cout << "Do you want to return ?\n";
              cout << "1. YES\n";
              cout << "--------------\n";
              int option;
              cin >> option;
              if (option == 1)
                viewSemesterMenu();
              else
                cout << "Invalid choice!\n";
              return;
            } 
          }
          Semester* pSemester2 = new Semester();
          pSemester2->semesterName = "Spring";
          App::pSemesters.push_back(pSemester2);
          p->pSemesters.push_back(pSemester2);
          cout << "The semester has been created successfully!\n";
          break; 
        }
        case 3:  //Summer
        {
          for (auto pSemes : p->pSemesters) {
            if (pSemes->semesterName == "Summer") {
              cout << "This semester has already existed!\n";
              cout << "Do you want to return ?\n";
              cout << "1. YES\n";
              cout << "--------------\n";
              int option;
              cin >> option;
              if (option == 1)
                viewSemesterMenu();
              else
                cout << "Invalid choice!\n";
              return;
            }  
          }
          Semester* pSemester3 = new Semester();
          pSemester3->semesterName = "Summer";
          App::pSemesters.push_back(pSemester3);
          p->pSemesters.push_back(pSemester3);
          cout << "The semester has been created successfully!\n";
          break;
        }  
        default:
          cout << "Invalid choice !\n";
          break;
      }
    } 
  }
  cout << "Wrong school year !\n";
}
void Semester::choose(const int& choice, const int& i) {
  if (choice == i) {
    Semester::create();
  } else if (choice < i && choice >= 0) {
    App::pSemesters[choice]->viewEditSemester();
  } else if (choice == -1) {
    Menu::staffMenu();
  } else {
    cout << "This Semester does not exist";
  }
}

void Semester::viewSemesterMenu() {
  Console::clear();
  cout << "----------------------\n";
  int i = 0;
  for (const auto& p : App::pSemesters) {
    ++i;
    cout << i << ". " << p->pSchoolYear->yearName << ": ";
    cout << p->semesterName << endl;
  }
  cout << i + 1 << ". "
       << "Create new semester\n";
  cout << "0. Go back\n";
  cout << "----------------------\n";
  int choice;
  cout << "Input your choice: ";
  cin >> choice;
  choose(choice - 1, i);
}