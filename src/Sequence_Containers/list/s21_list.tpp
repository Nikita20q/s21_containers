namespace s21 {
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), listSize(0) {
  TempTail = new Node(T{});  // GCOVR_EXCL_LINE
  TempTail->prev = nullptr;
  TempTail->next = nullptr;
}

template <typename T>
list<T>::~list() {
  clear();
  delete TempTail;  // GCOVR_EXCL_LINE
}

template <typename T>
list<T>::list(size_type n) : list<T>() {
  for (size_type i = 0; i < n; ++i) {
    Node *newNode = new Node(T{});  // GCOVR_EXCL_LINE

    if (!this->head) {
      this->head = this->tail = newNode;
    } else {
      this->tail->next = newNode;
      newNode->prev = this->tail;
      this->tail = newNode;
    }
  }
  this->listSize = n;
  if (tail) {
    set_temp_tail();
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto item : items) {
    Node *NewNode = new Node(item);  // GCOVR_EXCL_LINE
    if (!head) {
      head = NewNode;
      tail = NewNode;
    } else {
      tail->next = NewNode;
      NewNode->prev = tail;
      tail = NewNode;
    }
    listSize++;
  }
  set_temp_tail();
}

template <typename T>
void list<T>::set_temp_tail() {
  tail->next = TempTail;
  TempTail->prev = tail;
}

template <typename T>
typename list<T>::Node *list<T>::split(Node *node, size_type size) {
  Node *tmp = node;
  size_type i = 1;
  while (tmp && i < size) {
    tmp = tmp->next;
    i++;
  }
  if (!tmp) return nullptr;
  Node *tmp_next = tmp->next;
  tmp->next = nullptr;
  // рвем связь, чтобы последнее значение подмассива не
  // тащило за собой следующие узлы. Сортировка только подмассива
  return tmp_next;
};

template <typename T>
typename list<T>::Node *list<T>::merge_sorted(Node *left, Node *right) {
  if (!right) return left;
  Node *merged{nullptr}, *merged_res;
  if (left->value > right->value) {
    merged = right;
    right = right->next;
    merged->next = nullptr;
    if (right) right->prev = nullptr;
  } else {
    merged = left;
    left = left->next;
    merged->next = nullptr;
    if (left) left->prev = nullptr;
  }
  merged_res = merged;
  while (left && right) {
    if (left->value > right->value) {
      merged->next = right;
      right->prev = merged;
      merged = right;
      right = right->next;
      if (right) right->prev = nullptr;
    } else {
      merged->next = left;
      left->prev = merged;
      merged = left;
      left = left->next;
      merged->next = nullptr;
      if (left) left->prev = nullptr;
    }
  }
  if (left) {
    merged->next = left;
    left->prev = merged;
  }
  if (right) {
    merged->next = right;
    right->prev = merged;
  }
  return merged_res;
};

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *NewNode = new Node(value);  // GCOVR_EXCL_LINE
  if (this->listSize == 0) {
    this->head = NewNode;
    this->tail = NewNode;
  } else {
    NewNode->prev = pos.get_node()->prev;
    NewNode->next = pos.get_node();
    if (pos.get_node()->prev) {
      pos.get_node()->prev->next = NewNode;
    } else {
      this->head = NewNode;
    }

    pos.get_node()->prev = NewNode;
  }
  this->listSize++;
  set_temp_tail();
  return iterator(NewNode);
}

template <typename T>
list<T>::list(const list &l) : list<T>() {
  Node *current = l.head;
  while (current != nullptr && current != l.TempTail) {
    Node *newNode = new Node(current->value);
    if (!this->head) {
      this->head = this->tail = newNode;
    } else {
      this->tail->next = newNode;
      newNode->prev = this->tail;
      this->tail = newNode;
    }
    this->listSize++;
    current = current->next;
  }
  if (this->tail) {
    set_temp_tail();
  }
}

template <typename T>
list<T>::list(list &&l) : list<T>() {
  this->head = l.head;
  this->tail = l.tail;
  this->listSize = l.listSize;
  TempTail->prev = tail;

  l.head = nullptr;
  l.tail = nullptr;
  l.listSize = 0;
}

template <typename T>
typename list<T>::list &list<T>::operator=(list &&l) {
  if (this != &l) {
    this->clear();

    this->head = l.head;
    this->tail = l.tail;
    this->listSize = l.listSize;
    TempTail->prev = tail;

    l.head = nullptr;
    l.tail = nullptr;
    l.listSize = 0;
  }

  return *this;
}
template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (!this->head) {
    throw std::out_of_range(
        "Cannot get front() from an empty list");  // GCOVR_EXCL_LINE
  }
  return this->head->value;
}
template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (!this->head)
    throw std::out_of_range(
        "Cannot get back() from an empty list");  // GCOVR_EXCL_LINE

  return this->tail->value;
}
template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.current == TempTail) {
    throw std::out_of_range("Данного узла не существует");  // GCOVR_EXCL_LINE
  }

  Node *nodeToDelete = pos.current;
  Node *prevNode = nodeToDelete->prev;
  Node *nextNode = nodeToDelete->next;

  if (prevNode) {
    prevNode->next = nextNode;
  } else {
    this->head = nextNode;
  }

  if (nextNode != TempTail) {
    nextNode->prev = prevNode;
  } else {
    this->tail = prevNode;
  }

  delete nodeToDelete;  // GCOVR_EXCL_LINE
  this->listSize--;
  set_temp_tail();
}
// template <typename T>
// void list<T>::push_front(const_reference value)
// {
//     Node *newNode = new Node(value);

//     if (this->head)
//     {
//         newNode->next = this->head;
//         this->head->prev = newNode;
//     }
//     else
//     {
//         this->tail = newNode;
//     }

//     this->head = newNode;
//     this->listSize++;
//     TempTail->prev = tail;
// }

template <typename T>
void list<T>::push_front(const_reference value) {
  insert(begin(), value);
}

template <typename T>
void s21::list<T>::pop_front() {
  if (this->head) {
    Node *delNode = this->head;

    if (this->head == this->tail) {
      this->head = this->tail = nullptr;
    } else {
      this->head = this->head->next;
      this->head->prev = nullptr;
    }

    delete delNode;  // GCOVR_EXCL_LINE
    this->listSize--;
  }
}

template <typename T>
void s21::list<T>::merge(list &other) {
  Node *a = this->head;
  Node *b = other.head;
  Node *mergedHead = nullptr;
  Node *mergedTail = nullptr;

  while (a && b && a != TempTail && b != other.TempTail) {
    if (a->value <= b->value) {
      if (!mergedHead) {
        mergedHead = mergedTail = a;
      } else {
        mergedTail->next = a;
        a->prev = mergedTail;
        mergedTail = a;
      }
      a = a->next;
    } else {
      if (!mergedHead) {
        mergedHead = mergedTail = b;
      } else {
        mergedTail->next = b;
        b->prev = mergedTail;
        mergedTail = b;
      }
      b = b->next;
    }
  }
  while (a && a != TempTail) {
    if (!mergedHead) {
      mergedHead = mergedTail = a;
    } else {
      mergedTail->next = a;
      a->prev = mergedTail;
      mergedTail = a;
    }
    a = a->next;
  }

  while (b && b != other.TempTail) {
    if (!mergedHead) {
      mergedHead = mergedTail = b;
    } else {
      mergedTail->next = b;
      b->prev = mergedTail;
      mergedTail = b;
    }
    b = b->next;
  }

  this->head = mergedHead;
  this->tail = mergedTail;
  this->listSize += other.listSize;

  if (this->tail) {
    set_temp_tail();
  } else {
    this->TempTail->prev = nullptr;
  }
  other.head = nullptr;
  other.tail = nullptr;
  other.listSize = 0;
}

template <typename T>
void s21::list<T>::reverse() {
  if (!this->head || !this->head->next)
    throw std::out_of_range("Список пуст");  // GCOVR_EXCL_LINE

  Node *current = this->head;
  Node *temp = nullptr;

  while (current != nullptr && current != TempTail) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  std::swap(this->head, this->tail);

  if (this->tail) {
    set_temp_tail();
  } else {
    TempTail->prev = nullptr;
  }
}

template <typename T>
void s21::list<T>::unique() {
  if (!this->head) throw std::out_of_range("Список пуст");  // GCOVR_EXCL_LINE

  Node *current = this->head;

  while (current && current->next) {
    if (current->value == current->next->value) {
      Node *duplicate = current->next;

      current->next = duplicate->next;

      if (duplicate->next)
        duplicate->next->prev = current;
      else
        this->tail = current;

      delete duplicate;  // GCOVR_EXCL_LINE
      this->listSize--;
    } else {
      current = current->next;
    }
  }
  set_temp_tail();
}

// template <typename T>
// typename s21::list<T>::Node *s21::list<T>::merge(Node *a, Node *b)
// {
//     if (!a)
//         return b;
//     if (!b)
//         return a;

//     if (a->value <= b->value)
//     {
//         a->next = merge(a->next, b);
//         a->next->prev = a;
//         a->prev = nullptr;
//         return a;
//     }
//     else
//     {
//         b->next = merge(a, b->next);
//         b->next->prev = b;
//         b->prev = nullptr;
//         return b;
//     }
// }

// template <typename T>
// typename s21::list<T>::Node *s21::list<T>::merge_sort(Node *head)
// {
//     if (!head || !head->next)
//         return head;

//     Node *second = split(head);

//     head = merge_sort(head);
//     second = merge_sort(second);

//     return merge(head, second);
// }

template <typename T>
void list<T>::splice(typename list<T>::const_iterator pos,
                     typename s21::list<T> &other) {
  Node *before_pos = (pos.get_node())->prev;
  Node *after_pos = (pos.get_node())->next;
  if (pos != end()) {
    before_pos->next = other.head;
    other.head->prev = before_pos;
    other.tail->next = pos.get_node();
    after_pos->prev = other.tail;
  } else {
    tail->next = other.head;
    other.head->prev = tail;
    this->tail = other.tail;
  }
  other.head = nullptr;
  this->listSize += other.listSize;

  set_temp_tail();
  TempTail->next = nullptr;
}

// template <typename T>
// typename s21::list<T>::Node *s21::list<T>::split(Node *head)
// {
//     Node *slow = head;
//     Node *fast = head;

//     while (fast && fast->next && fast->next->next)
//     {
//         slow = slow->next;
//         fast = fast->next->next;
//     }

//     Node *secondHalf = slow->next;
//     slow->next = nullptr;
//     return secondHalf;
// }

// template <typename T>
// void s21::list<T>::sort()
// {
//     if (!this->head || !this->head->next)
//         return;
//     tail->next = nullptr;
//     this->head = merge_sort(this->head);
//     Node *current = this->head;
//     while (current && current->next)
//         current = current->next;
//     this->tail = current;
//     TempTail->prev = tail;
//     tail->next = TempTail;
// }

template <typename T>
void list<T>::swap(list &other) {
  std::swap(this->listSize, other.listSize);
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->TempTail, other.TempTail);
}

template <typename T>
void list<T>::clear() {
  Node *current = head;
  while (current != nullptr && current->next != nullptr) {
    Node *next = current->next;
    delete current;  // GCOVR_EXCL_LINE
    current = next;
  }
  head = nullptr;
  tail = nullptr;
  listSize = 0;
}

template <typename T>
void list<T>::pop_back() {
  if (!tail)
    throw std::out_of_range("pop_back(): empty list");  // GCOVR_EXCL_LINE

  Node *to_delete = tail;

  if (head == tail) {
    head = tail = nullptr;
  } else {
    tail = tail->prev;
  }

  delete to_delete;  // GCOVR_EXCL_LINE
  listSize--;
  if (tail) set_temp_tail();
}

template <typename T>
void list<T>::push_back(const T &value) {
  Node *newNode = new Node(value);  // GCOVR_EXCL_LINE
  if (!tail) {
    head = tail = newNode;
  } else {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
  }
  set_temp_tail();
  listSize++;
}

// template <typename T>
// void list<T>::output()
// {
//     Node *now = nullptr;
//     for (int i = 0; i < listSize; i++)
//     {
//         if (now == nullptr)
//         {
//             std::cout << head->value << ' ';
//             now = head->next;
//         }
//         else
//         {
//             std::cout << now->value << ' ';
//             now = now->next;
//         }
//     }
//     std::cout << '\n';
// }

template <typename T>
template <typename... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(const_iterator pos,
                                                          Args &&...args) {
  return (insert(pos, std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  (push_front(std::forward<Args>(args)), ...);
}
}  // namespace s21
