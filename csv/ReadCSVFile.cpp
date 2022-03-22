#include"Header.h"

using namespace std;

int countStu() {
    ifstream fin;
    fin.open("Student.csv");
    if (!fin.is_open()) return 0;
    int count = 0;
    string line;
    getline(fin, line);
    while (fin) {
        getline(fin, line);
        ++count;
    }
    fin.close();
    return count;
}

int countTea() {
    ifstream fin;
    fin.open("Teacher.csv");
    if (!fin.is_open()) return 0;
    int count = 0;
    string line;
    getline(fin, line);
    while (fin) {
        getline(fin, line);
        ++count;
    }
    fin.close();
    return count;
}

int countCou() {
    ifstream fin;
    fin.open("Course.csv");
    if (!fin.is_open()) return 0;
    int count = 0;
    string line;
    getline(fin, line);
    while (fin) {
        getline(fin, line);
        ++count;
    }
    fin.close();
    return count;
}

int convertStringToNum(string s) {
    int n = s.length();
    int re = 0;
    for (int i = 0; i < n; i++) {
        switch (s[n - 1 - i]) {
        case '0': re += 0 * pow(10, i); break;
        case '1': re += 1 * pow(10, i); break;
        case '2': re += 2 * pow(10, i); break;
        case '3': re += 3 * pow(10, i); break;
        case '4': re += 4 * pow(10, i); break;
        case '5': re += 5 * pow(10, i); break;
        case '6': re += 6 * pow(10, i); break;
        case '7': re += 7 * pow(10, i); break;
        case '8': re += 8 * pow(10, i); break;
        case '9': re += 9 * pow(10, i); break;
        }
    }
    return re;
}

void loadStudentFromFile(vector <Student> S, int& n) {
    n = countStu();
    S.resize(n);

    ifstream fin;
    fin.open("Student.csv");
    if (!fin.is_open()) {
        cout << "Cannot open file." << endl;
        return;
    }

    string Line;
    string No;
    string StuID;
    string Day;
    string Month;
    string Year;
    string SocID;
    string Pass;

    int i = 0;
    getline(fin, Line);
    while (fin) {
        getline(fin, No, ',');
        getline(fin, StuID, ',');
        getline(fin, S[i].Fname, ',');
        getline(fin, S[i].Lname, ',');
        getline(fin, Day, '/');
        getline(fin, Month, '/');
        getline(fin, Year, '/');
        getline(fin, SocID, ',');
        getline(fin, S[i].Class, ',');
        getline(fin, Pass);

        S[i].No = convertStringToNum(No);
        S[i].StuID = convertStringToNum(StuID);
        S[i].SocID = convertStringToNum(SocID);
        S[i].Day = convertStringToNum(Day);
        S[i].Month = convertStringToNum(Month);
        S[i].Year = convertStringToNum(Year);
        S[i].Pass = convertStringToNum(Pass);

        ++i;
    }

    fin.close();
}

void loadTeacherFromFile(vector <Teacher>& T, int& n) {
    n = countTea();
    T.resize(n);

    ifstream fin;
    fin.open("Teacher.csv");
    if (!fin.is_open()) {
        cout << "Cannot open file." << endl;
        return;
    }

    string Line;
    string No;
    string TeaID;
    string SocID;
    string Pass;

    int i = 0;
    getline(fin, Line);
    while (fin) {
        getline(fin, No, ',');
        getline(fin, TeaID, ',');
        getline(fin, T[i].Fname, ',');
        getline(fin, T[i].Lname, ',');
        getline(fin, T[i].Gen, ',');
        getline(fin, SocID, ',');
        getline(fin, T[i].Faculty, ',');
        getline(fin, Pass);

        T[i].No = convertStringToNum(No);
        T[i].TeaID = convertStringToNum(TeaID);
        T[i].SocID = convertStringToNum(SocID);
        T[i].Pass = convertStringToNum(Pass);

        ++i;
    }

    fin.close();
}

void loadCourseFromFile(vector <Course>& C, int& n) {
    n = countTea();
    C.resize(n);

    ifstream fin;
    fin.open("Course.csv");
    if (!fin.is_open()) {
        cout << "Cannot open file." << endl;
        return;
    }

    string Line;
    string NumCre;
    string MaxMem;
    string DayStart;
    string MonthStart;
    string DayEnd;
    string MonthEnd;

    int i = 0;
    getline(fin, Line);
    while (fin) {
        getline(fin, C[i].ID, ',');
        getline(fin, C[i].CName, ',');
        getline(fin, C[i].TName, ',');
        getline(fin, NumCre, ',');
        getline(fin, MaxMem, ',');
        getline(fin, C[i].Day1, ',');
        getline(fin, C[i].Session1, ',');
        getline(fin, C[i].Day2, ',');
        getline(fin, C[i].Session2, ',');
        getline(fin, DayStart, '/');
        getline(fin, MonthStart, ',');
        getline(fin, DayEnd, '/');
        getline(fin, MonthEnd);

        C[i].NumCre = convertStringToNum(NumCre);
        C[i].MaxMem = convertStringToNum(MaxMem);
        C[i].DayStart = convertStringToNum(DayStart);
        C[i].MonthStart = convertStringToNum(MonthStart);
        C[i].DayEnd = convertStringToNum(DayEnd);
        C[i].MonthEnd = convertStringToNum(MonthEnd);

        ++i;
    }

    fin.close();
}