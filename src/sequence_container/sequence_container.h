#ifndef SEQUENCE_CONTAINER_H
#define SEQUENCE_CONTAINER_H

#include "../container/container.h"
namespace s21 {
template <typename T>
class sequence_container : public s21::container {
 public:
  class iterator {
   public:
    iterator(T *ptr) : ptr_(ptr) {}
    iterator &operator++() {
      ++ptr_;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++ptr_;
      return tmp;
    }
    iterator &operator--() {
      --ptr_;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --ptr_;
      return tmp;
    }
    T &operator*() { return *ptr_; }
    T *operator->() { return ptr_; }
    bool operator==(const iterator &other) const { return ptr_ == other.ptr_; }
    bool operator!=(const iterator &other) const { return ptr_ != other.ptr_; }
    T *get_ptr() const { return ptr_; }

   private:
    T *ptr_;
  };
  class reverse_iterator {
   public:
    reverse_iterator(T *ptr) : ptr_(ptr) {}
    reverse_iterator &operator++() {
      --ptr_;
      return *this;
    }
    reverse_iterator operator++(int) {
      reverse_iterator tmp = *this;
      --ptr_;
      return tmp;
    }
    reverse_iterator &operator--() {
      ++ptr_;
      return *this;
    }
    reverse_iterator operator--(int) {
      reverse_iterator tmp = *this;
      ++ptr_;
      return tmp;
    }
    T &operator*() { return *ptr_; }
    T *operator->() { return ptr_; }
    bool operator==(const reverse_iterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const reverse_iterator &other) const {
      return ptr_ != other.ptr_;
    }

   private:
    T *ptr_;
  };

  class const_iterator {
   public:
    // using iterator_category = std::random_access_iterator_tag;
    // using value_type = T;
    // using difference_type = std::ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    // Constructors
    const_iterator() : ptr_(nullptr) {}
    const_iterator(const pointer ptr) : ptr_(ptr) {}

    // Dereference operator
    reference operator*() const { return *ptr_; }
    pointer operator->() const { return ptr_; }

    // Increment and decrement operators
    const_iterator &operator++() {
      ++ptr_;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++ptr_;
      return temp;
    }

    const_iterator &operator--() {
      --ptr_;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp = *this;
      --ptr_;
      return temp;
    }

    // Arithmetic operators
    const_iterator operator+(difference_type n) const {
      return const_iterator(ptr_ + n);
    }

    const_iterator operator-(difference_type n) const {
      return const_iterator(ptr_ - n);
    }

    difference_type operator-(const const_iterator &other) const {
      return ptr_ - other.ptr_;
    }

    const_iterator &operator+=(difference_type n) {
      ptr_ += n;
      return *this;
    }

    const_iterator &operator-=(difference_type n) {
      ptr_ -= n;
      return *this;
    }

    // Comparison operators
    bool operator==(const const_iterator &other) const {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const const_iterator &other) const {
      return ptr_ != other.ptr_;
    }
    bool operator<(const const_iterator &other) const {
      return ptr_ < other.ptr_;
    }
    bool operator>(const const_iterator &other) const {
      return ptr_ > other.ptr_;
    }
    bool operator<=(const const_iterator &other) const {
      return ptr_ <= other.ptr_;
    }
    bool operator>=(const const_iterator &other) const {
      return ptr_ >= other.ptr_;
    }

   private:
    pointer ptr_;
  };

  typedef unsigned int size_type;

  sequence_container();
  sequence_container(const sequence_container<T> &x);
  ~sequence_container();

  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend();

  sequence_container<T> &operator=(const sequence_container<T> &x);

  size_type size();
  void resize(size_type new_size, T x);
  bool empty();

  void insert(iterator position, const T &value);
  void insert(iterator position, size_type count, T &value);
  template <typename InputIt>
  void insert(iterator position, InputIt first, InputIt last);

  void erase(iterator position);
  void erase(iterator first, iterator last);

  void push_back(const T &element);
  void pop_back();

  T &front();
  T &back();

 protected:
  T *data;
  size_type size_;
};
}  // namespace s21

#include "sequence_container.tpp"

#endif