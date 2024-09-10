#include "sequence_container.h"

namespace s21 {

template <typename T>
sequence_container<T>::sequence_container() : data(nullptr), size_(0) {}

template <typename T>
sequence_container<T>::sequence_container(const sequence_container<T> &x)
    : data(nullptr), size_(0) {
  *this = x;
}

template <typename T>
sequence_container<T>::~sequence_container() {
  delete[] data;
}

template <typename T>
typename sequence_container<T>::iterator sequence_container<T>::begin() {
  return iterator(data);
}

template <typename T>
typename sequence_container<T>::iterator sequence_container<T>::end() {
  return iterator(data + size_);
}

template <typename T>
typename sequence_container<T>::reverse_iterator
sequence_container<T>::rbegin() {
  return reverse_iterator(data + size_ - 1);
}

template <typename T>
typename sequence_container<T>::reverse_iterator sequence_container<T>::rend() {
  return reverse_iterator(data - 1);
}

template <typename T>
sequence_container<T> &sequence_container<T>::operator=(
    const sequence_container<T> &x) {
  if (this != &x) {
    delete[] data;
    size_ = x.size_;
    data = new T[size_];
    for (size_type i = 0; i < size_; ++i) {
      data[i] = x.data[i];
    }
  }
  return *this;
}

template <typename T>
typename sequence_container<T>::size_type sequence_container<T>::size() {
  return size_;
}

template <typename T>
void sequence_container<T>::resize(size_type new_size, T x) {
  T *new_data = new T[new_size];
  for (size_type i = 0; i < new_size && i < size_; ++i) {
    new_data[i] = data[i];
  }
  for (size_type i = size_; i < new_size; ++i) {
    new_data[i] = x;
  }
  delete[] data;
  data = new_data;
  size_ = new_size;
}

template <typename T>
bool sequence_container<T>::empty() {
  return size_ == 0;
}

template <typename T>
void sequence_container<T>::insert(iterator position, const T &value) {
  size_type pos = position.get_ptr() - data;
  resize(size_ + 1, T());
  for (size_type i = size_ - 1; i > pos; --i) {
    data[i] = data[i - 1];
  }
  data[pos] = value;
}

template <typename T>
void sequence_container<T>::insert(iterator position, size_type count,
                                   T &value) {
  size_type pos = position.ptr_ - data;
  resize(size_ + count, T());
  for (size_type i = size_ - 1; i >= pos + count; --i) {
    data[i] = data[i - count];
  }
  for (size_type i = 0; i < count; ++i) {
    data[pos + i] = value;
  }
}

template <typename T>
template <typename InputIt>
void sequence_container<T>::insert(iterator position, InputIt first,
                                   InputIt last) {
  size_type pos = position.ptr_ - data;
  size_type count = std::distance(first, last);
  resize(size_ + count, T());
  for (size_type i = size_ - 1; i >= pos + count; --i) {
    data[i] = data[i - count];
  }
  for (size_type i = 0; i < count; ++i) {
    data[pos + i] = *first++;
  }
}

template <typename T>
void sequence_container<T>::erase(iterator position) {
  size_type pos = position.get_ptr() - data;
  for (size_type i = pos; i < size_ - 1; ++i) {
    data[i] = data[i + 1];
  }
  resize(size_ - 1, T());
}

template <typename T>
void sequence_container<T>::erase(iterator first, iterator last) {
  size_type start_pos = first.ptr_ - data;
  size_type end_pos = last.ptr_ - data;
  size_type count = end_pos - start_pos;
  for (size_type i = start_pos; i < size_ - count; ++i) {
    data[i] = data[i + count];
  }
  resize(size_ - count, T());
}

template <typename T>
void sequence_container<T>::push_back(const T &element) {
  resize(size_ + 1, element);
}

template <typename T>
void sequence_container<T>::pop_back() {
  if (size_ > 0) {
    resize(size_ - 1, T());
  }
}

template <typename T>
T &sequence_container<T>::front() {
  return data[0];
}

template <typename T>
T &sequence_container<T>::back() {
  return data[size_ - 1];
}
}  // namespace s21