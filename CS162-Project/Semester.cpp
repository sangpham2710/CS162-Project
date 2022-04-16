#include "Semester.h"

#include <iostream>

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "SchoolYear.h"
#include "Utils.h"

using std::cin;
using std::cout;

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

void Semester::addCourse(Course* const& course) {
  cout << "Not implemented\n";
}
void Semester::viewCourse(const string& courseID) {
  cout << "Not implemented\n";
}

#define bug(x) cout << #x << ": " << x << '\n'

void Semester::deleteSemester() {
  // need to also delete all the courses associate with this
  auto itSemester = App::pSemesters.find_if(
      [&](const auto& p) { return p->_id == this->_id; });
  cout << "Semester " << this->semesterName << " in school year "
       << this->pSchoolYear->yearName << "has been deleted\n";
  delete *itSemester;
  App::pSemesters.remove(itSemester);
}

void Semester::updateSemester() {
  Console::clear();
  cout << "--------------------\n";
  cout << "1. Change semester name\n";
  cout << "0. Go back\n";
  cout << "--------------------\n";
  int option = Utils::getOption(0, 1);

  auto semesterExisted = [&](const List<Semester*>& l,
                             const string& semesterName) -> bool {
    return this->pSchoolYear->pSemesters.find_if([&](const auto& p) -> bool {
      return p->semesterName == semesterName;
    }) == this->pSchoolYear->pSemesters.end();
  };
  switch (option) {
    case 1: {
      Console::clear();
      cout << "--------------\n";
      cout << "1. Fall\n";
      cout << "2. Spring\n";
      cout << "3. Summer\n";
      cout << "--------------\n";
      int choiceName = Utils::getOption(1, 3);
      switch (choiceName) {
        case 1:  // Fall
          if (semesterExisted(this->pSchoolYear->pSemesters, "Fall")) {
            cout << "This semester existed!\n";
            return;
          }
          this->semesterName = "Fall";
          break;
        case 2:  // Spring
          if (semesterExisted(this->pSchoolYear->pSemesters, "Spring")) {
            cout << "This semester existed!\n";
            return;
          }
          this->semesterName = "Spring";
          break;
        case 3:  // Summer
          if (semesterExisted(this->pSchoolYear->pSemesters, "Summer")) {
            cout << "This semester existed!\n";
            return;
          }
          this->semesterName = "Summer";
          break;
      }
    }
      this->viewEditSemester();
      break;
    case 0:
      this->viewEditSemester();
      break;
  }
}

void Semester::viewEditSemester() {
  Console::clear();
  cout << "Semester: " << this->pSchoolYear->yearName << ": "
       << this->semesterName << '\n';
  cout << "-----------------------\n";
  cout << "1. Update semester\n";
  cout << "2. Delete semester\n";
  cout << "0. Go back\n";
  cout << "-----------------------\n";

  int option = Utils::getOption(0, 2);
  switch (option) {
    case 1:
      this->updateSemester();
      break;
    case 2:
      this->deleteSemester();
      break;
    case 0:
      viewMainMenu();
      break;
  }
}

void Semester::createSemester() {
    Console::clear();

    cout << "-----------------------\n";
    int i = 1;
    for (const auto& p : App::pSchoolYears) {
        cout << i << ". " << p->yearName << endl;
        ++i;
    }
    cout << "0. Go back\n";
    cout << "-----------------------\n";
    int option = Utils::getOption(0, i - 1);
    if (option == 0) {
        Semester::viewMainMenu();
        return;
    }
    else {
        Console::clear();

        List <Semester*> sem;
        for (const auto& p : App::pSchoolYears[option - 1]->pSemesters) {
            sem.push_back(p);
        }
        if (sem.empty()) cout << App::pSchoolYears[option - 1]->yearName;
        else cout << App::pSchoolYears[option - 1]->yearName << "(";
        for (int i = 0; i < sem.length(); ++i) {
            if (i == sem.length() - 1) {
                cout << sem[i]->semesterName << ")";
            }
            else cout << sem[i]->semesterName << "-";
        }
        cout << "\n-----------------------\n";
        List <string> tmp = { "Autumn", "Spring", "Summer" };
        if (sem.length() != 3) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < sem.length(); ++j) {
                    if (tmp[i] == sem[j]->semesterName) tmp.remove(tmp[i]);
                }
            }
            int i = 0;
            for (; i < tmp.length(); ++i) {
                cout << i + 1 << ". " << tmp[i] << endl;
            }
        }
        cout << "0. Go back\n";
        cout << "-----------------------\n";
        int option1 = Utils::getOption(0, i);
        if (option1 == 0) {
            Semester::viewMainMenu();
            return;
        }
        else {
            Semester* semester = new Semester();
            semester->semesterName = tmp[option1 - 1];
            semester->pSchoolYear = App::pSchoolYears[option - 1];
            App::pSchoolYears[option - 1]->pSemesters.push_back(semester);
            App::pSemesters.push_back(semester);

            cout << "The semester has been created successfully!\n";
            Utils::waitForKeypress();
            Semester::viewMainMenu();
            return;
        }
    }
}

void Semester::viewMainMenu() {
  Console::clear();
  cout << "----------------------\n";
  int i = 1;
  for (const auto& p : App::pSemesters) {
    cout << i << ". " << p->pSchoolYear->yearName << ": ";
    cout << p->semesterName << endl;
    ++i;
  }
  cout << i << ". "
       << "Create new semester\n";
  cout << "0. Go back\n";
  cout << "----------------------\n";
  int option = Utils::getOption(0, i);
  if (option == i) {
    Semester::createSemester();
    return;
  } else if (1 <= option && option < i) {
    App::pSemesters[option - 1]->viewEditSemester();
    return;
  } else {
    Menu::staffMenu();
  }
}

void Semester::changeDefaultSemester() {
  Console::clear();
  cout << "Default semester: " << App::pCurrentSemester->semesterName << "-"
       << App::pCurrentSemester->pSchoolYear->yearName << endl;
  cout << "---------------------------------\n";
  int i = 1;
  for (const auto& p : App::pSchoolYears) {
    cout << i << ". " << p->yearName << endl;
    ++i;
  }
  cout << "0. Go back\n";
  cout << "---------------------------------\n";
  int option = Utils::getOption(0, i - 1);
  if (option == 0) {
    Menu::staffMenu();
    return;
  }
  else {
    Console::clear();
    cout << "Default semester: " << App::pCurrentSemester->semesterName << "-"
        << App::pCurrentSemester->pSchoolYear->yearName << endl;
    cout << "---------------------------------\n";
    i = 1;
    for (const auto& p : App::pSchoolYears[option - 1]->pSemesters) {
        cout << i << ". " << p->semesterName << endl;
        ++i;
    }
    cout << "0. Go back\n";
    cout << "---------------------------------\n";
    int option1 = Utils::getOption(0, i - 1);
    if (option1 == 0) {
        Menu::staffMenu();
        return;
    }
    else {
        App::pCurrentSemester = App::pSchoolYears[option - 1]->pSemesters[option1 - 1];
        cout << "Successfully changed default semester\n";
        Utils::waitForKeypress();
        Menu::staffMenu();
        return;
    }
  }
}