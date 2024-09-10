#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <cstddef>  // for size_t
#include <initializer_list>
#include <stdexcept>
#include <utility>  // for std::move

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  // Member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // Member functions
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();

  array &operator=(const array &a);
  array &operator=(array &&a) noexcept;

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type data_[N];
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_ARRAY_H
