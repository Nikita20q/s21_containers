#ifndef S21_CPP_ARRAY
#define S21_CPP_ARRAY

#include <limits>

#include "../container/s21_container.h"

namespace s21 {
template <typename T, size_t N>
class array : public container<T> {
 private:
  T data_[N];

 public:
  using typename container<T>::value_type;
  using typename container<T>::size_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::key_type;
  using iterator = T *;
  using const_iterator = const T *;
  array() = default;
  size_type size() const noexcept override { return N; }
  array(std::initializer_list<value_type> const &items) {
    size_t len = (N > items.size() ? items.size() : N);
    size_t i = 0;
    for (auto it = items.begin(); it != items.end() && i < len; ++it, ++i) {
      data_[i] = *it;
    }
    for (; i < N; ++i) {
      data_[i] = T{};
    }
  }
  array(const array &a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
  }
  array(array &&a) {
    for (size_t i = 0; i < N; ++i) {
      data_[i] = std::move(a.data_[i]);
    }
  }
  array &operator=(array &&a) noexcept {
    if (this != &a) {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    return *this;
  }
  ~array() = default;
  reference at(size_type pos) {
    if (pos > N) {
      throw std::out_of_range("Выход за границы массива");  // GCOVR_EXCL_LINE
    }
    return data_[pos];
  };

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() { return data_[0]; };
  const_reference back() { return data_[N - 1]; };

  iterator data() { return data_; }
  iterator begin() { return data_; }
  iterator end() { return data_ + N; }

  const_iterator data() const { return data_; }
  const_iterator begin() const { return data_; }
  const_iterator end() const { return data_ + N; }

  bool empty() const override { return (N == 0); }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }
  void swap(array &other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }
  void fill(const_reference value) {
    for (size_type i = 0; i < N; i++) {
      data_[i] = value;
    }
  }
};
}  // namespace s21

#endif