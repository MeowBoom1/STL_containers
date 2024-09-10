#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

#include "../s21_containers.h"

namespace s21 {
template <typename K, typename T>
class associative_container : public Binary_tree<K, T> {
 public:
  class AssIterator;
  class ConstAssIterator;

  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = AssIterator;
  using const_iterator = ConstAssIterator;
  using size_type = size_t;

  associative_container() : Binary_tree<K, T>(){};
  associative_container(std::initializer_list<value_type> const &items);
  associative_container(const associative_container &other)
      : Binary_tree<K, T>(other){};
  associative_container(associative_container &&other) noexcept
      : Binary_tree<K, T>(std::move(other)){};
  associative_container &operator=(associative_container &&other) noexcept;
  associative_container &operator=(const associative_container &other);
  ~associative_container() = default;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  void merge(associative_container &other);

  class AssIterator : public Binary_tree<K, T>::Iterator {
   public:
    friend class associative_container;
    AssIterator() : Binary_tree<K, T>::Iterator(){};
    AssIterator(typename Binary_tree<K, T>::Node *node,
                typename Binary_tree<K, T>::Node *past_node = nullptr)
        : Binary_tree<K, T>::Iterator(node, past_node = nullptr){};
    value_type &operator*();

   protected:
    T &return_value();
  };

  class ConstAssIterator : public AssIterator {
   public:
    friend class associative_container;
    ConstAssIterator() : AssIterator(){};
    ConstAssIterator(typename Binary_tree<K, T>::Node *node,
                     typename Binary_tree<K, T>::Node *past_node = nullptr)
        : AssIterator(node, past_node = nullptr){};
    const_reference operator*() const { return AssIterator::operator*(); };
  };

  T &at(const value_type &key);
  T &operator[](const K &key);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert_or_assign(const value_type &value);
  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  iterator find(const value_type &key);
  iterator find(const K &key);
};

}  // namespace s21

#include "associative_container.tpp"

#endif