#ifndef SET_CONTAINER_H
#define SET_CONTAINER_H

#include "../s21_containers.h"

namespace s21 {
template <typename Key>
class set_container : public Binary_tree<Key, Key> {
 public:
  class SetConIterator;
  class SetConReverseIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = SetConIterator;
  using reverse_iterator = SetConReverseIterator;
  using const_iterator = typename Binary_tree<Key, Key>::ConstIterator;

  set_container() : Binary_tree<Key, Key>(){};
  set_container(std::initializer_list<value_type> const &items);
  set_container(const set_container &s) : Binary_tree<Key, Key>(s){};
  set_container(set_container &&s) : Binary_tree<Key, Key>(std::move(s)){};
  ~set_container() = default;

  class SetConIterator : public Binary_tree<Key, Key>::Iterator {
   public:
    SetConIterator() : Binary_tree<Key, Key>::Iterator(){};
    SetConIterator(typename Binary_tree<Key, Key>::Node *node,
                   typename Binary_tree<Key, Key>::Node *past_node = nullptr)
        : Binary_tree<Key, Key>::Iterator(node, past_node = nullptr){};
    value_type &operator*();
  };

  class SetConReverseIterator : public Binary_tree<Key, Key>::ReverseIterator {
   public:
    SetConReverseIterator() : Binary_tree<Key, Key>::ReverseIterator(){};
    SetConReverseIterator(
        typename Binary_tree<Key, Key>::Node *node,
        typename Binary_tree<Key, Key>::Node *past_node = nullptr)
        : Binary_tree<Key, Key>::ReverseIterator(node, past_node = nullptr){};
    value_type &operator*();
  };

  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend();

  set_container &operator=(set_container &&other);
  set_container &operator=(const set_container &other);

  iterator lower_bound(Key &key);
  iterator upper_bound(Key &key);
  std::pair<iterator, iterator> equal_range(Key &key);
  std::pair<typename Binary_tree<Key, Key>::Iterator, bool> insert(
      const value_type &value);
  iterator find(const Key &key);
  template <class... Args>
  vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>> insert_many(
      Args &&...args);
};
}  // namespace s21

#include "set_container.tpp"

#endif