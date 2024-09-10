#ifndef QUEUE_H
#define QUEUE_H

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q);
  ~queue();
  queue &operator=(queue &&q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  struct Node {
    value_type data;
    Node *next;
    Node(const_reference value) : data(value), next(nullptr) {}
  };

  Node *front_;
  Node *back_;
  size_type size_;
};
};  // namespace s21

#include "s21_queue.tpp"

#endif
