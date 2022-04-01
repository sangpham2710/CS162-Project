#include "SchoolYear.h"

#include "App.h"
#include "Console.h"
#include "Menu.h"

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

void SchoolYear::choose(SchoolYear* pSchoolYear, short screen, short option) {
    if (screen == 1) { // schoolYearMainMenu
        if (option >= 1 && option <= App::pSchoolYears.size()) {
            App::pSchoolYears[option - 1]->schoolYearChooseMenu();
            return;
        }
        if (option == App::pSchoolYears.size() + 1) {
            create();
            return;
        }
        else {
            Menu::staffMenu();
            return;
        }
    }
    if (screen == 2) { // schoolYearChooseMenu
        switch (option) {
        case 0: {
            schoolYearMainMenu();
            break;
        }
        case 1: {

            break;
        }
        }
    }
}

void SchoolYear::SchoolYearSemesterMenu() {
    Console::clear();

    cout << "---------------------------------------\n";
    cout << "1. School Years\n";
    cout << "2. Semesters\n";
    cout << "---------------------------------------\n";
    cout << "0. Return\n";
    cout << "Your choice: ";
    short option;
    cin >> option;
    while (option < 0 || option > 2) {
        cout << "\nInvalid!\n";
        cout << "Your choice: ";
        cin >> option;
    }
    if (option == 0) {
        Menu::staffMenu;
    }
    if (option == 1) {
        schoolYearMainMenu();
        return;
    }
    if (option == 2) {

    }
}

void SchoolYear::schoolYearMainMenu() {
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
    cout << 0 << ". " << "Return \n \n";
    cout << "Your choice: ";

    short option;
    cin >> option;
    while (option < 0 || option > i) {
        cout << "\nInvalid!\n";
        cout << "Your choice: ";
        cin >> option;
    }
    choose(NULL, 1, option);
}

void SchoolYear::schoolYearChooseMenu() {
    Console::clear();

    cout << "---------------------------------------\n";
    cout << "1. Update school year\n";
    cout << "2. Delete school year\n";
    cout << "---------------------------------------\n";
    cout << "0. Return\n";

    cout << "Your choice: ";
    short option;
    cin >> option;
    while (option < 0 || option > 2) {
        cout << "\nInvalid!\n";
        cout << "Your choice: ";
        cin >> option;
    }

    choose(this, 2, option);
    return;
}

void SchoolYear::create() {
    Console::clear();

    string schoolYearName;
    cout << "School year (Ex:2022-2023): ";
    cin.ignore();
    getline(cin, schoolYearName);
    if (schoolYearName.length() != 9 || schoolYearName[4] != '-') {
        cout << "Invalid\n";
        cout << "\n0. Return\n";
        cout << "Your choice: ";
        short option1;
        cin >> option1;
        while (option1 != 0) {
            cout << "\nInvalid!";
            cout << "Your choice: ";
            cin >> option1;
        }
        schoolYearMainMenu();
        return;
    }
    for (auto sy : App::pSchoolYears) {
        if (sy->yearName == schoolYearName) {
            cout << "school year " << schoolYearName << "already exists!";
            cout << "\n0. Return\n";
            cout << "Your choice: ";
            short option1;
            cin >> option1;
            while (option1 != 0) {
                cout << "\nInvalid!";
                cout << "Your choice: ";
                cin >> option1;
            }
            schoolYearMainMenu();
            return;
        }
    }

    SchoolYear* sy = new SchoolYear();
    sy->yearName = schoolYearName;
    App::pSchoolYears.push_back(sy);
    cout << "Create school year " << schoolYearName << "successfully!";
    cout << "\n0. Return\n";
    cout << "Your choice: ";
    short option1;
    cin >> option1;
    while (option1 != 0) {
        cout << "\nInvalid!";
        cout << "Your choice: ";
        cin >> option1;
    }
    schoolYearMainMenu();
    return;
}