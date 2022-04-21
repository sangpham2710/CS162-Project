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

void Semester::deleteSemesterScene() {
  string tmpSemesterName = this->semesterName;
  string tmpYearName = this->pSchoolYear->yearName;
  this->deleteSemester(0);
  cout << "Semester " << tmpSemesterName << " in school year " << tmpYearName
       << " has been deleted\n";

  Utils::waitForKeypress();
  Semester::viewMainMenu();
}

void Semester::deleteSemester(bool cascade) {
  for (const auto& p : this->pCourses) {
    p->deleteCourse(1);
  }

  if (!cascade) {
    this->pSchoolYear->pSemesters.remove_if(
        [&](const auto& p) { return p->_id == this->_id; });
  }

  auto itSemester = App::pSemesters.find_if(
      [&](const auto& p) { return p->_id == this->_id; });

  if (App::pCurrentSemester->_id == this->_id) {
    App::pCurrentSemester = App::pSchoolYears.back()->pSemesters.back();
  }
  App::pRecentSemester = App::pCurrentSemester;

  delete *itSemester;
  App::pSemesters.remove(itSemester);
}

void Semester::updateSemester() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "1. Change semester name\n";
  Utils::printLine();
  cout << "0. Return\n\n";
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
      Utils::getCurrentSemester();
      Utils::printLine();
      cout << "1. Fall\n";
      cout << "2. Spring\n";
      cout << "3. Summer\n";
      Utils::printLine();
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
  Utils::getCurrentSemester();
  Utils::printLine();
  cout << "Semester: " << this->pSchoolYear->yearName << ": "
       << this->semesterName << '\n';
  Utils::printLine();

  if (this->pSchoolYear->pSemesters.length() == 1) {
    cout << "1. Update semester\n";
    Utils::printLine();
    cout << "0. Return\n\n";
    int option = Utils::getOption(0, 1);
    switch (option) {
      case 1:
        this->updateSemester();
        break;
      case 0:
        viewMainMenu();
        break;
    }
  } else {
    cout << "1. Update semester\n";
    cout << "2. Delete semester\n";
    Utils::printLine();
    cout << "0. Return\n\n";

    int option = Utils::getOption(0, 2);
    switch (option) {
      case 1:
        this->updateSemester();
        break;
      case 2:
        this->deleteSemesterScene();
        break;
      case 0:
        viewMainMenu();
        break;
    }
  }
}

void Semester::createSemester() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  List<Semester*> sem;
  for (const auto& p : App::pCurrentSemester->pSchoolYear->pSemesters) {
    sem.push_back(p);
  }
  if (sem.empty())
    cout << App::pCurrentSemester->pSchoolYear->yearName;
  else
    cout << App::pCurrentSemester->pSchoolYear->yearName << "(";
  for (int i = 0; i < sem.length(); ++i) {
    if (i == sem.length() - 1) {
      cout << sem[i]->semesterName << ")";
    } else
      cout << sem[i]->semesterName << "-";
  }
  cout << "\n";
  Utils::printLine();
  List<string> tmp = {"Autumn", "Spring", "Summer"};
  int i = 1;
  bool check = false;
  for (int k = 0; k < tmp.length(); ++k) {
    check = false;
    for (int j = 0; j < sem.length(); ++j) {
      if (tmp[k] == sem[j]->semesterName) {
        check = true;
        tmp.remove(tmp[k]);
        --k;
        break;
      }
    }
    if (!check) {
      cout << i << ". " << tmp[k] << endl;
      ++i;
    }
  }
  Utils::printLine();
  cout << "0. Return\n\n";
  int option = Utils::getOption(0, i - 1);
  if (option == 0) {
    Semester::viewMainMenu();
    return;
  } else {
    Semester* semester = new Semester();
    semester->semesterName = tmp[option - 1];
    semester->pSchoolYear = App::pCurrentSemester->pSchoolYear;
    App::pCurrentSemester->pSchoolYear->pSemesters.push_back(semester);
    App::pSemesters.push_back(semester);
    App::pCurrentSemester = semester;
    App::pRecentSemester = semester;

    cout << "The semester has been created successfully!\n";
    Utils::waitForKeypress();
    Semester::viewMainMenu();
    return;
  }
}

void Semester::viewMainMenu() {
  Console::clear();
  Utils::getCurrentSemester();
  Utils::printLine();
  int i = 1;
  int option;
  for (const auto& p : App::pCurrentSemester->pSchoolYear->pSemesters) {
    cout << i << ". " << p->pSchoolYear->yearName << ": ";
    cout << p->semesterName << endl;
    ++i;
  }
  if (App::pCurrentSemester->pSchoolYear->_id == App::pSchoolYears.back()->_id) {
      cout << i << ". "
          << "Create new semester\n";
      Utils::printLine();
      cout << "0. Return\n\n";
      option = Utils::getOption(0, i);
  }
  else {
      Utils::printLine();
      cout << "0. Return\n\n";
      option = Utils::getOption(0, i - 1);
  }
  if (option == i) {
    Semester::createSemester();
    return;
  } else if (1 <= option && option < i) {
    App::pCurrentSemester->pSchoolYear->pSemesters[option - 1]
        ->viewEditSemester();
    return;
  } else {
    Menu::staffMenu();
  }
}

void Semester::changeDefaultSemester() {
  Console::clear();
  cout << "Default semester: " << App::pCurrentSemester->semesterName << " - "
       << App::pCurrentSemester->pSchoolYear->yearName << endl;
  Utils::printLine();
  int i = 1;
  for (const auto& p : App::pSchoolYears) {
    cout << i << ". " << p->yearName << endl;
    ++i;
  }
  Utils::printLine();
  cout << "0. Return\n\n";
  int option = Utils::getOption(0, i - 1);
  if (option == 0) {
    Menu::staffMenu();
    return;
  } else {
    Console::clear();
    cout << "Default semester: " << App::pCurrentSemester->semesterName << "-"
         << App::pCurrentSemester->pSchoolYear->yearName << endl;
    Utils::printLine();
    i = 1;
    for (const auto& p : App::pSchoolYears[option - 1]->pSemesters) {
      cout << i << ". " << p->semesterName << endl;
      ++i;
    }
    Utils::printLine();
    cout << "0. Return\n\n";
    int option1 = Utils::getOption(0, i - 1);
    if (option1 == 0) {
      Menu::staffMenu();
      return;
    } else {
      App::pCurrentSemester =
          App::pSchoolYears[option - 1]->pSemesters[option1 - 1];
      cout << "Successfully changed default semester\n";
      Utils::waitForKeypress();
      Menu::staffMenu();
      return;
    }
  }
}

void Semester::createFirstSemester() {
    Console::clear();
    Utils::getCurrentSemester();
    Utils::printLine();

    string yearName;
    cout << "School year (Ex: 2022-2023): ";
    cin.ignore();
    getline(cin, yearName);
    if (yearName.length() != 9 || yearName[4] != '-') {
        cout << "Invalid!\n";

        Utils::waitForKeypress();
        Menu::adminMenu();
        return;
    }

    cout << "Input first semester in " << yearName << ": ";
    cout << "\n1. Autumn      2. Spring       3.Summer\n";
    int option = Utils::getOption(1, 3);
    Semester* pSemester = new Semester();
    switch (option) {
        case 1: {
            pSemester->semesterName = "Autumn";
            break;
        }
        case 2: {
            pSemester->semesterName = "Spring";
            break;
        }
        case 3: {
            pSemester->semesterName = "Summer";
            break;
        }
    }

    SchoolYear* pSchoolYear = new SchoolYear();
    pSchoolYear->yearName = yearName;

    pSchoolYear->pSemesters.push_back(pSemester);
    pSemester->pSchoolYear = pSchoolYear;
    App::pSchoolYears.push_back(pSchoolYear);
    App::pSemesters.push_back(pSemester);
    App::pCurrentSemester = pSemester;
    App::pRecentSemester = pSemester;

    cout << "Created first semester " << pSemester->semesterName << " in " << yearName << " successfully!\n";
    Utils::waitForKeypress();
    Menu::adminMenu();
}

void Semester::displaySemester() {
  cout << this->pSchoolYear->yearName << " - " << this->semesterName << " - "
       << this->pCourses.size() << " courses\n";
}