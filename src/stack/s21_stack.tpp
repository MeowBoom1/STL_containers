#ifndef STACK_TPP
#define STACK_TPP

namespace s21 {
template <typename T>
stack<T>::stack() : bot_(nullptr), size_(0) {}

template <typename T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : bot_(nullptr), size_(0) {
  for (const auto &item : items) {
    push(item);
  }
}

template <typename T>
stack<T>::stack(const stack &s) : bot_(nullptr), size_(0) {
  Node *current = s.bot_;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

template <typename T>
stack<T>::stack(stack &&s) : bot_(s.bot_), size_(s.size_) {
  s.bot_ = nullptr;
  s.size_ = 0;
}

template <typename T>
stack<T>::~stack() {
  while (!empty()) pop();
}

template <typename T>
stack<T> stack<T>::operator=(stack &&s) {
  while (!empty()) pop();
  bot_ = s.bot_;
  size_ = s.size_;
  s.bot_ = nullptr;
  s.size_ = 0;
  return *this;
}

template <typename T>
typename stack<T>::const_reference stack<T>::top() {
  if (empty()) throw std::out_of_range("stack is empty");

  return top_->data;
}

template <typename T>
bool stack<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename stack<T>::size_type stack<T>::size() {
  return size_;
}

template <typename T>
void stack<T>::push(const_reference value) {
  if (bot_ == nullptr) {
    bot_ = new Node(value);
  } else {
    Node *i = bot_;
    while (i->next != nullptr) i = i->next;
    i->next = new Node(value);
    top_ = i->next;
  }
  ++size_;
}

template <typename T>
void stack<T>::pop() {
  if (empty()) throw std::out_of_range("stack is empty");
  if (bot_->next == nullptr) {
    delete bot_;
  } else {
    Node *last = bot_;
    Node *prev = bot_;
    while (last->next != nullptr) {
      prev = last;
      last = last->next;
    }
    prev->next = nullptr;
    delete last;
    top_ = prev;
  }
  --size_;
}

template <typename T>
void stack<T>::swap(stack &other) {
  std::swap(bot_, other.bot_);
  std::swap(size_, other.size_);
}

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif