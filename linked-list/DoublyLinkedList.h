#pragma once

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <string>

#include "Node.h"
template <class T>
class List {
 public:
  class iterator;
  class const_iterator;

 private:
  iterator list_begin, list_end;
  int list_size;
  bool insert_next(iterator& it, iterator& it_next) {
    if (it == this->end() || it == nullptr || it_next == this->end() ||
        it_next == nullptr)
      return false;

    Node<T>*& node = it.ptr;
    Node<T>*& p_next = it_next.ptr;

    p_next->next = node->next;
    p_next->prev = node;
    p_next->prev->next = p_next;
    p_next->next->prev = p_next;

    ++this->list_size;

    return true;
  }
  bool insert_previous(const iterator& it, const iterator& it_prev) {
    if (it.ptr == nullptr || it_prev == this->end() || it_prev.ptr == nullptr)
      return false;

    Node<T>* node = it.ptr;
    Node<T>* p_prev = it_prev.ptr;

    p_prev->next = node;
    p_prev->prev = node->prev;
    p_prev->next->prev = p_prev;
    if (p_prev->prev) p_prev->prev->next = p_prev;

    if (it == this->begin()) list_begin = p_prev;

    ++this->list_size;

    return true;
  }
  bool remove(iterator& it) {
    if (it == this->end() || it.ptr == nullptr) return false;

    Node<T>* node = it.ptr;

    if (node->next) {
      node->next->prev = node->prev;
    }
    if (node->prev) {
      node->prev->next = node->next;
    }

    if (this->begin() == it) {
      ++list_begin;
    }

    --this->list_size;

    delete node;
    it.ptr = nullptr;

    return true;
  }
  /// Exception(s): out of range
  iterator get_iterator(const int& index) {
    if (index < 0 || index >= this->size()) {
      throw std::out_of_range("List of size " + std::to_string(this->size()) +
                              " is out of range at index " +
                              std::to_string(index) + ".");
    }

    iterator it;
    if (index < this->size() / 2) {
      it = this->begin();
      for (int i = 1; i <= index; i++) ++it;
    } else {
      it = this->end();
      for (int i = this->size() - 1; i >= index; i--) --it;
    }

    return it;
  }
  const_iterator get_iterator(const int& index) const {
    if (index < 0 || index >= this->size()) {
      throw std::out_of_range("List of size " + std::to_string(this->size()) +
                              " is out of range at index " +
                              std::to_string(index) + ".");
    }

    const_iterator it;
    if (index < this->size() / 2) {
      it = this->begin();
      for (int i = 1; i <= index; i++) ++it;
    } else {
      it = this->end();
      for (int i = this->size() - 1; i >= index; i--) --it;
    }

    return it;
  }

 public:
  List() : list_size{0} {
    Node<T>* end_node = new Node<T>();
    list_begin = list_end = end_node;
  }
  List(const std::initializer_list<T>& source) : list_size{0} {
    Node<T>* end_node = new Node<T>();
    list_begin = list_end = end_node;
    for (const auto& x : source) this->push_back(x);
  }
  List(const List<T>& source) : list_size{0} {
    Node<T>* end_node = new Node<T>();
    list_begin = list_end = end_node;

    for (const auto& x : source) this->push_back(x);
  }
  List(List<T>&& source)
      : list_begin{source.list_begin},
        list_end{source.list_end},
        list_size{source.list_size} {
    source.list_begin = nullptr;
    source.list_end = nullptr;
    source.list_size = 0;
  }
  ~List() {
    this->clear();
    delete list_end.ptr;
  }
};
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
template <class T>
class List<T>::const_iterator
    : public std::iterator<std::bidirectional_iterator_tag, T, T, T*, T&> {
  friend class List;

 private:
  const Node<T>* ptr;

 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = T;
  using value_type = T;
  using pointer = const T*;
  using reference = const T&;

  const_iterator() : ptr{nullptr} {}
  const_iterator(Node<value_type>* const& p) : ptr(p) {}
  const_iterator(const iterator& other) : ptr(other.ptr) {}
  const_iterator(const const_iterator& other) : ptr(other.ptr) {}
  reference operator*() const {
    reference value = ptr->value;
    return value;
  }
  pointer operator->() const { return &*(*this); }
  const_iterator& operator++() {
    ptr = ptr->next;
    return *this;
  }
  const_iterator operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
  }
  const_iterator& operator--() {
    ptr = ptr->prev;
    return *this;
  }
  const_iterator operator--(int) {
    const_iterator tmp = *this;
    --(*this);
    return tmp;
  }
  const_iterator& operator=(Node<value_type>* const& p) {
    ptr = p;
    return *this;
  }
  const_iterator& operator=(const iterator& other) {
    ptr = other.ptr;
    return *this;
  }
  bool operator==(const const_iterator& it) const { return it.ptr == ptr; }
  bool operator!=(const const_iterator& it) const { return it.ptr != ptr; }
};
