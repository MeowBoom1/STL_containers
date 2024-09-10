#include "s21_map.h"

namespace s21 {

template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K, typename T>
map<K, T> &map<K, T>::operator=(map &&other) {
  if (this != &other) {
    Binary_tree<K, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename K, typename T>
map<K, T> &map<K, T>::operator=(const map &other) {
  if (this != &other) {
    Binary_tree<K, T>::operator=(other);
  }
  return *this;
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const value_type &value) {
  std::pair<iterator, bool> return_value;
  if (Binary_tree<K, T>::root_ == nullptr) {
    Binary_tree<K, T>::root_ = new typename Binary_tree<K, T>::Node(K, obj);
    return_value.first = iterator(Binary_tree<K, T>::root_);
    return_value.second = true;
  } else {
    bool check_insert =
        Binary_tree<K, T>::RecursiveInsert(Binary_tree<K, T>::root_, K, obj);
    return_value.first = find(K);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename K, typename T>
typename map<K, T>::value_type &map<K, T>::MapIterator::operator*() {
  if (Binary_tree<K, T>::Iterator::iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  std::pair<const K_type, mapped_type> pr =
      std::make_pair(Binary_tree<K, T>::Iterator::iter_node_->K_,
                     Binary_tree<K, T>::Iterator::iter_node_->value_);
  std::pair<const K_type, mapped_type> &ref = pr;
  return ref;
}

template <typename K, typename T>
T &map<K, T>::MapIterator::return_value() {
  if (Binary_tree<K, T>::Iterator::iter_node_ == nullptr) {
    static T fake_value{};
    return fake_value;
  }
  return Binary_tree<K, T>::Iterator::iter_node_->value_;
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::find(const K &K) {
  typename Binary_tree<K, T>::Node *node =
      Binary_tree<K, T>::RecursiveFind(Binary_tree<K, T>::root_, K);
  return iterator(node);
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert_or_assign(
    const K &K, const T &obj) {
  auto it = find(K);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(K, obj);
    pr.second = false;
    return pr;
  }
  return insert(K, obj);
}

template <typename K, typename T>
template <class... Args>
std::vector<std::pair<typename map<K, T>::iterator, bool>>
map<K, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<K, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename K, typename T>
T &map<K, T>::at(const K &K) {
  auto it = find(K);
  if (it == nullptr)
    throw std::out_of_range(
        "Container does not have an element with the specified K");
  return it.return_value();
}

template <typename K, typename T>
T &map<K, T>::operator[](const K &K) {
  auto it = find(K);
  if (it == nullptr) {
    auto pr = insert(std::make_pair(K, T()));
    it = pr.first;
  }
  return it.return_value();
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::begin() {
  return map<K, T>::MapIterator(
      Binary_tree<K, T>::GetMin(Binary_tree<K, T>::root_));
}

template <typename K, typename T>
typename map<K, T>::iterator map<K, T>::end() {
  if (Binary_tree<K, T>::root_ == nullptr) return begin();

  typename Binary_tree<K, T>::Node *last_node =
      Binary_tree<K, T>::GetMax(Binary_tree<K, T>::root_);
  MapIterator test(nullptr, last_node);
  return test;
}

template <typename K, typename T>
typename map<K, T>::const_iterator map<K, T>::cbegin() const {
  return map<K, T>::ConstMapIterator(
      Binary_tree<K, T>::GetMin(Binary_tree<K, T>::root_));
}

template <typename K, typename T>
typename map<K, T>::const_iterator map<K, T>::cend() const {
  if (Binary_tree<K, T>::root_ == nullptr) return cbegin();
  typename Binary_tree<K, T>::Node *last_node =
      Binary_tree<K, T>::GetMax(Binary_tree<K, T>::root_);
  ConstMapIterator test(nullptr, last_node);
  return test;
}

template <typename K, typename T>
void map<K, T>::merge(map &other) {
  map const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto K = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<iterator, bool> pr = insert(K, obj);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename K, typename T>
void map<K, T>::erase(map::iterator pos) {
  if (Binary_tree<K, T>::root_ == nullptr || pos.iter_node_ == nullptr) return;
  Binary_tree<K, T>::root_ = Binary_tree<K, T>::RecursiveDelete(
      Binary_tree<K, T>::root_, (*pos).first);
}
}  // namespace s21