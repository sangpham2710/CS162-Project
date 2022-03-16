#pragma once

template <class T>
class Node {
 public:
  T value;
  Node<T>*prev, *next;

  Node() : value{T()}, prev{nullptr}, next{nullptr} {}
  Node(const T& x) : value{x}, prev{nullptr}, next{nullptr} {}
  Node(const T& x, Node<T>* const& prev, Node<T>* const& next)
      : value{x}, prev{prev}, next{next} {}
  Node(const Node<T>& node)
      : value{node.value}, prev{node.prev}, next{node.next} {}
};
