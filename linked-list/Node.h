#pragma once

template <class T>
class Node {
 public:
  T value;
  Node<T> *next;
  Node() : value{0}, next{nullptr} {}
  Node(const T &x) : value{x}, next{nullptr} {}
  Node(const T &x, Node<T> *next) : value{x}, next{next} {}
  Node(const Node<T> &node) : value{node.value}, next{node.next} {}
};