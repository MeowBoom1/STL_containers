namespace s21 {

template <typename K, typename T>
associative_container<K, T>::associative_container(
    const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename K, typename T>
associative_container<K, T> &associative_container<K, T>::operator=(
    associative_container &&other) noexcept {
  if (this != &other) {
    Binary_tree<K, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename K, typename T>
associative_container<K, T> &associative_container<K, T>::operator=(
    const associative_container &other) {
  if (this != &other) {
    Binary_tree<K, T>::operator=(other);
  }
  return *this;
}

template <typename K, typename T>
std::pair<typename associative_container<K, T>::iterator, bool>
associative_container<K, T>::insert(const value_type &value) {
  std::pair<iterator, bool> return_value;
  value_type val = value;
  if (Binary_tree<K, T>::root_ == nullptr) {
    Binary_tree<K, T>::root_ = new typename Binary_tree<K, T>::Node(value);
    return_value.first = iterator(Binary_tree<K, T>::root_);
    return_value.second = true;
  } else {
    bool check_insert =
        Binary_tree<K, T>::RecursiveInsert(Binary_tree<K, T>::root_, value);
    return_value.first = find(val);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename K, typename T>
typename associative_container<K, T>::value_type &
associative_container<K, T>::AssIterator::operator*() {
  if (Binary_tree<K, T>::Iterator::iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  std::pair<const key_type, mapped_type> pr =
      std::make_pair(Binary_tree<K, T>::Iterator::iter_node_->value_.first,
                     Binary_tree<K, T>::Iterator::iter_node_->value_.second);
  std::pair<const key_type, mapped_type> &ref = pr;
  return ref;
}

template <typename K, typename T>
T &associative_container<K, T>::AssIterator::return_value() {
  if (Binary_tree<K, T>::Iterator::iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value.second;
  }
  return Binary_tree<K, T>::Iterator::iter_node_->value_.second;
}

template <typename K, typename T>
typename associative_container<K, T>::iterator
associative_container<K, T>::find(const value_type &key) {
  typename Binary_tree<K, T>::Node *node =
      Binary_tree<K, T>::RecursiveFind(Binary_tree<K, T>::root_, key);
  return iterator(node);
}

template <typename K, typename T>
typename associative_container<K, T>::iterator
associative_container<K, T>::find(const K &key) {
  value_type sec_key = {key, 0};
  typename Binary_tree<K, T>::Node *node =
      Binary_tree<K, T>::RecursiveFind(Binary_tree<K, T>::root_, sec_key);
  return iterator(node);
}

template <typename K, typename T>
std::pair<typename associative_container<K, T>::iterator, bool>
associative_container<K, T>::insert_or_assign(const value_type &value) {
  auto it = find(value);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(value.first, value.second);
    pr.second = false;
    return pr;
  }
  return insert(value.first, value.second);
}

template <typename K, typename T>
template <class... Args>
vector<std::pair<typename associative_container<K, T>::iterator, bool>>
associative_container<K, T>::insert_many(Args &&...args) {
  vector<std::pair<typename associative_container<K, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename K, typename T>
T &associative_container<K, T>::at(const value_type &key) {
  auto it = find(key);
  if (it == nullptr) throw std::out_of_range("There is no such container");
  return it.return_value();
}

template <typename K, typename T>
T &associative_container<K, T>::operator[](const K &key) {
  auto it = find({key, 0});
  if (it == nullptr) {
    auto pr = insert(std::make_pair(key, T()));
    it = pr.first;
  }
  return it.return_value();
}

template <typename K, typename T>
typename associative_container<K, T>::iterator
associative_container<K, T>::begin() {
  return associative_container<K, T>::AssIterator(
      Binary_tree<K, T>::GetMin(Binary_tree<K, T>::root_));
}

template <typename K, typename T>
typename associative_container<K, T>::iterator
associative_container<K, T>::end() {
  if (Binary_tree<K, T>::root_ == nullptr) return begin();
  return associative_container<K, T>::AssIterator(
      Binary_tree<K, T>::GetMax(Binary_tree<K, T>::root_));
}

template <typename K, typename T>
typename associative_container<K, T>::const_iterator
associative_container<K, T>::cbegin() const {
  return associative_container<K, T>::ConstMapIterator(
      Binary_tree<K, T>::GetMin(Binary_tree<K, T>::root_));
}

template <typename K, typename T>
typename associative_container<K, T>::const_iterator
associative_container<K, T>::cend() const {
  if (Binary_tree<K, T>::root_ == nullptr) return cbegin();

  typename Binary_tree<K, T>::Node *last_node =
      Binary_tree<K, T>::GetMax(Binary_tree<K, T>::root_);
  ConstAssIterator test(nullptr, last_node);
  return test;
}

template <typename K, typename T>
void associative_container<K, T>::merge(associative_container &other) {
  associative_container const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto key = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<iterator, bool> pr = insert(key, obj);
    if (pr.second) other.erase(pr.first);
  }
}
}  // namespace s21