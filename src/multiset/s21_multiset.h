#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../s21_containers.h"

namespace s21 {
template <typename Key>
class multiset : public set_container<Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  multiset() : set_container<Key>(){};
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &s) : set_container<Key>(s){};
  multiset(multiset &&s) : set_container<Key>(s){};
  ~multiset() = default;

  multiset &operator=(multiset &&other);
  multiset &operator=(const multiset &other);

  std::pair<typename Binary_tree<Key, Key>::Iterator, bool> insert(
      const value_type &value);
  template <class... Args>
  vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>> insert_many(
      Args &&...args);

 protected:
  bool RecursiveInsert(typename Binary_tree<Key, Key>::Node *node,
                       const typename Binary_tree<Key, Key>::value_type &key);
};

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key>
std::pair<typename Binary_tree<Key, Key>::Iterator, bool> multiset<Key>::insert(
    const value_type &key) {
  typename Binary_tree<Key, Key>::value_type bin_v = {key, key};
  std::pair<typename Binary_tree<Key, Key>::Iterator, bool> value;
  if (Binary_tree<Key, Key>::root_ == nullptr) {
    typename Binary_tree<Key, Key>::value_type sec_key = bin_v;
    Binary_tree<Key, Key>::root_ = new
        typename Binary_tree<Key, Key>::Node({sec_key.first, sec_key.second});
    value.first =
        typename Binary_tree<Key, Key>::Iterator(Binary_tree<Key, Key>::root_);
    value.second = true;
  } else {
    typename Binary_tree<Key, Key>::value_type sec_key = bin_v;
    bool check_insert = RecursiveInsert(Binary_tree<Key, Key>::root_, sec_key);
    value.first = Binary_tree<Key, Key>::Find(key);
    value.second = check_insert;
  }
  return value;
}

template <typename Key>
bool multiset<Key>::RecursiveInsert(
    typename Binary_tree<Key, Key>::Node *node,
    const typename Binary_tree<Key, Key>::value_type &key) {
  bool check_insert = false;
  if (key.first <= node->value_.first) {
    if (node->left_ == nullptr) {
      node->left_ = new typename Binary_tree<Key, Key>::Node(key, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->left_, key);
    }
  } else if (key.first > node->value_.first) {
    if (node->right_ == nullptr) {
      node->right_ = new typename Binary_tree<Key, Key>::Node(key, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->right_, key);
    }
  }
  Binary_tree<Key, Key>::SetHeight(node);
  Binary_tree<Key, Key>::Balance(node);
  return check_insert;
}

template <typename Key>
template <class... Args>
vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(multiset &&other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(const multiset &other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(other);
  }
  return *this;
}
}  // namespace s21

#endif