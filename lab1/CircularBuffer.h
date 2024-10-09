/**
 * @file CircularBuffer.h
 * @brief Defines the CircularBuffer class for managing a circular buffer.
 * 
 * This file contains the definition of the CircularBuffer class, which provides
 * methods to interact with a circular buffer.
 * It supports insertion, deletion, resizing, and other buffer management operations.
 */

#include <errno.h>
#include <algorithm>
#include <iostream>

/** @brief Default size for the circular buffer. */
const size_t default_size = 4;

/** @brief Type used to store elements in the buffer. */
typedef char value_type;

/**
 * @class CircularBuffer
 * @brief A class to represent a circular buffer.
 *
 * insertion and deletion of elements in a circular manner.
 */
class CircularBuffer {
  value_type* buffer_; /**< Pointer to the buffer array */
  int capacity_;       /**< Capacity of the buffer */
  int head_;           /**< Index of the head element */
  int tail_;           /**< Index of the tail element */

 public:
  /**
   * @brief Default constructor, initializes buffer with default size.
   */
  CircularBuffer();

  /**
   * @brief Constructor with specified capacity.
   * @param capacity The max size of the buffer.
   */
  explicit CircularBuffer(int capacity);

  /**
   * @brief Constructor with specified capacity and default element.
   * @param capacity The max size of the buffer.
   * @param elem The element to fill the buffer with.
   */
  CircularBuffer(int capacity, const value_type& elem);

  /**
   * @brief Copy constructor.
   * @param cb The CircularBuffer object to copy from.
   */
  CircularBuffer(const CircularBuffer& cb);

  /**
   * @brief Destructor, deallocates the buffer.
   */
  ~CircularBuffer();

  /**
   * @brief Correct index access depending on the header.
   * @param i Index of the element.
   * @return Reference to the element at index i.
   */
  value_type& operator[](int i);

  const value_type& operator[](int i) const;

  /**
   * @brief Correct index access depending on the header. Addin checking correct
   * @param i Index of the element.
   * @return Reference to the element at index i.
   * @throws std::invalid_argument if the index is out of range.
   */
  value_type& at(int i);

  const value_type& at(int i) const;

  /**
   * @brief Get reference to the front element.
   * @return Reference to the front element.
   */
  value_type& front();

  /**
   * @brief Get reference to the back element.
   * @return Reference to the back element.
   */
  value_type& back();

  /**
   * @brief Get reference to the front element (const version).
   * @return Const reference to the front element.
   */
  value_type& front() const;

  /**
   * @brief Get reference to the back element (const version).
   * @return Const reference to the back element.
   */
  value_type& back() const;

  /**
   * @brief Get the number of elements in the buffer.
   * @return The size of the buffer.
   */
  int size() const;

  /**
   * @brief Check if the buffer is linearized (head at index 0).
   * @return True if the buffer is linearized, false otherwise.
   */
  bool is_linearized() const;

  /**
   * @brief Linearize the buffer. First element has null index.
   * @return Pointer to the linearized buffer.
   */
  value_type* linearize();

  /**
   * @brief Rotate the buffer to start at a new beginning.
   * @param new_begin The new index to start from.
   */
  void rotate(int new_begin);

  /**
   * @brief Check if the buffer is empty.
   * @return True if the buffer is empty, false otherwise.
   */
  bool empty() const;

  /**
   * @brief Check if the buffer is full.
   * @return True if the buffer is full, false otherwise.
   */
  bool full() const;

  /**
   * @brief Get the amount of free space in the buffer.
   * @return The number of available positions in the buffer.
   */
  int reserve() const;

  /**
   * @brief Get the capacity of the buffer.
   * @return The total capacity of the buffer.
   */
  int capacity() const;

  /**
   * @brief Set a new capacity for the buffer.
   * @param new_capacity The new capacity for the buffer.
   */
  void set_capacity(int new_capacity);

  /**
   * @brief Resize the buffer and optionally fill with a specified element.
   * @param new_capacity The new size for the buffer.
   * @param item The element to fill the buffer with (default is value_type()).
   */
  void resize(int new_capacity, const value_type& item = value_type());

  /**
   * @brief Overloaded assignment operator.
   * @param cb The CircularBuffer object to assign from.
   * @return Reference to the current CircularBuffer.
   */
  CircularBuffer& operator=(const CircularBuffer& cb);

  /**
   * @brief Swap the contents of two buffers.
   * @param cb The buffer to swap with.
   */
  void swap(CircularBuffer& cb);

  /**
   * @brief Add an element to the back of the buffer.
   * @param item The element to add (default is value_type()).
   */
  void push_back(const value_type& item = value_type());

  /**
   * @brief Add an element to the front of the buffer.
   * @param item The element to add (default is value_type()).
   */
  void push_front(const value_type& item = value_type());

  /**
   * @brief Remove the element from the back of the buffer.
   * @throws std::invalid_argument if the buffer is empty.
   */
  void pop_back();

  /**
   * @brief Remove the element from the front of the buffer.
   * @throws std::invalid_argument if the buffer is empty.
   */
  void pop_front();

  /**
   * @brief Insert an element at a specific position.
   * @param pos The position to insert the element at.
   * @param item The element to insert (default is value_type()).
   * @throws std::invalid_argument if the index is out of range.
   */
  void insert(int pos, const value_type& item = value_type());

  /**
   * @brief Clear the buffer.
   *
   * Resets the buffer to an empty state.
   */
  void clear();

  /**
   * @brief Erase a range of elements from the buffer.
   * @param first The starting index of the range.
   * @param last The ending index of the range.
   * @throws std::invalid_argument if indices are out of range.
   */
  void erase(int first, int last);
};

/**
 * @brief Equality comparison operator for CircularBuffer.
 * @param a First buffer.
 * @param b Second buffer.
 * @return True if both buffers are equal, false otherwise.
 */
bool operator==(const CircularBuffer& a, const CircularBuffer& b);

/**
 * @brief Inequality comparison operator for CircularBuffer.
 * @param a First buffer.
 * @param b Second buffer.
 * @return True if both buffers are not equal, false otherwise.
 */
bool operator!=(const CircularBuffer& a, const CircularBuffer& b);
