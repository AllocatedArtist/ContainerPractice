#ifndef CUSTOM_CONTAINER_ARRAY_H_
#define CUSTOM_CONTAINER_ARRAY_H_

#include <assert.h>
#include <initializer_list>

template <typename Array>
class ArrayIterator {
public:
  using ValueType = typename Array::ValueType;
  enum class Type {
    Begin,
    Middle,
    End,
  };
public: 
  ArrayIterator(ValueType* iterator, const Type& type = Type::Middle) : iterator_(iterator), type_(type) {}

  ArrayIterator& operator++() {
    assert(type_ != Type::End && "Cannot advance last element!");
    iterator_++;
    return *this;
  }

  ArrayIterator operator++(int) {
    assert(type_ != Type::End && "Cannot advance last element!");
    ArrayIterator iterator_copy(iterator_);
    ++(*this);
    return iterator_copy;
  }

  ArrayIterator& operator--() {
    assert(type_ != Type::Begin && "Cannot decrement first element!");
    iterator_--;
    return *this;
  }

  ArrayIterator operator--(int) {
    assert(type_ != Type::Begin && "Cannot decrement first element!");
    ArrayIterator iterator_copy(iterator_);
    --(*this);
    return iterator_copy;
  }

  ArrayIterator operator+(size_t offset) { 
    ArrayIterator iterator_copy = *this;
    iterator_copy.iterator_ += offset;
    return iterator_copy;
  }

  void operator+=(size_t offset) { 
    iterator_ = iterator_ + offset;
  }

  ValueType& operator[](const int& index) {
    assert(index >= 0 && "Index cannot be negative!");
    return *(iterator_ + index);
  }

  ValueType* operator->() {
    return iterator_;
  }

  ValueType& operator*() {
    assert(type_ != Type::End && "Cannot dereference out of range iterator!");
    return *iterator_;
  }

  bool operator==(const ArrayIterator& other) const {
    return iterator_ == other.iterator_;
  }

  bool operator!=(const ArrayIterator& other) const {
    return !(*this == other);
  }
private:
  ValueType* iterator_;
  Type type_;
};

template <typename T, size_t N>
class Array {
public:
  using ValueType = T;
  using Iterator = ArrayIterator<Array<T, N>>;
public:
  Array() = default;

  Array(const std::initializer_list<T>& elements_list) {
    assert(elements_list.size() <= size_ && "Initializing array with too many elements!");
    if (elements_list.size() > 0) {
      for (int i = 0; i < elements_list.size(); ++i) {
        elements_[i] = *(elements_list.begin() + i);
      }
    }
  } 

  size_t GetSize() const {
    return size_;
  }

  const T& operator[](const size_t& index) const {
    assert(index < size_ && "Index out of range!"); 
    return elements_[index];
  }

  T& operator[](const size_t& index) {
    assert(index < size_ && "Index out of range!");
    return elements_[index];
  }

  Iterator begin() {
    return Iterator(&elements_[0], Iterator::Type::Begin);
  }

  Iterator end() {
    return Iterator(&elements_[size_], Iterator::Type::End);
  }
private:
  size_t size_ = N;
  T elements_[N] = {};
};



#endif