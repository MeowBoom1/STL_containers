namespace s21 {

template <typename Key>
set_container<Key>::set_container(
    const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key>
set_container<Key> &set_container<Key>::operator=(set_container &&other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key>
set_container<Key> &set_container<Key>::operator=(const set_container &other) {
  if (this != &other) {
    Binary_tree<Key, Key>::operator=(other);
  }
  return *this;
}

template <typename Key>
std::pair<typename Binary_tree<Key, Key>::Iterator, bool>
set_container<Key>::insert(const value_type &value) {
  std::pair<typename Binary_tree<Key, Key>::Iterator, bool> result;
  result = Binary_tree<Key, Key>::insert({value, value});
  return result;
}

template <typename Key>
template <class... Args>
vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>>
set_container<Key>::insert_many(Args &&...args) {
  vector<std::pair<typename Binary_tree<Key, Key>::Iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename Key>
typename set_container<Key>::value_type &
set_container<Key>::SetConIterator::operator*() {
  if (Binary_tree<Key, Key>::Iterator::iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  value_type &res = Binary_tree<Key, Key>::Iterator::iter_node_->value_.first;
  return res;
}

template <typename Key>
typename set_container<Key>::value_type &
set_container<Key>::SetConReverseIterator::operator*() {
  if (Binary_tree<Key, Key>::ReverseIterator::reverse_iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  value_type &res =
      Binary_tree<Key, Key>::ReverseIterator::reverse_iter_node_->value_.first;
  return res;
}

template <typename Key>
typename set_container<Key>::iterator set_container<Key>::begin() {
  return set_container<Key>::SetConIterator(
      Binary_tree<Key, Key>::GetMin(Binary_tree<Key, Key>::root_));
}

template <typename Key>
typename set_container<Key>::iterator set_container<Key>::end() {
  return set_container<Key>::SetConIterator(
      Binary_tree<Key, Key>::GetMax(Binary_tree<Key, Key>::root_));
}

template <typename Key>
typename set_container<Key>::reverse_iterator set_container<Key>::rbegin() {
  return set_container<Key>::SetConReverseIterator(
      Binary_tree<Key, Key>::GetMax(Binary_tree<Key, Key>::root_));
}

template <typename Key>
typename set_container<Key>::reverse_iterator set_container<Key>::rend() {
  return set_container<Key>::SetConReverseIterator(
      Binary_tree<Key, Key>::GetMin(Binary_tree<Key, Key>::root_));
}

template <typename Key>
typename set_container<Key>::iterator set_container<Key>::find(const Key &key) {
  typename Binary_tree<Key, Key>::Iterator temp =
      Binary_tree<Key, Key>::Find(key);
  return set_container<Key>::iterator(temp.iter_node_, temp.iter_past_node_);
}

template <typename Key>
typename set_container<Key>::iterator set_container<Key>::lower_bound(
    Key &key) {
  iterator temp = find(key);
  typename Binary_tree<Key, Key>::Iterator temp_bit(temp.iter_node_,
                                                    temp.iter_past_node_);
  --temp_bit;
  return set_container<Key>::iterator(temp_bit.iter_node_,
                                      temp_bit.iter_past_node_);
}

template <typename Key>
typename set_container<Key>::iterator set_container<Key>::upper_bound(
    Key &key) {
  iterator temp = find(key);
  typename Binary_tree<Key, Key>::Iterator temp_bit(temp.iter_node_,
                                                    temp.iter_past_node_);
  ++temp_bit;
  return set_container<Key>::iterator(temp_bit.iter_node_,
                                      temp_bit.iter_past_node_);
}

template <typename Key>
std::pair<typename set_container<Key>::iterator,
          typename set_container<Key>::iterator>
set_container<Key>::equal_range(Key &key) {
  std::pair<iterator, iterator> result;
  result.first = lower_bound(key);
  result.second = upper_bound(key);
  return result;
}
}  // namespace s21