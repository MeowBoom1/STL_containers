#include "binary_tree.h"

template <typename K, typename T>
Binary_tree<K, T>::Binary_tree() : root_(nullptr) {}

template <typename K, typename T>
Binary_tree<K, T>::Binary_tree(const Binary_tree &other) {
  root_ = CopyTree(other.root_, nullptr);
}

template <typename K, typename T>
Binary_tree<K, T>::Binary_tree(Binary_tree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename K, typename T>
Binary_tree<K, T>::~Binary_tree() {
  clear();
}

template <typename K, typename T>
Binary_tree<K, T> &Binary_tree<K, T>::operator=(Binary_tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename K, typename T>
Binary_tree<K, T> &Binary_tree<K, T>::operator=(const Binary_tree &other) {
  if (this != &other) {
    Binary_tree temp(other);
    FreeNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Iterator Binary_tree<K, T>::begin() {
  return Binary_tree::Iterator(GetMin(root_));
}

template <typename K, typename T>
typename Binary_tree<K, T>::Iterator Binary_tree<K, T>::end() {
  return Binary_tree::Iterator(GetMax(root_));
}

template <typename K, typename T>
typename Binary_tree<K, T>::ReverseIterator Binary_tree<K, T>::rbegin() {
  return Binary_tree::ReverseIterator(GetMax(root_));
}

template <typename K, typename T>
typename Binary_tree<K, T>::ReverseIterator Binary_tree<K, T>::rend() {
  return Binary_tree::ReverseIterator(GetMin(root_));
}

template <typename K, typename T>
bool Binary_tree<K, T>::empty() {
  return root_ == nullptr;
}

template <typename K, typename T>
size_t Binary_tree<K, T>::size() {
  return RecursiveSize(root_);
}

// template <typename K, typename T>
// size_t Binary_tree<K, T>::max_size() {
//   return std::numeric_limits<size_type>::max() /
//          sizeof(typename Binary_tree<K, T>::Node);
// }

template <typename K, typename T>
void Binary_tree<K, T>::clear() {
  if (root_ != nullptr) FreeNode(root_);
  root_ = nullptr;
}

template <typename K, typename T>
std::pair<typename Binary_tree<K, T>::Iterator, bool> Binary_tree<K, T>::insert(
    const value_type &key) {
  std::pair<Iterator, bool> value;
  if (root_ == nullptr) {
    value_type sec_key = key;
    root_ = new Node({sec_key.first, sec_key.second});
    value.first = Iterator(root_);
    value.second = true;
  } else {
    value_type sec_key = key;
    bool check_insert = RecursiveInsert(root_, sec_key);
    value.first = Find(key);
    value.second = check_insert;
  }
  return value;
}

template <typename K, typename T>
void Binary_tree<K, T>::erase(iterator pos) {
  if (root_ == nullptr || pos.iter_node_ == nullptr) return;
  root_ = RecursiveDelete(root_, *pos);
}

template <typename K, typename T>
void Binary_tree<K, T>::erase(K &key) {
  if (root_ == nullptr) return;
  value_type pos = {key, 0};
  root_ = RecursiveDelete(root_, pos);
}

template <typename K, typename T>
void Binary_tree<K, T>::swap(Binary_tree &other) {
  std::swap(root_, other.root_);
}

template <typename K, typename T>
void Binary_tree<K, T>::merge(Binary_tree &other) {
  Binary_tree const_tree(other);
  Iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    std::pair<Iterator, bool> pr = insert(*const_it);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::Find(
    const value_type &key) {
  value_type sec_key = key;
  Node *exact_node = RecursiveFind(root_, sec_key);
  return Iterator(exact_node);
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::Find(const K &key) {
  value_type sec_key = {key, 0};
  Node *exact_node = RecursiveFind(root_, sec_key);
  return Iterator(exact_node);
}

template <typename K, typename T>
bool Binary_tree<K, T>::contains(const value_type &key) {
  // value_type sec_key = key;
  Node *contain_node = RecursiveFind(root_, key);
  return !(contain_node == nullptr);
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::Iterator::MoveForward(
    Binary_tree::Node *node) {
  if (node->right_ != nullptr) {
    return GetMin(node->right_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::Iterator::MoveBack(
    Binary_tree::Node *node) {
  if (node->left_ != nullptr) {
    return GetMax(node->left_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *
Binary_tree<K, T>::ReverseIterator::ReverseMoveForward(
    Binary_tree::Node *node) {
  if (node->left_ != nullptr) {
    return GetMax(node->left_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *
Binary_tree<K, T>::ReverseIterator::ReverseMoveBack(Binary_tree::Node *node) {
  if (node->right_ != nullptr) {
    return GetMin(node->right_);
  }
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename K, typename T>
Binary_tree<K, T>::Iterator::Iterator()
    : iter_node_(nullptr), iter_past_node_(nullptr) {}

template <typename K, typename T>
Binary_tree<K, T>::Iterator::Iterator(Binary_tree::Node *node,
                                      Binary_tree::Node *past_node)
    : iter_node_(node), iter_past_node_(past_node) {}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator &
Binary_tree<K, T>::Iterator::operator++() {
  Node *tmp;
  if (iter_node_ != nullptr) {
    tmp = GetMax(iter_node_);
  }
  iter_node_ = MoveForward(iter_node_);
  if (iter_node_ == nullptr) {
    iter_past_node_ = tmp;
  }
  return *this;
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::Iterator::operator++(
    int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator &
Binary_tree<K, T>::Iterator::operator--() {
  if (iter_node_ == nullptr && iter_past_node_ != nullptr) {
    *this = iter_past_node_;
    return *this;
  }
  iter_node_ = MoveBack(iter_node_);
  return *this;
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::iterator::operator--(
    int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename K, typename T>
typename Binary_tree<K, T>::reference &
Binary_tree<K, T>::iterator::operator*() {
  if (iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  return iter_node_->value_;
}

template <typename K, typename T>
bool Binary_tree<K, T>::Iterator::operator==(const Binary_tree::iterator &it) {
  return iter_node_ == it.iter_node_;
}

template <typename K, typename T>
bool Binary_tree<K, T>::Iterator::operator!=(const Binary_tree::iterator &it) {
  return iter_node_ != it.iter_node_;
}

template <typename K, typename T>
Binary_tree<K, T>::ReverseIterator::ReverseIterator()
    : reverse_iter_node_(nullptr), reverse_iter_past_node_(nullptr) {}

template <typename K, typename T>
Binary_tree<K, T>::ReverseIterator::ReverseIterator(
    Binary_tree::Node *node, Binary_tree::Node *past_node)
    : reverse_iter_node_(node), reverse_iter_past_node_(past_node) {}

template <typename K, typename T>
typename Binary_tree<K, T>::ReverseIterator &
Binary_tree<K, T>::ReverseIterator::operator++() {
  if (reverse_iter_node_ == nullptr && reverse_iter_past_node_ != nullptr) {
    *this = reverse_iter_past_node_;
    return *this;
  }
  reverse_iter_node_ = ReverseMoveForward(reverse_iter_node_);
  return *this;
}

template <typename K, typename T>
typename Binary_tree<K, T>::ReverseIterator &
Binary_tree<K, T>::ReverseIterator::operator--() {
  Node *tmp;
  if (reverse_iter_node_ != nullptr) {
    tmp = GetMax(reverse_iter_node_);
  }
  reverse_iter_node_ = ReverseMoveBack(reverse_iter_node_);
  if (reverse_iter_node_ == nullptr) {
    reverse_iter_past_node_ = tmp;
  }
  return *this;
}

template <typename K, typename T>
typename Binary_tree<K, T>::reference &
Binary_tree<K, T>::ReverseIterator::operator*() {
  if (reverse_iter_node_ == nullptr) {
    static value_type fake_value{};
    return fake_value;
  }
  return reverse_iter_node_->value_;
}

template <typename K, typename T>
bool Binary_tree<K, T>::ReverseIterator::operator==(
    const reverse_iterator &it) {
  return reverse_iter_node_ == it.reverse_iter_node_;
}

template <typename K, typename T>
bool Binary_tree<K, T>::ReverseIterator::operator!=(
    const reverse_iterator &it) {
  return reverse_iter_node_ != it.reverse_iter_node_;
}

template <typename K, typename T>
Binary_tree<K, T>::Node::Node(value_type value) {
  value_.first = value.first;
  value_.second = value.second;
}

template <typename K, typename T>
Binary_tree<K, T>::Node::Node(value_type value, Node *parent) {
  value_.first = value.first;
  value_.second = value.second;
  parent_ = parent;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::CopyTree(
    Binary_tree::Node *node, Binary_tree::Node *parent) {
  if (node == nullptr) return nullptr;
  Node *new_node = new Node(node->value_, parent);
  new_node->left_ = CopyTree(node->left_, new_node);
  new_node->right_ = CopyTree(node->right_, new_node);
  return new_node;
}

template <typename K, typename T>
void Binary_tree<K, T>::FreeNode(Node *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

template <typename K, typename T>
int Binary_tree<K, T>::GetHeight(Binary_tree::Node *node) {
  return node == nullptr ? -1 : node->height_;
}

template <typename K, typename T>
int Binary_tree<K, T>::GetBalance(Binary_tree::Node *node) {
  return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->left_);
}

template <typename K, typename T>
void Binary_tree<K, T>::SetHeight(Binary_tree::Node *node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

template <typename K, typename T>
void Binary_tree<K, T>::SwapValue(Binary_tree::Node *a, Binary_tree::Node *b) {
  std::swap(a->value_.first, b->value_.first);
  std::swap(a->value_.second, b->value_.second);
}

template <typename K, typename T>
void Binary_tree<K, T>::RightRotate(Binary_tree::Node *node) {
  Node *new_left = node->left_->left_;
  Node *new_right_right = node->right_;
  Node *new_right_left = node->left_->right_;

  SwapValue(node, node->left_);
  node->right_ = node->left_;

  node->left_ = new_left;
  if (node->left_) {
    node->left_->parent_ = node;
  }

  node->right_->left_ = new_right_left;
  if (node->right_->left_) {
    node->right_->left_->parent_ = node->right_;
  }

  node->right_->right_ = new_right_right;
  if (node->right_->right_) {
    node->right_->right_->parent_ = node->right_;
  }

  SetHeight(node->right_);
  SetHeight(node);
}

template <typename K, typename T>
void Binary_tree<K, T>::LeftRotate(Binary_tree::Node *node) {
  Node *new_right = node->right_->right_;
  Node *new_left_left = node->left_;
  Node *new_left_right = node->right_->left_;

  SwapValue(node, node->right_);
  node->left_ = node->right_;

  node->right_ = new_right;
  if (node->right_) {
    node->right_->parent_ = node;
  }

  node->left_->right_ = new_left_right;
  if (node->left_->right_) {
    node->left_->right_->parent_ = node->left_;
  }

  node->left_->left_ = new_left_left;
  if (node->left_->left_) {
    node->left_->left_->parent_ = node->left_;
  }

  SetHeight(node->left_);
  SetHeight(node);
}

template <typename K, typename T>
void Binary_tree<K, T>::Balance(Node *node) {
  int balance = GetBalance(node);
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
    RightRotate(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotate(node->right_);
    LeftRotate(node);
  }
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::GetMin(
    Binary_tree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMin(node->left_);
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::GetMax(
    Binary_tree::Node *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMax(node->right_);
}

template <typename K, typename T>
size_t Binary_tree<K, T>::RecursiveSize(Binary_tree::Node *node) {
  if (node == nullptr) return 0;
  size_t left_size = RecursiveSize(node->left_);
  size_t right_size = RecursiveSize(node->right_);
  return 1 + left_size + right_size;
}

template <typename K, typename T>
bool Binary_tree<K, T>::RecursiveInsert(Binary_tree::Node *node,
                                        const value_type &key) {
  bool check_insert = false;
  if (key.first < node->value_.first) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(key, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->left_, key);
    }
  } else if (key.first > node->value_.first) {
    if (node->right_ == nullptr) {
      node->right_ = new Node(key, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->right_, key);
    }
  } else if (key.first == node->value_.first) {
    return check_insert;
  }
  SetHeight(node);
  Balance(node);
  return check_insert;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::RecursiveDelete(
    Binary_tree::Node *node, value_type key) {
  if (node == nullptr) return nullptr;
  if (key.first < node->value_.first) {
    node->left_ = RecursiveDelete(node->left_, key);
  } else if (key.first > node->value_.first) {
    node->right_ = RecursiveDelete(node->right_, key);
  } else {
    if (node->left_ == nullptr || node->right_ == nullptr) {
      Node *node_right = node->right_;
      Node *node_left = node->left_;
      Node *node_parent = node->parent_;
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) node->parent_ = node_parent;
    } else {
      Node *min_in_right = GetMin(node->right_);
      // node->value_.first = min_in_right->value_.first;
      node->value_ = min_in_right->value_;
      node->right_ = RecursiveDelete(node->right_, min_in_right->value_);
    }
  }
  if (node != nullptr) {
    SetHeight(node);
    Balance(node);
  }
  return node;
}

template <typename K, typename T>
typename Binary_tree<K, T>::Node *Binary_tree<K, T>::RecursiveFind(
    Binary_tree::Node *node, const value_type &key) {
  if (node == nullptr || node->value_.first == key.first) return node;
  if (key.first > node->value_.first) {
    return RecursiveFind(node->right_, key);
  } else {
    return RecursiveFind(node->left_, key);
  }
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::lower_bound(K &key) {
  iterator result = Find({key, 0});
  return --result;
}

template <typename K, typename T>
typename Binary_tree<K, T>::iterator Binary_tree<K, T>::upper_bound(K &key) {
  iterator result = Find({key, 0});
  return ++result;
}

template <typename K, typename T>
std::pair<typename Binary_tree<K, T>::iterator,
          typename Binary_tree<K, T>::iterator>
Binary_tree<K, T>::equal_range(K &key) {
  std::pair<iterator, iterator> result;
  result.first = lower_bound(key);
  result.second = upper_bound(key);
  return result;
}