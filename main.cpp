#include <iostream>

template< class T >
struct BiList {
  T val;
  BiList<T>* next;
  BiList<T>* prev;
};

template< class T >
BiList<T>* push_front(BiList<T>* head, const T& value) {
  BiList<T>* new_node = new BiList<T>;  // T::T()
  new_node->val = value;  // T& operator=(const T&)

  if (head == nullptr) {
    new_node->next = new_node;
    new_node->prev = new_node;
    return new_node;
  }

  BiList<T>* tail = head->prev;
  new_node->next = head;
  new_node->prev = tail;
  head->prev = new_node;
  tail->next = new_node;
  return new_node;
}

template< class T >
BiList<T>* insert_after(BiList<T>* node, const T& value) {
  if (node == nullptr) return nullptr;

  BiList<T>* new_node = new BiList<T>;  // T::T()
  new_node->val = value;  //  T& operator=(const T&)
  BiList<T>* next_node = node->next;

  new_node->next = next_node;
  new_node->prev = node;
  node->next = new_node;
  next_node->prev = new_node;

  return new_node;
}

template< class T >
BiList<T>* insert_before(BiList<T>* node, const T& value) {
  if (node == nullptr) return nullptr;

  BiList<T>* new_node = new BiList<T>;  // T::T()
  new_node->val = value;  // T& operator=(const T&)
  BiList<T>* prev_node = node->prev;

  new_node->next = node;
  new_node->prev = prev_node;
  prev_node->next = new_node;
  node->prev = new_node;

  return new_node;
}

template< class T >
BiList<T>* pop_front(BiList<T>* head) noexcept {
  if (head == nullptr) return nullptr;

  if (head->next == head) {
    delete head;  // ~T()
    return nullptr;
  }

  BiList<T>* tail = head->prev;
  BiList<T>* new_head = head->next;

  tail->next = new_head;
  new_head->prev = tail;

  delete head;  // ~T()
  return new_head;
}

template< class T >
BiList<T>* erase(BiList<T>* node) noexcept {
  if (node == nullptr) return nullptr;

  if (node->next == node) {
    delete node;  // ~T()
    return nullptr;
  }

  BiList<T>* prev_node = node->prev;
  BiList<T>* next_node = node->next;

  prev_node->next = next_node;
  next_node->prev = prev_node;

  delete node;  // ~T()
  return next_node;
}

template< class T >
BiList<T>* clear(BiList<T>* head) noexcept {
  if (head == nullptr) return nullptr;

  BiList<T>* current = head;
  BiList<T>* next = nullptr;

  while (current->next != head) {
    next = current->next;
    delete current;  // ~T()
    current = next;
  }

  delete current;  // ~T()
  return nullptr;
}

template< class T >
BiList<T>* array_to_list(const T arr[], size_t size) {
  if (size == 0) return nullptr;

  BiList<T>* head = nullptr;
  for (size_t i = 0; i < size; ++i) {
    if (head == nullptr) {
      head = push_front(head, arr[i]);
    } else {
      insert_after(head->prev, arr[i]);
    }
  }
  return head;
}

void print_list(BiList<int>* head) {
  if (head == nullptr) return;

  BiList<int>* current = head;

  while (current->next != head) {
    std::cout << current->val << " ";
    current = current->next;
  }

  std::cout << current->val << " ";
  std::cout << '\n';
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};
  size_t size = 5;

  BiList<int>* my_list = array_to_list(arr, size);
  print_list(my_list);
  my_list = clear(my_list);

  return 0;
}
