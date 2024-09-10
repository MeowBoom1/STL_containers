#include "s21_map.h"

namespace s21 {

// template <typename K, typename T>
// map<K,T>::map() {
//   Binary_tree<K,T>
// }

// }

template <typename K, typename T>
map<K, T>::map(std::initializer_list<value_type> const &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K, typename T>
std::pair<typename map<K, T>::iterator, bool> map<K, T>::insert(
    const value_type &value) {
  std::pair<iterator, bool> rvalue;
  if (Binary_tree<K, T>::root_ == nullptr) }
}  // namespace s21
