#ifndef S21_LIST_H
#define S21_LIST_H

#include <algorithm>  // for std::move
#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <typename T>
class list {
 private:
  struct Node {
    T data;
    Node* prev;
    Node* next;
    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
  };

 public:
  // Member types
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class ListIterator {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    ListIterator(Node* node = nullptr) : node_(node) {}

    reference operator*() const { return node_->data; }
    pointer operator->() const { return &node_->data; }

    ListIterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator temp = *this;
      node_ = node_->next;
      return temp;
    }

    bool operator==(const ListIterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const ListIterator& other) const {
      return node_ != other.node_;
    }

    Node* getNode() const { return node_; }

   private:
    Node* node_;
  };

  class ListConstIterator {
   public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;

    ListConstIterator(Node* node = nullptr) : node_(node) {}
    ListConstIterator(const ListIterator& it) : node_(it.getNode()) {}

    reference operator*() const { return node_->data; }
    pointer operator->() const { return &node_->data; }

    ListConstIterator& operator++() {
      node_ = node_->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator temp = *this;
      node_ = node_->next;
      return temp;
    }

    bool operator==(const ListConstIterator& other) const {
      return node_ == other.node_;
    }
    bool operator!=(const ListConstIterator& other) const {
      return node_ != other.node_;
    }

    Node* getNode()
        const {  // Add this method to allow access to the node pointer
      return node_;
    }

   private:
    Node* node_;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Constructors and Destructor
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l) noexcept;
  ~list();

  // Assignment operators
  list& operator=(const list& l);
  list& operator=(list&& l) noexcept;

  // Element Access
  const_reference front() const;
  const_reference back() const;

  // Iterators
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique();
  void sort();

 private:
  Node* head_;
  Node* tail_;
  size_type size_;

  void init_empty();
  void link_nodes(Node* first, Node* second);
  void move_nodes(list& other);
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H
