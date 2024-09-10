namespace s21 {

// Constructors and Destructor
template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list& l) : list() {
  for (auto it = l.begin(); it != l.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list&& l) noexcept : list() {
  move_nodes(l);
}

template <typename T>
list<T>::~list() {
  clear();
}

// Assignment operators
template <typename T>
list<T>& list<T>::operator=(const list& l) {
  if (this != &l) {
    clear();
    for (auto it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& l) noexcept {
  if (this != &l) {
    clear();
    move_nodes(l);
  }
  return *this;
}

// Element Access
template <typename T>
typename list<T>::const_reference list<T>::front() const {
  return head_->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  return tail_->data;
}

// Iterators
template <typename T>
typename list<T>::iterator list<T>::begin() noexcept {
  return iterator(head_);
}

template <typename T>
typename list<T>::const_iterator list<T>::begin() const noexcept {
  return const_iterator(head_);
}

template <typename T>
typename list<T>::iterator list<T>::end() noexcept {
  return iterator(nullptr);
}

template <typename T>
typename list<T>::const_iterator list<T>::end() const noexcept {
  return const_iterator(nullptr);
}

// Capacity
template <typename T>
bool list<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const noexcept {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

// Modifiers
template <typename T>
void list<T>::clear() noexcept {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* new_node = new Node(value);
  Node* current = pos.getNode();
  if (current) {
    Node* prev_node = current->prev;
    link_nodes(new_node, current);
    if (prev_node) {
      link_nodes(prev_node, new_node);
    } else {
      head_ = new_node;
    }
  } else {
    push_back(value);
    return iterator(tail_);
  }
  ++size_;
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  Node* current = pos.getNode();
  if (current) {
    Node* prev_node = current->prev;
    Node* next_node = current->next;
    if (prev_node) {
      prev_node->next = next_node;
    } else {
      head_ = next_node;
    }
    if (next_node) {
      next_node->prev = prev_node;
    } else {
      tail_ = prev_node;
    }
    delete current;
    --size_;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);
  if (tail_) {
    link_nodes(tail_, new_node);
  } else {
    head_ = new_node;
  }
  tail_ = new_node;
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node* prev_node = tail_->prev;
    delete tail_;
    tail_ = prev_node;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);
  if (head_) {
    link_nodes(new_node, head_);
  } else {
    tail_ = new_node;
  }
  head_ = new_node;
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (head_) {
    Node* next_node = head_->next;
    delete head_;
    head_ = next_node;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }
    --size_;
  }
}

template <typename T>
void list<T>::swap(list& other) noexcept {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    auto it1 = begin();
    auto it2 = other.begin();
    while (it1 != end() && it2 != other.end()) {
      if (*it2 < *it1) {
        auto next = it2;
        ++next;
        splice(it1, other);
        it2 = next;
      } else {
        ++it1;
      }
    }
    if (it2 != other.end()) {
      splice(end(), other);
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  if (other.empty()) return;

  Node* pos_node = pos.getNode();
  Node* other_head = other.head_;
  Node* other_tail = other.tail_;

  if (pos_node) {
    Node* prev_node = pos_node->prev;
    if (prev_node) {
      link_nodes(prev_node, other_head);
    } else {
      head_ = other_head;
    }
    link_nodes(other_tail, pos_node);
  } else {
    if (tail_) {
      link_nodes(tail_, other_head);
    } else {
      head_ = other_head;
    }
    tail_ = other_tail;
  }

  size_ += other.size_;
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
void list<T>::reverse() noexcept {
  if (empty()) return;

  Node* current = head_;
  Node* temp = nullptr;

  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp) {
    head_ = temp->prev;
    tail_ = temp->next;
  }
}

template <typename T>
void list<T>::unique() {
  if (empty()) return;

  for (auto it = begin(); it != end();) {
    auto next = it;
    ++next;
    if (next != end() && *it == *next) {
      erase(next);
    } else {
      ++it;
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) return;

  for (auto it = begin(); it != end(); ++it) {
    for (auto jt = it; jt != end(); ++jt) {
      if (*jt < *it) {
        std::swap(*it, *jt);
      }
    }
  }
}

// Private methods
template <typename T>
void list<T>::init_empty() {
  head_ = tail_ = nullptr;
  size_ = 0;
}

template <typename T>
void list<T>::link_nodes(Node* first, Node* second) {
  first->next = second;
  second->prev = first;
}

template <typename T>
void list<T>::move_nodes(list& other) {
  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;

  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

}  // namespace s21
