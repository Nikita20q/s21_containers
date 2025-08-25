#ifndef S21_CPP_SEQUENCE_CONTAINER
#define S21_CPP_SEQUENCE_CONTAINER

#include <iostream>

#include "../container/s21_container.h"

namespace s21 {
template <typename T>
class Sequence_Container : public s21::container<T> {
 protected:
 public:
  virtual void unique() = 0;
  virtual void reverse() = 0;
  virtual void push_back(const T &value) = 0;
  virtual void pop_back() = 0;
  // virtual void output() = 0;
  virtual void clear() = 0;
  virtual void pop_front() = 0;
  // virtual void swap(Sequence_Container &other) = 0;
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;
  Sequence_Container() = default;
  virtual ~Sequence_Container() {
    // clear();
    // std::cout << "Good";
  }
  // const_reference front();
  // size_type max_size() { return (this->listSize + 1); }
};
}  // namespace s21

// #include "s21_Sequence_Container.tpp"

#endif