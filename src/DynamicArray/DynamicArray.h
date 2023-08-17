#ifndef CUSTOM_CONTAINER_DYNAMIC_ARRAY_H_
#define CUSTOM_CONTAINER_DYNAMIC_ARRAY_H_

#include <assert.h>
#include <tuple>

template <typename T>
class DynamicArray {
public:
  /*
    ValueHandle is returned from EmplaceBack() which returns a reference to an element in the array and 
    the current capacity. If you store a reference to an element using EmplaceBack() then it will be
    invalidated when the array has to resize itself to fit more elements. Check the handle's size against
    the current capacity of the container if you are unsure the container has resized itself by the time
    you want to use the handle's reference.
  */
  using ValueHandle = std::tuple<T&, size_t>;
public:
  DynamicArray() {
    Resize(2);
  };

  DynamicArray(const size_t& capacity) {
    Resize(capacity);
  }

  ~DynamicArray() {
    Clear();
    ::operator delete(data_, capacity_ * sizeof(T));
    data_ = nullptr;
    capacity_ = 0;
  }

  const T& operator[](const size_t& index) const {
    assert(index < size_ && "Index out of range!");
    return data_[index];
  }

  T& operator[](const size_t& index) {
    assert(index < size_ && "Index out of range!");
    return data_[index];
  }

  void PopBack() {
    assert(size_ > 0 && "Cannot pop back empty array!");
    data_[--size_].~T();
  }

  void PushBack(const T& value) {
    if (size_ >= capacity_) {
      Resize(capacity_ + capacity_ / 2);
    }
     
    new(&data_[size_++]) T(value);
  }

  void PushBack(T&& value) {
    if (size_ >= capacity_) {
      Resize(capacity_ + capacity_ / 2);
    }

    new (&data_[size_++]) T(std::move(value));
  }

  template <typename... Args>
  ValueHandle EmplaceBack(Args&& ...args) {
    if (size_ >= capacity_) {
      Resize(capacity_ + capacity_ / 2);
    }

    T& new_value = *(new (&data_[size_++]) T(std::forward<T>(args...)));
    return { new_value, GetCapacity() };
  }

  const bool IsValueHandleValid(const ValueHandle& handle) const {
    return std::get<size_t>(handle) == GetCapacity();
  } 

  const size_t& GetSize() const {
    return size_;
  }

  const size_t& GetCapacity() const {
    return capacity_;
  }

  void Clear(void) {
    for (int i = 0; i < size_; ++i) {
      data_[i].~T();
    }

    size_ = 0;
  }

  void Resize(const size_t& capacity) {
    if (capacity < size_) {
      size_ = capacity;
    }

    T* new_data = static_cast<T*>(::operator new(capacity * sizeof(T)));

    for (int i = 0; i < size_; ++i) {
      new (&new_data[i]) T(std::move(data_[i]));
    }

    for (int i = 0; i < size_; ++i) {
      data_[i].~T();
    }

    ::operator delete(data_, capacity_ * sizeof(T));

    data_ = new_data;

    capacity_ = capacity;
  }
private:
  size_t capacity_ = 0;
  size_t size_ = 0;
  T* data_ = nullptr;
};


#endif