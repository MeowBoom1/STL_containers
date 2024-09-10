#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <iostream>

#include "../s21_containers.h"

template <typename K, typename T>
class Binary_tree {
 public:
  struct Node;

 public:
  class Iterator;
  class ConstIterator;
  class ReverseIterator;

  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using reverse_iterator = ReverseIterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* past_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator& it);
    friend class Binary_tree<K, T>;
    bool operator!=(const iterator& it);

    Node* iter_node_;
    Node* iter_past_node_;
    static Node* MoveForward(Node* node);
    static Node* MoveBack(Node* node);
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return iterator::operator*(); };
  };

  class ReverseIterator {
   public:
    ReverseIterator();
    ReverseIterator(Node* node, Node* past_node = nullptr);
    ReverseIterator& operator++();
    ReverseIterator& operator--();
    reference operator*();
    bool operator==(const reverse_iterator& it);
    bool operator!=(const reverse_iterator& it);

    Node* reverse_iter_node_;
    Node* reverse_iter_past_node_;
    Node* ReverseMoveForward(Node* node);
    Node* ReverseMoveBack(Node* node);
  };

  Binary_tree();
  Binary_tree(const Binary_tree& other);
  Binary_tree(Binary_tree&& other) noexcept;
  ~Binary_tree();
  Binary_tree& operator=(Binary_tree&& other) noexcept;
  Binary_tree& operator=(const Binary_tree& other);
  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& key);
  void erase(iterator pos);
  void erase(K& key);
  void swap(Binary_tree& other);
  void merge(Binary_tree& other);
  bool contains(const value_type& key);
  iterator lower_bound(K& key);
  iterator upper_bound(K& key);
  std::pair<iterator, iterator> equal_range(K& key);

 public:
  iterator Find(const value_type& key);
  iterator Find(const K& key);
  struct Node {
    Node(value_type value);
    Node(value_type value, Node* parent);
    value_type value_;
    Node* left_ = nullptr;
    Node* right_ = nullptr;
    Node* parent_ = nullptr;
    int height_ = 0;
    friend class Binary_tree<K, T>;
  };
  Node* root_;
  void FreeNode(Node* node);
  Node* CopyTree(Node* node, Node* parent);
  void SwapValue(Node* a, Node* b);
  void RightRotate(Node* node);
  void LeftRotate(Node* node);
  void Balance(Node* node);
  int GetBalance(Node* node);
  int GetHeight(Node* node);
  void SetHeight(Node* node);
  static Node* GetMin(Node* node);
  static Node* GetMax(Node* node);
  bool RecursiveInsert(Node* node, const value_type& key);
  Node* RecursiveDelete(Node* node, value_type key);
  size_t RecursiveSize(Node* node);
  Node* RecursiveFind(Node* node, const value_type& key);
};

#include "binary_tree.tpp"

#endif