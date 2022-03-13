#pragma once

#include <initializer_list>

#include "Node.h"

template <class T>
class SinglyLinkedList {
 private:
  Node<T>* head;
  Node<T>* tail;
  int len;
  class Iterator;

 public:
  SinglyLinkedList() : head{nullptr}, tail{nullptr}, len{0} {}
  SinglyLinkedList(const std::initializer_list<T>& source)
      : head{nullptr}, tail{nullptr}, len{0} {
    for (auto it = source.begin(); it != source.end(); ++it)
      this->pushBack(*it);
  }
  SinglyLinkedList(const SinglyLinkedList<T>& source)
      : head{nullptr}, tail{nullptr}, len{0} {
    for (auto it = source.begin(); it; it = it->next) this->pushBack(it->value);
  }

  SinglyLinkedList& operator=(const SinglyLinkedList& rhs) {
    if (this == &rhs) return *this;
    this->clear();
    for (auto it = rhs.begin(); it; it = it->next) this->pushBack(it->value);
    return *this;
  }
  ~SinglyLinkedList() { this->clear(); }

  int length() const { return this->len; }
  int size() const { return this->len; }
  Node<T>* begin() const { return this->head; }
  Node<T>* end() const { return this->tail; }
  T front() const { return this->head->value; }
  T back() const { return this->tail->value; }
  Node<T>* at(const int& pos) const {
    if (pos < 0 || pos >= this->len) return nullptr;
    Node<T>* ptr = this->head;
    for (int i = 0; i < pos; ++i) ptr = ptr->next;
    return ptr;
  }

  bool insertAt(const int& pos, const T& value) {
    if (pos < 0 || pos > this->len) return false;
    if (pos == 0) {
      Node<T>* node = new Node<T>(value, this->head);
      this->head = node;
      if (this->len == 0) this->tail = node;
    } else if (pos == this->len) {
      Node<T>* node = new Node<T>(value, nullptr);
      this->tail->next = node;
      this->tail = node;
    } else {
      Node<T>* ptr = this->head;
      for (int i = 0; i < pos - 1; ++i) ptr = ptr->next;
      Node<T>* node = new Node<T>(value, ptr->next);
      ptr->next = node;
    }
    ++this->len;
    return true;
  }
  void pushFront(const T& value) { this->insertAt(0, value); }
  void pushBack(const T& value) { this->insertAt(this->len, value); }
  bool removeAt(const int& pos) {
    if (pos < 0 || pos >= this->len) return false;
    if (pos == 0) {
      Node<T>* tmp = this->head;
      this->head = this->head->next;
      delete tmp;
    } else {
      Node<T>* ptr = this->head;
      for (int i = 0; i < pos - 1; ++i) ptr = ptr->next;
      Node<T>* tmp = ptr->next;
      ptr->next = ptr->next->next;
      delete tmp;
      if (pos == this->len - 1) this->tail = ptr;
    }
    --this->len;
    return true;
  }
  Node<T>* findFirst(const int& value) const {
    Node<T>* ptr = this->head;
    while (ptr != nullptr) {
      if (ptr->value == value) return ptr;
      ptr = ptr->next;
    }
    return nullptr;
  }
  int countAll(const int& value) const {
    Node<T>* ptr = this->head;
    int cnt = 0;
    while (ptr != nullptr) {
      if (ptr->value == value) ++cnt;
      ptr = ptr->next;
    }
    return cnt;
  }
  void reverseAll() {
    Node<T>* prev = nullptr;
    Node<T>* cur = head;
    Node<T>* next = nullptr;
    while (cur != nullptr) {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
    this->head = prev;
  }
  friend std::ostream& operator<<(std::ostream& os,
                                  const SinglyLinkedList<T>& rhs) {
    for (auto ptr = rhs.head; ptr; ptr = ptr->next) os << ptr->value << "->";
    os << "NULL";
    return os;
  }
  void clear() {
    while (this->head != nullptr) {
      Node<T>* tmp = this->head;
      this->head = this->head->next;
      delete tmp;
    }
    this->head = this->tail = nullptr;
    this->len = 0;
  }
};