#include "Global.h"

List<User>::iterator Global::currentUser{nullptr};
List<Semester>::iterator Global::currentSemester{nullptr};
List<User> Global::allUsers{};
List<SchoolYear> Global::allSchoolYears{};