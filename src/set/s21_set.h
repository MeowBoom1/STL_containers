#ifndef S21_SET_H
#define S21_SET_H

#include "../s21_containers.h"

namespace s21 {
template <typename Key>
class set : public set_container<Key> {
 public:
  using key_type = Key;
  using value_type = Key;

  set() : set_container<Key>(){};
  set(std::initializer_list<value_type> const &items)
      : set_container<Key>(items){};
  set(const set &s) : set_container<Key>(s){};
  set(set &&s) : set_container<Key>(s){};
  ~set() = default;

  set &operator=(set &&other);
  set &operator=(const set &other);
};

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(other);
  }
  return *this;
}
}  // namespace s21

#endif