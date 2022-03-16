
#include <iostream>
#include <string>

#include "DoublyLinkedList.h"

void output(const List<int>& list) {
  std::cout << "<< OUTPUT <<\n";
  std::cout << "size: " << list.size() << '\n';
  std::cout << "Is list empty: " << list.empty() << '\n';
  std::cout << "front: " << list.front() << '\n';
  std::cout << "back: " << list.back() << '\n';
  for (int i = 0; i < list.size(); i++) std::cout << list[i] << ' ';
  std::cout << '\n';
  for (auto it = list.begin(); it != list.end(); ++it)
    std::cout << (*it) << ' ';

  // copy constructor
  std::cout << "\n\n";

  // CRASH since list.begin() returns a const_iterator
  // (*list.begin()) = 100;
  // std::cout << (*list.begin()) << '\n';
}

struct coord {
  int x, y;
};

int main(int argc, const char* argv[]) {
  List<int> list{1, 2, 3};
  List<int> list2;
  list2 = list;
  output(list2);
  list2.push_back(3);
  output(list);
  output(list2);
  //
  //  // std::cout << it->next << '\n';
  //  // it->next = nullptr;
  //  List<coord> ll{{1, 2}, {100, 200}};
  //  List<coord>::iterator it = ll.begin();
  //  (*it).x = 10;
  //  std::cout << ll.size() << ' ' << (*it).x << '\n';
  //  (++it)->y = 81273;
  //  std::cout << it->y << '\n';
  //  std::cout << ll[1].y << '\n';
  //  std::cout << ll[0].x << '\n';
  // output(list2);
  // 3 3
  std::cout << list.size() << ' ' << std::distance(list.begin(), list.end())
            << '\n';
  // 1 2 3
  output(list);

  list.push_front(0).push_back(5);
  // 0 1 2 3 5
  output(list);

  list.insert_at(4, 4).insert_at(list.size(), 6).insert_at(0, -1);
  // -1 0 1 2 3 4 5 6
  output(list);
  int tmp = list.size() - 1 - 1;
  (list.remove_at(0)).remove_at(list.size() - 1);
  // 0 1 2 3 4 5
  output(list);

  list.remove_at(1).push_back(4);
  std::cout << "----------------------";
  // 0 2 3 4 5 4
  output(list);
  // true true
  std::cout << "Is 5 an element: " << (list.find(5) != list.end())
            << (list.find_last(5) != list.end()) << "\n\n";
  // false true
  std::cout << "Is 5 an element: "
            << (list.find(5, list.begin(), list.find(4)) != list.end())
            << (list.find_last(5, list.begin(), list.find_last(4)) != nullptr)
            << "\n\n";

  list.reverse().at(0) = 100;
  // 100 5 4 3 2 0
  output(list);

  // true true
  std::cout << "Is 5 an element: " << (list.find(5) != list.end())
            << (list.find_last(5) != list.end()) << "\n\n";

  list.clear().push_back(1);
  // 1
  output(list);

  list.remove_at(0);
  // empty
  // CRASH at list.front()
  // output(list);

  List<std::string> ll{"acd", "cde", "acc"};
  // false
  std::cout << (ll.find_if([](const std::string& s) -> bool {
    return s[0] == 'b';
  }) != ll.end())
            << '\n';
  // 2
  std::cout << (ll.count_if([](const std::string& s) -> bool {
    return s[0] == 'a';
  })) << '\n';

  List<int> ll2{2, 4, 6, 8, 10};
  // true
  std::cout << ll2.all_of([](const int& value) { return value % 2 == 0; })
            << '\n';
  // false
  std::cout << ll2.any_of([](const int& value) { return value % 2 != 0; })
            << '\n';
  // true
  std::cout << ll2.none_of([](const int& value) { return value % 2 != 0; })
            << '\n';
}
