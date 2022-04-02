#pragma once

#include <string>

#include "Class.h"
#include "ID.h"
#include "List.h"
#include "Semester.h"

using std::string;

class SchoolYear {
public:
    string _id;
    string yearName;
    List<Semester*> pSemesters;
    List<Class*> pClasses;

    SchoolYear(const string& id)
        : _id{ id }, yearName{}, pSemesters{}, pClasses{} {}
    SchoolYear() : SchoolYear(ID::gen()) {}

    friend std::istream& operator>>(std::istream& stream, SchoolYear& schoolYear);
    friend std::ostream& operator<<(std::ostream& stream,
        const SchoolYear& schoolYear);

    static void SchoolYearSemesterMenu();
    static void choose(SchoolYear* pSchoolYear, short screen, short option);
    static void schoolYearMainMenu();
    static void create();

    void schoolYearChooseMenu();
    void schoolYearUpdate();
    void schoolYearDelete();
};