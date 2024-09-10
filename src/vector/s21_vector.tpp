namespace s21 {

// Default constructor
template <typename T>
vector<T>::vector() : data_(nullptr), size_(0), capacity_(0) {}

// Constructor with size
template <typename T>
vector<T>::vector(size_type n) : data_(new T[n]()), size_(n), capacity_(n) {}

// Initializer list constructor
template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : data_(new T[items.size()]), size_(items.size()), capacity_(items.size()) {
  std::copy(items.begin(), items.end(), data_);
}

// Copy constructor
template <typename T>
vector<T>::vector(const vector& v)
    : data_(new T[v.capacity_]), size_(v.size_), capacity_(v.capacity_) {
  std::copy(v.data_, v.data_ + v.size_, data_);
}

// Move constructor
template <typename T>
vector<T>::vector(vector&& v) noexcept
    : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
  v.data_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

// Destructor
template <typename T>
vector<T>::~vector() {
  delete[] data_;
}

// Copy assignment operator
template <typename T>
vector<T>& vector<T>::operator=(const vector& v) {
  if (this != &v) {
    delete[] data_;
    data_ = new T[v.capacity_];
    size_ = v.size_;
    capacity_ = v.capacity_;
    std::copy(v.data_, v.data_ + v.size_, data_);
  }
  return *this;
}

// Move assignment operator
template <typename T>
vector<T>& vector<T>::operator=(vector&& v) noexcept {
  if (this != &v) {
    delete[] data_;
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

// Element Access
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  check_bounds(pos);
  return data_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return data_[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return data_[size_ - 1];
}

template <typename T>
T* vector<T>::data() noexcept {
  return data_;
}

// Iterators
template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return data_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return data_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return data_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return data_ + size_;
}

// Capacity
template <typename T>
bool vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

// template <typename T>
// typename vector<T>::size_type vector<T>::max_size() const noexcept {
//     return std::numeric_limits<size_type>::max();
// }

template <typename T>
void vector<T>::reserve(size_type new_capacity) {
  if (new_capacity > capacity_) {
    reallocate(new_capacity);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    reallocate(size_);
  }
}

// Modifiers
template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - begin();
  if (size_ == capacity_) {
    reallocate(capacity_ ? capacity_ * 2 : 1);
  }
  std::move_backward(begin() + index, end(), end() + 1);
  data_[index] = value;
  ++size_;
  return begin() + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  std::move(pos + 1, end(), pos);
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reallocate(capacity_ ? capacity_ * 2 : 1);
  }
  data_[size_++] = value;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    --size_;
  }
}

template <typename T>
void vector<T>::swap(vector& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// Private Helper Functions
template <typename T>
void vector<T>::reallocate(size_type new_capacity) {
  T* new_data = new T[new_capacity];
  std::move(data_, data_ + size_, new_data);
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
}

template <typename T>
void vector<T>::check_bounds(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of bounds");
  }
}

}  // namespace s21
