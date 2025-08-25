#ifndef S21_CPP_VECTOR
#define S21_CPP_VECTOR

#include <cstdint>
#include <iostream>

#include "../s21_Sequence_Container.h"

namespace s21 {
template <typename T>
class vector : public Sequence_Container<T> {
 public:
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;

 protected:
  T *data_;
  size_type size_;
  size_type capacity_;

 public:
  size_type size() const override { return size_; }
  class VectorIterator {
   private:
    T *itdata;

   public:
    VectorIterator() : itdata(nullptr){};
    T *getData() const { return itdata; }
    explicit VectorIterator(T *ptr) : itdata(ptr) {}
    ~VectorIterator() = default;
    bool operator==(const VectorIterator &other) {
      return (this->itdata == other.itdata);
    }
    bool operator!=(const VectorIterator &other) {
      return (this->itdata != other.itdata);
    }
    VectorIterator operator++() {
      itdata++;
      return *this;
    }
    VectorIterator operator++(int) {
      VectorIterator copy = *this;
      ++(*this);
      return copy;
    }
    VectorIterator operator--() {
      itdata--;
      return *this;
    }
    VectorIterator operator--(int) {
      VectorIterator copy = *this;
      --(*this);
      return copy;
    }
    T &operator*() { return *itdata; }
  };
  class ConstVectorIterator {
   private:
    const T *itdata;

   public:
    ConstVectorIterator(const VectorIterator &it) : itdata(it.getData()) {}
    ConstVectorIterator() : itdata(nullptr){};
    const T *getData() const { return itdata; }
    explicit ConstVectorIterator(const T *ptr) : itdata(ptr) {}
    ~ConstVectorIterator() = default;
    bool operator==(const ConstVectorIterator &other) {
      return (this->itdata == other.itdata);
    }
    bool operator!=(const ConstVectorIterator &other) {
      return (this->itdata != other.itdata);
    }
    ConstVectorIterator operator++() {
      itdata++;
      return *this;
    }
    ConstVectorIterator operator++(int) {
      ConstVectorIterator copy = *this;
      ++(*this);
      return copy;
    }

    ConstVectorIterator operator--() {
      itdata--;
      return *this;
    }
    ConstVectorIterator operator--(int) {
      ConstVectorIterator copy = *this;
      --(*this);
      return copy;
    }
    const T &operator*() const { return *itdata; }
  };

  using iterator = VectorIterator;
  using const_iterator = ConstVectorIterator;

  iterator begin() { return iterator(data_); }
  iterator end() { return iterator(data_ + size_); }
  const_iterator begin() const { return const_iterator(data_); }
  const_iterator end() const { return const_iterator(data_ + size_); }

  vector() : data_(nullptr), size_(0), capacity_(0) {}
  vector(size_type n) : size_(n), capacity_(n) { data_ = new T[size_]; }
  vector(std::initializer_list<value_type> const &items)
      : size_(items.size()), capacity_(items.size()) {
    data_ = new T[size_];  // GCOVR_EXCL_LINE
    int i = 0;
    for (const auto item : items) data_[i++] = item;
  };
  vector(const vector &v) : vector() {
    data_ = new T[v.size_];  // GCOVR_EXCL_LINE
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    for (size_type i = 0; i < size_; i++) data_[i] = v.data_[i];
  }
  ~vector() {
    delete[] data_;  // GCOVR_EXCL_LINE
    size_ = 0;
    capacity_ = 0;
  }
  vector(vector &&v) noexcept
      : data_(v.data_), size_(v.size_), capacity_(v.capacity_) {
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      delete[] data_;  // GCOVR_EXCL_LINE

      data_ = v.data_;
      size_ = v.size_;
      capacity_ = v.capacity_;

      v.data_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
    return *this;
  }
  void output() {
    for (int i = 0; i < capacity_; i++) std::cout << *(data_ + i) << ' ';
    std::cout << std::endl;
  }
  void unique() override;   // готово
  void reverse() override;  // готово
  void erase(iterator pos);
  void push_back(const T &value) override;  // готово
  void pop_back() override;                 // готово
  void clear() override;                    // готово
  bool empty() const override;              // готово
  void pop_front() override;                // готово
  size_type capacity() const;               // готово
  size_type max_size() const;               // готово
  void swap(vector &other) {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }
  reference at(size_type pos)  // готово
  {
    if (0 > pos || pos > size_) {
      throw std::out_of_range("Выход за пределы");  // GCOVR_EXCL_LINE
    }
    return data_[pos];
  }
  reference operator[](size_type pos) { return data_[pos]; }
  T *data() { return data_; }
  const_reference front() const {
    if (data_ == nullptr) {
      throw std::out_of_range("контейнер пустой");  // GCOVR_EXCL_LINE
    }
    return *data_;
  }
  const_reference back() const {
    if (data_ == nullptr) {
      throw std::out_of_range("контейнер пустой");  // GCOVR_EXCL_LINE
    }
    return *(data_ + size_ - 1);
  }
  iterator insert(const_iterator pos, const_reference value);
  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args);
  void shrink_to_fit();
  void reserve(size_type size);
  template <typename... Args>
  void insert_many_back(Args &&...args);
};
}  // namespace s21

#include "s21_vector.tpp"

#endif
