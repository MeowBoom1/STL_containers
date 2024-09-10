#ifndef MAP_H
#define MAP_H

#include "../s21_containers.h"

namespace s21 {
template <typename K, typename T>
class map : public associative_container<K, T> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;

  map() : associative_container<K, T>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : associative_container<K, T>(other){};
  map(map &&other) noexcept : associative_container<K, T>(std::move(other)){};
  ~map() = default;
};
};  // namespace s21

#endif