#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <algorithm>  // for std::move, std::move_backward, etc.
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = T*;
  using const_iterator = const T*;

  // Constructors and Destructor
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector();

  // Assignment operators
  vector& operator=(const vector& v);
  vector& operator=(vector&& v) noexcept;

  // Element Access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T* data() noexcept;

  // Iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  // size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  // Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other) noexcept;

 private:
  T* data_;             // Pointer to the underlying array
  size_type size_;      // Number of elements in the vector
  size_type capacity_;  // Capacity of the vector

  void reallocate(size_type new_capacity);
  void check_bounds(size_type pos) const;
};

}  // namespace s21

#include "s21_vector.tpp"  // Include the implementation

#endif
