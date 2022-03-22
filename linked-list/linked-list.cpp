
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "DoublyLinkedList.h"

struct Student {
  string name;
  int age;
  List<string> courses;
  Student() : name(""), age(0) {}
  Student(string name, int age, List<string> courses)
      : name(name), age(age), courses(courses) {}
};

int main(int argc, const char* argv[]) {
  List<Student> a;
  Student stu1("sang", 10, {"cs162", "ph212"});
  Student stu2("nhut", 10, {"cs162", "mth252"});
  a.push_back(stu1);
  a.push_back(stu2);
  a.for_each([](const Student& stu) { cout << "Name: " << stu.name << '\n';
    cout << "Age: " << stu.age << '\n';
    cout << "Course: ";
    for (const auto& course : stu.courses) {
      cout << course << ", ";
    }
    cout << '\n';
    cout << "-----------------\n";
  });
  return 0;
}
