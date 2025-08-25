#include <limits>

namespace s21 {
template <typename T>
void s21::vector<T>::unique() {
  if (size_ > 1) {
    int write_index = 0;
    int duplicates = 0;

    for (size_type i = 0; i < size_; ++i) {
      if (i == 0 || data_[i] != data_[i - 1]) {
        if (duplicates > 0) {
          data_[write_index] = data_[i];
        }
        ++write_index;
      } else {
        ++duplicates;
      }
    }

    size_ = write_index;
  }
}

template <typename T>
void s21::vector<T>::reverse() {
  for (size_type i = 0; i < size_ / 2; i++)
    std::swap(data_[i], data_[size_ - i - 1]);
}

template <typename T>
void s21::vector<T>::push_back(const T &value) {
  if (capacity_ > size_) {
    data_[size_] = value;
  } else {
    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

    T *temp = new T[capacity_];  // GCOVR_EXCL_LINE

    for (size_type i = 0; i < size_; ++i) {
      temp[i] = data_[i];
    }

    delete[] data_;  // GCOVR_EXCL_LINE
    data_ = temp;
    temp = nullptr;
  }

  data_[size_++] = value;
}

template <typename T>
void s21::vector<T>::pop_back() {
  if (size_ > 0) {
    size_--;
  }
}

template <typename T>
void s21::vector<T>::clear() {
  for (size_type i = 0; i < size_; ++i) {
    data_[i].~T();
  }
  size_ = 0;
}

template <typename T>
bool s21::vector<T>::empty() const {
  return (size_ == 0);
}

template <typename T>
void s21::vector<T>::pop_front() {
  if (size_ == 0) {
    throw std::out_of_range("Длина вектора = 0");  // GCOVR_EXCL_LINE
  }
  std::copy(data_ + 1, data_ + size_, data_);
  size_--;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<typename vector<T>::size_type>::max() / sizeof(T);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(iterator pos,
                                                    Args &&...args) {
  auto it = pos;
  ((it = insert(it, std::forward<Args>(args)), ++it), ...);
  return pos;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(const_iterator pos,
                                               const_reference value) {
  if (empty()) {
    reserve(1);
    data_[0] = value;
    size_++;
    return begin();
  }
  if ((pos.getData()) == nullptr)
    throw std::out_of_range("Некорректный итератор");  // GCOVR_EXCL_LINE
  size_type pos_index = pos.getData() - begin().getData();

  if (size_ >= capacity_) {
    size_type new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T *new_data = new T[new_capacity];  // GCOVR_EXCL_LINE

    for (size_type i = 0; i < pos_index; ++i) {
      new_data[i] = data_[i];
    }

    new_data[pos_index] = value;

    for (size_type i = pos_index; i < size_; ++i) {
      new_data[i + 1] = data_[i];
    }

    delete[] data_;  // GCOVR_EXCL_LINE
    data_ = new_data;
    capacity_ = new_capacity;
    ++size_;
  } else {
    for (size_t i = size_; i > pos_index; --i) {
      data_[i] = data_[i - 1];
    }

    data_[pos_index] = value;
    ++size_;
  }
  return iterator(data_ + pos_index);
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T *new_data = new T[size_];  // GCOVR_EXCL_LINE
    for (size_type i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;  // GCOVR_EXCL_LINE
    data_ = new_data;
    new_data = nullptr;
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::reserve(typename vector<T>::size_type size) {
  T *new_data = new T[size];  // GCOVR_EXCL_LINE

  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }

  delete[] data_;  // GCOVR_EXCL_LINE
  data_ = new_data;
  capacity_ = size;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
void vector<T>::erase(iterator pos) {
  if (pos == end()) {
    throw std::out_of_range("Вы чё удаляете-то?...");  // GCOVR_EXCL_LINE
  }

  size_type pos_index = pos.getData() - begin().getData();

  for (size_type i = pos_index; i < size_ - 1; ++i) {
    data_[i] = data_[i + 1];
  }

  size_--;
}
}  // namespace s21