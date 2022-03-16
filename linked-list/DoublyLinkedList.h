#pragma once

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>

#include "Node.h"


template <class T>
class List<T>::iterator
    : public std::iterator<std::bidirectional_iterator_tag, T, T, T*, T&> {
  friend class List;

 private:
  Node<T>* ptr;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = T;
  using value_type = T;
  using pointer = T*;
  using reference = T&;

  iterator() : ptr{nullptr} {}
  iterator(Node<value_type>* const& p) : ptr(p) {}
  reference operator*() const {
    reference value = ptr->value;
    return value;
  }
  pointer operator->() const { return &*(*this); }
  iterator& operator++() {
    ptr = ptr->next;
    return *this;
  }
  iterator operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  }
  iterator& operator--() {
    ptr = ptr->prev;
    return *this;
  }
  iterator operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
  }
  iterator& operator=(Node<value_type>* const& p) {
    ptr = p;
    return *this;
  }
  bool operator==(const iterator& it) const { return it.ptr == ptr; }
  bool operator!=(const iterator& it) const { return it.ptr != ptr; }
};
