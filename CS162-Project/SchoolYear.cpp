#include "SchoolYear.h"

#include "App.h"
#include "Console.h"
#include "Menu.h"
#include "Utils.h"

std::istream& operator>>(std::istream& stream, SchoolYear& schoolYear) {
  int n;
  stream >> schoolYear._id;
  stream.ignore();
  getline(stream, schoolYear.yearName);
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string semesterID;
    stream >> semesterID;
    schoolYear.pSemesters.push_back(*App::pSemesters.find_if(
        [&](const auto& p) { return p->_id == semesterID; }));
  }
  stream >> n;
  for (int i = 0; i < n; ++i) {
    string classID;
    stream >> classID;
    schoolYear.pClasses.push_back(*App::pClasses.find_if(
        [&](const auto& p) -> bool { return p->_id == classID; }));
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const SchoolYear& schoolYear) {
  stream << schoolYear._id << '\n';
  stream << schoolYear.yearName << '\n';
  stream << schoolYear.pSemesters.size() << '\n';
  for (const auto& p : schoolYear.pSemesters) stream << p->_id << '\n';
  stream << schoolYear.pClasses.size() << '\n';
  for (const auto& p : schoolYear.pClasses) stream << p->_id << '\n';
  return stream;
}

void SchoolYear::viewSchoolYearSemesterMenu() {
  Console::clear();

  cout << "---------------------------------------\n";
  cout << "1. School Years\n";
  cout << "2. Semesters\n";
  cout << "---------------------------------------\n";
  cout << "0. Return\n";
  int option = Utils::getOption(0, 2);
  switch (option) {
    case 0: {
      Menu::staffMenu();
      return;
    }
    case 1: {
      SchoolYear::viewMainMenu();
      return;
    }
    case 2: {
      Semester::viewMainMenu();
      return;
    }
  }
}

void SchoolYear::viewMainMenu() {
  Console::clear();

  int i = 1;
  cout << "---------------------------------------\n";
  for (const auto& p : App::pSchoolYears) {
    cout << i << ". " << p->yearName << "\n";
    ++i;
  }
  cout << "---------------------------------------\n";
  cout << i << ". "
       << "Add new school year \n";
  cout << 0 << ". "
       << "Return \n \n";


  int option = Utils::getOption(0, i);
  if (option == i) {
    SchoolYear::createSchoolYear();
    return;
  } else if (option == 0) {
    Menu::staffMenu();
    return;
  } else {
    App::pSchoolYears[option - 1]->schoolYearChooseMenu();
    return;
  }
}

void SchoolYear::schoolYearChooseMenu() {
  Console::clear();

  if (App::pSchoolYears.length() == 1) {
    cout << "---------------------------------------\n";
    cout << "1. Update school year\n";
    cout << "---------------------------------------\n";
    cout << "0. Return\n";

    int option = Utils::getOption(0, 1);
    switch (option) {
      case 0: {
        SchoolYear::viewMainMenu();
        return;
      }
      case 1: {
        // update school year
        this->schoolYearUpdate();
        return;
      }
    }
  } else {
    cout << "---------------------------------------\n";
    cout << "1. Update school year\n";
    cout << "2. Delete school year\n";
    cout << "---------------------------------------\n";
    cout << "0. Return\n";

    int option = Utils::getOption(0, 2);
    switch (option) {
      case 0: {
        SchoolYear::viewMainMenu();
        return;
      }
      case 1: {
        // update school year
        this->schoolYearUpdate();
        return;
      }
      case 2: {
        // delete school year
        this->deleteSchoolYearScene();
        return;
      }
    }
  }
}

void SchoolYear::createSchoolYear() {
  Console::clear();

  string yearName;
  cout << "School year (Ex:2022-2023): ";
  cin.ignore();
  getline(cin, yearName);
  if (yearName.length() != 9 || yearName[4] != '-') {
    cout << "Invalid\n";

    Utils::waitForKeypress();
    SchoolYear::viewMainMenu();
    return;
  }
  for (auto sy : App::pSchoolYears) {
    if (sy->yearName == yearName) {
      cout << "school year " << yearName << "already exists!";

      Utils::waitForKeypress();
      SchoolYear::viewMainMenu();
      return;
    }
  }

  string semesterName;
  cout << "Input first semester in " << yearName << ": ";
  getline(cin, semesterName);
  Semester* sem = new Semester();
  sem->semesterName = semesterName;

  SchoolYear* sy = new SchoolYear();
  sy->yearName = yearName;

  sy->pSemesters.push_back(sem);
  sem->pSchoolYear = sy;
  App::pSchoolYears.push_back(sy);
  App::pSemesters.push_back(sem);
  App::pCurrentSemester = sem;
  App::pRecentSemester = sem;

  cout << "Create school year " << yearName << " successfully!\n";
  Utils::waitForKeypress();
  SchoolYear::viewMainMenu();
  return;
}

void SchoolYear::deleteSchoolYearScene() {
  Console::clear();

  cout << "Are you sure you want to permanently delete this school year?\n";
  cout << "1. Yes\n";
  cout << "2. No\n";

  int option = Utils::getOption(1, 2);
  if (option == 2) {
    this->schoolYearChooseMenu();
    return;
  }
  string tmp = this->yearName;
  this->deleteSchoolYear();
  cout << "\nDelete school year " << tmp << " successfully!\n";
  Utils::waitForKeypress();
  SchoolYear::viewMainMenu();
}

void SchoolYear::deleteSchoolYear() {
  if (App::pCurrentSemester->pSchoolYear->_id == this->_id) {
    if (App::pSchoolYears.back()->_id == this->_id) {
      App::pCurrentSemester =
          App::pSchoolYears[App::pSchoolYears.length() - 2]->pSemesters.back();
    } else {
      App::pCurrentSemester = App::pSchoolYears.back()->pSemesters.back();
    }
  }
  App::pRecentSemester = App::pCurrentSemester;

  for (const auto& p : this->pSemesters) {
    p->deleteSemester(1);
  }

  auto it = App::pSchoolYears.find_if(
      [&](const auto& p) -> bool { return p->_id == this->_id; });
  delete *it;
  App::pSchoolYears.remove(it);
}

void SchoolYear::schoolYearUpdate() {
  Console::clear();
  cout << "1. Year name: " << this->yearName << '\n';
  cout << "0. Return\n";
  cout << "Which one do you want to update? \n";
  int option = Utils::getOption(0, 1);
  if (option == 0) {
    this->schoolYearChooseMenu();
    return;
  }

  cout << "Input new school year name: ";
  string yearName;
  cin.ignore();
  getline(cin, yearName);
  auto it = App::pSchoolYears.find_if(
      [&](const auto& p) -> bool { return p->yearName == yearName; });
  if (it == App::pSchoolYears.end()) {
    this->yearName = yearName;
    cout << "\nUpdated successfully! ";
  } else {
    cout << "\nThis school year already exists! ";
  }
  Utils::waitForKeypress();
  this->schoolYearChooseMenu();
  return;
}

void SchoolYear::displaySchoolYear() {
  cout << this->yearName << " - " << this->pSemesters.size() << " semesters - "
       << this->pClasses.size() << " classes\n";
}