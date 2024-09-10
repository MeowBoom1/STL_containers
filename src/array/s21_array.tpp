#include "s21_array.h"

namespace s21 {

// Member functions

template <typename T, std::size_t N>
array<T, N>::array() {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = T();
  }
}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items) {
  size_type i = 0;
  for (auto it = items.begin(); it != items.end() && i < N; ++it, ++i) {
    data_[i] = *it;
  }
}

template <typename T, std::size_t N>
array<T, N>::array(const array &a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = a.data_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array &&a) noexcept {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(a.data_[i]);
  }
  std::fill(std::begin(a.data_), std::end(a.data_),
            T());  // Reset the moved-from object
}

template <typename T, std::size_t N>
array<T, N>::~array() {
  // No dynamic memory to free, so nothing needed here
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(const array &a) {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <typename T, std::size_t N>
typename array<T, N>::array &array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
    std::fill(std::begin(a.data_), std::end(a.data_),
              T());  // Reset the moved-from object
  }
  return *this;
}

// Element access

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Array index out of range");
  }
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

// Iterators

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data_ + N;
}

// Capacity

template <typename T, std::size_t N>
bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

// Modifiers

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21
