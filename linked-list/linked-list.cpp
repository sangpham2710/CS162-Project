#include <iostream>

#include "SinglyLinkedList.h"

using namespace std;

int main() {
  SinglyLinkedList<int> a{1, 3};
  a.insertAt(2, 2);
  cout << a.at(2)->value << '\n';
  return 0;
}