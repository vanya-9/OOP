#include "CircularBuffer.h"
#include <errno.h>
#include <algorithm>
#include <iostream>

CircularBuffer::CircularBuffer() : capacity_(default_size), head_(0), tail_(0) {
  buffer_.resize(default_size, '\0');
}

CircularBuffer::CircularBuffer(int capacity)
    : capacity_(capacity), head_(0), tail_(0) {
  buffer_.resize(capacity, '\0');
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem)
    : capacity_(capacity), head_(0), tail_(0) {
  buffer_.resize(capacity, elem);
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb)
    : capacity_(cb.capacity_),
      head_(cb.head_),
      tail_(cb.tail_),
      buffer_(cb.buffer_) {}

CircularBuffer::~CircularBuffer() {}

const int CircularBuffer::increment() const {
  return (tail_ - 1 + capacity_);
}

const int CircularBuffer::decrement() const {
  return (head_ - 1 + capacity_);
}

value_type& CircularBuffer::operator[](int i) {
  return buffer_[(i + head_) % capacity_];
};

const value_type& CircularBuffer::operator[](int i) const {
  return buffer_[(i + head_) % capacity_];
};

value_type& CircularBuffer::at(int i) {
  if (i < 0 || i >= size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  return buffer_[(i + head_) % capacity_];
}

const value_type& CircularBuffer::at(int i) const {
  if (i < 0 || i >= size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  return buffer_[(i + head_) % capacity_];
}

value_type& CircularBuffer::front() {
  return buffer_[head_];
}

value_type& CircularBuffer::back() {
  if (empty()) {
    return buffer_[head_];
  } else {
    return buffer_[increment() % capacity_];
  }
};

const value_type& CircularBuffer::front() const {
  return buffer_[head_];
}

const value_type& CircularBuffer::back() const {
  if (empty()) {
    throw std::out_of_range("Index out of bounds");
  } else {
    return buffer_[increment() % capacity_];
  }
};

int CircularBuffer::size() const {
  if (buffer_.data() == nullptr) {
    return 0;
  }

  if (buffer_.vector::empty()) {
    return 0;
  }

  if (((tail_ - head_ + capacity_) % capacity_) == 0) {
    if (buffer_[head_] == '\0')
      return 0;

    else if (buffer_[head_] != '\0') {
      return capacity_;
    }
  }
  return ((tail_ - head_ + capacity_) % capacity_);
}

bool CircularBuffer::is_linearized() const {
  return head_ == 0;
}

value_type* CircularBuffer::linearize() {
  if (is_linearized()) {
    return buffer_.data();
  }
  {
    for (int i = 0; i < size(); i++) {
      int curr_index = (head_ + i) % capacity_;
      int new_index = i;

      std::swap(buffer_[new_index], buffer_[curr_index]);
    }
  }

  head_ = 0;
  tail_ = size();
  return buffer_.data();
}

void CircularBuffer::rotate(int new_begin) {
  if (new_begin == head_ || (new_begin < 0 && new_begin > size())) {
    return;
  }
  for (int i = 0; i < size(); i++) {
    int fact_index = (head_ + i) % capacity_;
    int new_index = (new_begin + i) % capacity_;
    std::swap(buffer_[new_index], buffer_[fact_index]);
  }
  head_ = new_begin;
  tail_ = (size() + new_begin) % capacity_;
}

bool CircularBuffer::empty() const {
  return (size() == 0 || buffer_.data() == nullptr);
}

bool CircularBuffer::full() const {
  return size() == capacity_;
}

int CircularBuffer::reserve() const {
  return capacity_ - size();
}

int CircularBuffer::capacity() const {
  return capacity_;
};

void CircularBuffer::set_capacity(int new_capacity) {
  if (new_capacity <= 0) {
    buffer_.clear();
    capacity_ = 0;
    head_ = 0;
    tail_ = 0;
  } else {
    rotate(0);
    buffer_.resize(new_capacity, '\0');
    head_ = 0;
    tail_ = size() < new_capacity ? size() : new_capacity;
    capacity_ = new_capacity;
  }
};

void CircularBuffer::resize(int new_capacity, const value_type& item) {
  if (new_capacity <= 0) {
    buffer_.clear();
    capacity_ = 0;
    head_ = 0;
    tail_ = 0;
    return;
  } else {
    rotate(0);
    buffer_.resize(size());
    buffer_.resize(new_capacity, item);
    head_ = 0;
    tail_ = size() < new_capacity ? size() : new_capacity;
    capacity_ = new_capacity;
  }
};

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
  if (&cb == this) {
    return *this;
  } else {
    buffer_ = cb.buffer_;
    head_ = cb.head_;
    tail_ = cb.tail_;
    return *this;
  }
}

void CircularBuffer::swap(CircularBuffer& cb) {
  std::swap(buffer_, cb.buffer_);
  std::swap(capacity_, cb.capacity_);
  std::swap(head_, cb.head_);
  std::swap(tail_, cb.tail_);
}

void CircularBuffer::push_back(const value_type& item) {
  if (full()) {
    head_ = (head_ + 1) % capacity_;
  }

  buffer_[tail_] = item;
  tail_ = (tail_ + 1) % capacity_;
}

void CircularBuffer::push_front(const value_type& item) {
  if (full()) {
    buffer_[increment() % capacity_] = item;
    head_ = decrement() % capacity_;
    tail_ = head_;
    return;
  }
  if (full()) {
    head_ = tail_;
  }

  head_ = decrement() % capacity_;
  buffer_[head_] = item;
}

void CircularBuffer::pop_back() {
  if (empty()) {
    throw std::invalid_argument("Index out of bounds");
  }

  if (full()) {
    buffer_[(tail_ - 1) % capacity_] = '\0';
    tail_ = (tail_ - 1) % capacity_;
  } else {
    tail_ = increment() % capacity_;
    buffer_[tail_] = '\0';
  }
};

void CircularBuffer::pop_front() {
  if (empty()) {
    throw std::invalid_argument("Index out of bounds");
  }
  if (full()) {
    buffer_[tail_] = '\0';
    head_ = (head_ + 1) % capacity_;
  } else {
    buffer_[head_] = '\0';
    head_ = (head_ + 1) % capacity_;
  }
}

void CircularBuffer::insert(int pos, const value_type& item) {
  if (pos < 0 || pos > size()) {
    throw std::invalid_argument("Index out of bounds");
  }

  int insert_pos = (head_ + pos) % capacity_;

  if (!full()) {
    for (int i = size(); i > pos; --i) {
      buffer_[(head_ + i) % capacity_] = buffer_[(head_ + i - 1) % capacity_];
    }
    tail_ = (tail_ + 1) % capacity_;
  }

  buffer_[insert_pos] = item;
}

void CircularBuffer::erase(int first, int last) {
  if (first < 0 || first >= size() || last <= first || last > size()) {
    throw std::invalid_argument("Index out of bounds");
  }

  int num_to_erase = last - first;

  if (first == 0 && last == size()) {
    clear();
    return;
  }

  int real_first = (head_ + first) % capacity_;
  int real_last = (head_ + last) % capacity_;
  for (int i = 0; i < num_to_erase; i++) {
    buffer_[(first + i) % capacity_] = '\0';
  }
  int offset_ind = 0;
  for (int i = last; i < size(); i++) {
    buffer_[(real_first + offset_ind) % capacity_] =
        buffer_[(real_last + offset_ind) % capacity_];
    buffer_[(real_last + offset_ind) % capacity_] = '\0';
    offset_ind++;
  }
  offset_ind = 0;
  tail_ = (tail_ - num_to_erase + capacity_) % capacity_;
}

void CircularBuffer::clear() {
  head_ = 0;
  tail_ = 0;

  buffer_.vector::clear();
}

bool operator==(const CircularBuffer& a, const CircularBuffer& b) {
  if (a.size() != b.size())
    return false;

  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i])
      return false;
  }
  if (a.capacity() != b.capacity()) {
    return false;
  }
  return true;
}

bool operator!=(const CircularBuffer& a, const CircularBuffer& b) {
  return !(a == b);
}