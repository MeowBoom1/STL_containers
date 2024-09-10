#ifndef QUEUE_TPP
#define QUEUE_TPP

namespace s21 {

template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0) {}

template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (const auto &item : items) {
    push(item);
  }
}

template <typename T>
queue<T>::queue(const queue &q) : front_(nullptr), back_(nullptr), size_(0) {
  Node *current = q.front_;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

template <typename T>
queue<T>::queue(queue &&q) : front_(q.front_), back_(q.back_), size_(q.size_) {
  q.front_ = nullptr;
  q.back_ = nullptr;
  q.size_ = 0;
}

template <typename T>
queue<T>::~queue() {
  while (!empty()) pop();
}

template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  while (!empty()) pop();

  front_ = q.front_;
  back_ = q.back_;
  size_ = q.size_;

  q.front_ = nullptr;
  q.back_ = nullptr;
  q.size_ = 0;

  return *this;
}

// element access

template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return front_->data;
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return back_->data;
}

// capacity

template <typename T>
bool queue<T>::empty() {
  return (front_ == nullptr && back_ == nullptr && size_ == 0);
}

template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return size_;
}

// modifiers

template <typename T>
void queue<T>::push(const_reference value) {
  Node *newNode = new Node(value);
  if (empty()) {
    front_ = newNode;
  } else {
    back_->next = newNode;
  }
  back_ = newNode;
  ++size_;
}

template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  Node *temp = front_;
  front_ = front_->next;
  delete temp;
  --size_;
  if (front_ == nullptr) {
    back_ = nullptr;
  }
}

template <typename T>
void queue<T>::swap(queue &other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

// insert_many

template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif
