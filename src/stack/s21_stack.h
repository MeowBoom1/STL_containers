#ifndef STACK_H
#define STACK_H

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &s);
  stack(stack &&s);
  ~stack();
  stack operator=(stack &&s);

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  struct Node {
    value_type data;
    Node *next;
    Node(const_reference value) : data(value), next(nullptr) {}
  };

  Node *bot_;
  Node *top_;
  size_type size_;
};

}  // namespace s21

#include "s21_stack.tpp"

#endif