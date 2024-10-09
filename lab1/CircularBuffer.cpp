#include "CircularBuffer.h"
#include <errno.h>
#include <algorithm>
#include <iostream>

CircularBuffer::CircularBuffer() : capacity_(default_size), head_(0), tail_(0) {
  buffer_ = new value_type[default_size];
  std::fill(buffer_, buffer_ + capacity_, '\0');
}

CircularBuffer::CircularBuffer(int capacity)
    : capacity_(capacity), head_(0), tail_(0) {
  buffer_ = new value_type[capacity];
  std::fill(buffer_, buffer_ + capacity_, '\0');
}

CircularBuffer::CircularBuffer(int capacity, const value_type& elem)
    : capacity_(capacity), head_(0), tail_(0) {
  buffer_ = new value_type[capacity];
  std::fill(buffer_, buffer_ + capacity_, elem);
}

CircularBuffer::CircularBuffer(const CircularBuffer& cb)
    : capacity_(cb.capacity_), head_(cb.head_), tail_(cb.tail_) {
  buffer_ = new value_type[cb.capacity_];
  std::copy(cb.buffer_, cb.buffer_ + cb.capacity_, buffer_);
}

CircularBuffer::~CircularBuffer() {
  delete[] buffer_;
}

value_type& CircularBuffer::operator[](int i) {
  return buffer_[(i + head_) % capacity_];
};

const value_type& CircularBuffer::operator[](int i) const {
  return buffer_[(i + head_) % capacity_];
};

value_type& CircularBuffer::at(int i) {
  if (i < 0 || i >= size()) {
    throw std::invalid_argument("Error exit abroad");

  } else {
    return buffer_[(i + head_) % capacity_];
  }
}

const value_type& CircularBuffer::at(int i) const {
  if (i < 0 || i >= size()) {
    throw std::invalid_argument("Error exit abroad");
  } else {
    return buffer_[(i + head_) % capacity_];
  }
}

value_type& CircularBuffer::front() {
  return buffer_[head_];
}

value_type& CircularBuffer::back() {
  if (empty()) {
    return buffer_[head_];
  } else {
    return buffer_[(tail_ - 1 + capacity_) % capacity_];
  }
};

value_type& CircularBuffer::front() const {
  return buffer_[head_];
}

value_type& CircularBuffer::back() const {
  if (empty()) {
    throw std::out_of_range("Error exit abroad");
  } else {
    return buffer_[(tail_ - 1 + capacity_) % capacity_];
  }
};

int CircularBuffer::size() const {
  if (buffer_ == nullptr) {
    return 0;
  }
  if (((tail_ - head_ + capacity_) % capacity_) == 0) {
    if (buffer_[head_] == '\0')
      return 0;
    else
      return capacity_;
  } else
    return ((tail_ - head_ + capacity_) % capacity_);
}

bool CircularBuffer::is_linearized() const {
  return head_ == 0;
}

value_type* CircularBuffer::linearize() {
  if (is_linearized()) {
    return buffer_;
  } else {
    value_type* linearize_buffer = new value_type[capacity_];
    for (int i = 0; i < size(); i++) {
      linearize_buffer[i] = buffer_[(head_ + i) % capacity_];
    }
    head_ = 0;
    tail_ = size();
    delete[] buffer_;
    buffer_ = linearize_buffer;
    return buffer_;
  }
};

void CircularBuffer::rotate(int new_begin) {
  if (new_begin != head_ && (new_begin > 0 || new_begin < size())) {
    value_type* rotate_buffer = new value_type[capacity_];
    for (int i = 0; i < size(); i++) {
      rotate_buffer[i] = buffer_[(new_begin + i) % capacity_];
    }
    delete[] buffer_;
    buffer_ = rotate_buffer;
    head_ = 0;
    tail_ = size();
  }
}

bool CircularBuffer::empty() const {
  return (size() == 0 || buffer_ == nullptr);
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
    delete[] buffer_;
    buffer_ = nullptr;
    capacity_ = 0;
    head_ = 0;
    tail_ = 0;
    return;
  } else {
    value_type* new_buffer = new value_type[new_capacity];
    for (int i = 0; i < size(); i++) {
      new_buffer[i] = buffer_[(head_ + i) % capacity_];
    }
    tail_ = size() < new_capacity ? size() : new_capacity;
    delete[] buffer_;
    head_ = 0;
    buffer_ = new_buffer;
    capacity_ = new_capacity;
  }
};

void CircularBuffer::resize(int new_capacity, const value_type& item) {
  if (new_capacity < capacity_) {
    set_capacity(new_capacity);
  } else {
    value_type* new_buffer = new value_type[new_capacity];
    for (int i = 0; i < size(); i++) {
      new_buffer[i] = buffer_[(head_ + i) % capacity_];
    }
    for (int i = size(); i < new_capacity; i++) {
      new_buffer[i] = item;
    }
    head_ = 0;
    delete[] buffer_;
    buffer_ = new_buffer;
    capacity_ = new_capacity;
    tail_ = size();
  }
};

CircularBuffer& CircularBuffer::operator=(const CircularBuffer& cb) {
  if (&cb != this) {
    delete[] buffer_;
    capacity_ = cb.capacity_;
    head_ = cb.head_;
    tail_ = cb.tail_;
    if (capacity_ == 0) {
      buffer_ = nullptr;
    } else {
      buffer_ = new value_type[capacity_];
      std::copy(cb.buffer_, cb.buffer_ + capacity_, buffer_);
    }
  }
  return *this;
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
    buffer_[(tail_ - 1 + capacity_) % capacity_] = item;
    head_ = (head_ - 1 + capacity_) % capacity_;
    tail_ = head_;
  } else {
    head_ = (head_ - 1 + capacity_) % capacity_;
    buffer_[head_] = item;
    if (full()) {
      head_ = tail_;
    }
  }
}

void CircularBuffer::pop_back() {
  if (empty()) {
    throw std::invalid_argument("Error exit abroad");
  }
  if (full()) {
    buffer_[(tail_ - 1) % capacity_] = '\0';
    tail_ = (tail_ - 1) % capacity_;
  } else {
    tail_ = (tail_ - 1 + capacity_) % capacity_;
    buffer_[tail_] = '\0';
  }
};

void CircularBuffer::pop_front() {
  if (empty()) {
    throw std::invalid_argument("Error exit abroad");
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
    throw std::invalid_argument("Index out of range");
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
  if (first >= 0 && first < capacity_ && last >= 0 && last <= capacity_ &&
      first <= last) {
    for (int i = first; i < last; i++) {
      buffer_[i] = '\0';
    }
    int new_haid;
    int flag{0};
    for (int i = 0; i < capacity_; i++) {
      if (buffer_[i] == '\0') {
        if (flag == 0) {
          tail_ = i;
          flag++;
        }
        flag++;
      }
    }
    head_ = (tail_ + flag - 1) % capacity_;
    flag = 0;
  } else {
    throw std::invalid_argument("index out of range");
  }
}

void CircularBuffer::clear() {
  head_ = 0;
  tail_ = 0;

  std::fill(buffer_, buffer_ + capacity_, '\0');
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