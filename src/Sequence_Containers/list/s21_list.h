#ifndef S21_CPP_LIST
#define S21_CPP_LIST
#include <iostream>
#include <limits>

#include "../s21_Sequence_Container.h"

namespace s21 {
template <typename T>
class list : public Sequence_Container<T> {
 private:
  struct Node {
    T value;
    Node *next;
    Node *prev;
    Node(const T &val) : value(val), next(nullptr), prev(nullptr) {}
  };
  Node *head;
  Node *tail;
  Node *TempTail;
  size_t listSize;
  using typename container<T>::value_type;
  using typename container<T>::reference;
  using typename container<T>::const_reference;
  using typename container<T>::size_type;

  Node *split(Node *node, size_type size);
  Node *merge_sorted(Node *left, Node *right);
  void set_temp_tail();

 public:
  void sort() {
    if (listSize <= 1) return;
    tail->next = nullptr;
    TempTail->prev = nullptr;
    Node *left{nullptr}, *right{nullptr}, *curr{nullptr};
    Node *sorted_head{nullptr}, *sorted_tail{nullptr};
    for (size_type i = 1; i < listSize; i *= 2) {
      curr = (i == 1 ? head : sorted_head), sorted_head = nullptr,
      sorted_tail = nullptr;
      while (curr) {
        left = curr;
        right = split(left, i);
        curr = split(right, i);
        Node *merged_part = merge_sorted(left, right);
        if (!sorted_head) {
          sorted_head = merged_part;
          sorted_tail = merged_part;
        } else {
          sorted_tail->next = merged_part;
          merged_part->prev = sorted_tail;
        }
        while (sorted_tail->next) {
          sorted_tail = sorted_tail->next;
        }
      }
    }
    head = sorted_head;
    tail = sorted_tail;
    TempTail->prev = tail;
    tail->next = TempTail;
  };
  class ListIterator {
   protected:
    Node *current;
    friend class list<T>;

   public:
    Node *get_node() const { return current; }
    explicit ListIterator(Node *node)
        : current(node){

          };
    reference operator*() const { return current->value; }
    ListIterator &operator++() {
      if (current->next) current = current->next;
      return *this;
    }
    ListIterator operator++(int) {
      ListIterator copy = *this;
      ++(*this);
      return copy;
    }
    ListIterator &operator--() {
      if (current->prev) current = current->prev;
      return *this;
    }
    ListIterator operator--(int) {
      ListIterator copy = *this;
      --(*this);
      return copy;
    }
    bool operator==(const ListIterator &other) const {
      return (this->current == other.current);
    }
    bool operator!=(const ListIterator &other) const {
      return (this->current != other.current);
    }
  };
  class ListConstIterator : public ListIterator {
   public:
    using ListIterator::ListIterator;  // Копирует конструктор
    ListConstIterator(const ListIterator &it) : ListIterator(it) {}
    const_reference operator*() const { return this->current->value; };
    Node *get_node() const { return this->current; }
  };
  using const_iterator = ListConstIterator;
  using iterator = ListIterator;
  // void sort();
  void erase(iterator pos);
  iterator begin() { return iterator(this->head); }
  iterator end() { return iterator(TempTail); }
  iterator insert(iterator pos, const_reference value);
  size_type size() const { return (this->listSize); }
  size_type max_size() {
    return std::numeric_limits<typename list<T>::size_type>::max() / sizeof(T);
  }
  list();
  list(size_type n);
  list(const list &l);
  list(list &&l);
  list(std::initializer_list<value_type> const &items);
  ~list();
  list &operator=(list &&l);
  const_reference front();
  const_reference back();
  void push_front(const_reference value);
  virtual bool empty() const override { return (listSize == 0); };
  void swap(list &other);
  void pop_front() override;
  void pop_back() override;
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse() override;
  void unique() override;
  void push_back(const T &value) override;
  void clear() override;
  // void output() override;
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  template <typename... Args>
  void insert_many_front(Args &&...args);
};

}  // namespace s21
#include "s21_list.tpp"
#endif
