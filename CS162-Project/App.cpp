#include "App.h"

#include <iostream>
#include <string>

#include "Console.h"
#include "Global.h"
#include "List.h"
#include "Menu.h"
#include "User.h"

using std::cin;
using std::cout;
using std::string;

void App::loadData() {
  Global::allUsers.push_back(User{"admin", "admin", UserType::ADMIN});
  Global::allUsers.push_back(User{"staff", "staff", UserType::ACADEMIC_STAFF});
  Global::allUsers.push_back(User{"student", "student", UserType::STUDENT});

  Student stu[5];
  stu[0].no = 1; stu[0].studentCode = "20280001"; stu[0].firstName = "Ho Ngoc"; stu[0].lastName = "An"; stu[0].gender = "Male"; stu[0].dateOfBirth = "25/5/2002"; stu[0].socialID = "157863159"; stu[0].classID = "20KDL1";
  stu[1].no = 2; stu[1].studentCode = "20280002"; stu[1].firstName = "Nguyen Dinh"; stu[1].lastName = "An"; stu[1].gender = "Female"; stu[1].dateOfBirth = "30/9/2002"; stu[1].socialID = "169536895"; stu[1].classID = "20KDL1";
  stu[2].no = 3; stu[2].studentCode = "20280003"; stu[2].firstName = "Nguyen Phuoc Hong"; stu[2].lastName = "An"; stu[2].gender = "Male"; stu[2].dateOfBirth = "16/12/2002"; stu[2].socialID = "326862365"; stu[2].classID = "20KDL1";
  stu[3].no = 4; stu[3].studentCode = "20280004"; stu[3].firstName = "Tran Hoang"; stu[3].lastName = "Anh"; stu[3].gender = "Male"; stu[3].dateOfBirth = "9/8/2002"; stu[3].socialID = "215964156"; stu[3].classID = "20KDL1";
  stu[4].no = 5; stu[4].studentCode = "20280005"; stu[4].firstName = "Nguyen Que"; stu[4].lastName = "Anh"; stu[4].gender = "Female"; stu[4].dateOfBirth = "6/11/2002"; stu[4].socialID = "546835432"; stu[4].classID = "20KDL1";
  for (int i = 0; i < 5; ++i) Global::allStudents.push_back(stu[i]);


  Course cou[5];
  cou[0].courseCode = "CS162"; cou[0].courseName = "Introduction to Computer Science II"; cou[0].lecturer = "Dinh Ba Tien"; cou[0].numberOfCredits = 4; cou[0].maxNumberOfStudents = 60; cou[0].schedule = "MON:S1/SAT:S3"; cou[0].startDate = "03/01"; cou[0].endDate = "27/05";
  cou[1].courseCode = "BAA00004"; cou[1].courseName = "Introduction to Laws"; cou[1].lecturer = "Nguyen Ngoc Phuong Hong"; cou[1].numberOfCredits = 3; cou[1].maxNumberOfStudents = 60; cou[1].schedule = "TUE:S3/TUE:S4"; cou[1].startDate = "03/01"; cou[1].endDate = "27/05";
  cou[2].courseCode = "BAA00102"; cou[2].courseName = "Marxist-Leninist Political Economics"; cou[2].lecturer = "Ngo Tuan Phuong"; cou[2].numberOfCredits = 2; cou[2].maxNumberOfStudents = 60; cou[2].schedule = "WED:S1/WED:S2"; cou[2].startDate = "03/01"; cou[2].endDate = "27/05";
  cou[3].courseCode = "MTH252"; cou[3].courseName = "Calculus II"; cou[3].lecturer = "Nguyen Thi Thu Van"; cou[3].numberOfCredits = 4; cou[3].maxNumberOfStudents = 60; cou[3].schedule = "FRI:S3/FRI:S4"; cou[3].startDate = "03/01"; cou[3].endDate = "27/05";
  cou[4].courseCode = "PH212"; cou[4].courseName = "General Physics II"; cou[4].lecturer = "Nguyen Huu Nha"; cou[4].numberOfCredits = 4; cou[4].maxNumberOfStudents = 60; cou[4].schedule = "WED:S4/THU:S4"; cou[4].startDate = "03/01"; cou[4].endDate = "27/05";
  for (int i = 0; i < 5; ++i) Global::allCourses.push_back(cou[i]);

    
}

void App::saveData() {
}

void App::main() {
  Console::clear();
  User::login();
  if (Global::currentUser.userType == UserType::ACADEMIC_STAFF) {
    Menu::staffMenu();
    return;
  }
  if (Global::currentUser.userType == UserType::STUDENT) {
    Menu::studentMenu();
    return;
  }
}

void App::run() {
  Console::setup();
  loadData();
  App::main();
}
