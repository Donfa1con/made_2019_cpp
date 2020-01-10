#pragma once

#include "iterator.hpp"


template<class T, class Allocator = std::allocator<T>>
class Vector {
  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = Iterator<value_type>;
    using reverse_iterator = std::reverse_iterator<iterator>;

    explicit Vector();
    explicit Vector(size_type count);
    Vector(size_type count, const value_type& default_value);
    Vector(std::initializer_list<value_type> init);
    Vector(const Vector& copied);
    Vector(Vector&& moved);
    Vector& operator=(const Vector& copied);
    Vector& operator=(Vector&& moved);
    ~Vector();
    
    void clear() noexcept {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destroy(&data_[i]);
        }
        size_ = 0;
    }
    
    void resize(size_type new_size, const value_type& default_value = value_type()) {
        if (new_size < size_) {
            for (size_t i = new_size; i < size_; ++i) {
                alloc_.destroy(&data_[i]);
            }
            size_ = new_size;
            check_capacity();
        } else if (new_size > size_){
            reserve(new_size);
            init_vector(data_ + size_, new_size - size_, default_value);
            size_ = new_size;
        }
    }
    
   void reserve(size_type count) {
       if (count > capacity_) {
           reallocate(count);
       }
   }
    
    void push_back(value_type&& value) {
        check_capacity();
        alloc_.construct(&data_[size_++], std::move(value));
    }
    
    void push_back(const value_type& value) {
        check_capacity();
        alloc_.construct(&data_[size_++], value);
    }
    
    void pop_back() {
        if (size_) {
            alloc_.destroy(&data_[--size_]);
            check_capacity();
        }
    }
    
    iterator begin() noexcept {
        return iterator(data_);
    }
    reverse_iterator rbegin() noexcept {
        return reverse_iterator(begin());
    }

    iterator end() noexcept {
        return iterator(data_ + size_);
    }
    reverse_iterator rend() noexcept {
        return reverse_iterator(end());
    }
    
    size_type capacity() const noexcept {
        return capacity_;
    }
    
    size_type size() const noexcept {
        return size_;
    }
    
    bool empty() const noexcept {
        return !size_;
    }
    
    reference operator[](size_type pos) {
        return data_[pos];
    }
    
    const_reference operator[](size_type pos) const {
        return data_[pos];
    }
  
  private:
    void reallocate(size_t new_capacity);
    void check_capacity();
    void init_vector(value_type* start, size_type count,
                     const value_type& default_value = value_type());
    void copy(value_type* from, value_type* to, size_type size);
    
    allocator_type alloc_;
    size_type capacity_;
    size_type size_;
    value_type* data_;
    static constexpr size_type capacity_mult = 2;
};

template<class T, class Allocator>
Vector<T, Allocator>::~Vector() {
    clear();
    alloc_.deallocate(data_, capacity_);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(): alloc_(allocator_type()), capacity_(0), size_(0), data_(nullptr) {}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count)
: alloc_(allocator_type()), capacity_(count), size_(count), data_(alloc_.allocate(count)) {
    init_vector(data_, count);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count, const value_type& default_value)
: alloc_(allocator_type()), capacity_(count), size_(count), data_(alloc_.allocate(count)) {
    init_vector(data_, count, default_value);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> init)
: alloc_(allocator_type()), capacity_(init.size())
, size_(capacity_), data_(alloc_.allocate(capacity_)) {
    size_t i = 0;
    auto current = init.begin();
    const auto end = init.end();
    while (current != end) {
        alloc_.construct(&data_[i], *current++);
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& copied)
: alloc_(allocator_type()), capacity_(copied.capacity_)
, size_(copied.size_), data_(alloc_.allocate(capacity_)) {
    copy(copied.data_, data_, size_);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& moved)
: alloc_(allocator_type()), capacity_(moved.capacity_)
, size_(moved.size_), data_(alloc_.allocate(capacity_)) {
    moved.capacity_ = 0;
    moved.size_ = 0;
    moved.data_ = nullptr;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& copied) {
    if (this == &copied) {
        return *this;
    }
    value_type* ptr = alloc_.allocate(copied.capacity_);
    clear();
    alloc_.deallocate(data_, capacity_);
    data_ = ptr;
    size_ = copied.size_;
    capacity_ = copied.capacity_;
    copy(copied.data_, data_, size_);
    return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& moved) {
    if (this == &moved) {
        return *this;
    }
    clear();
    alloc_.deallocate(data_, capacity_);
    data_ = moved.data_;
    size_ = moved.size_;
    capacity_ = moved.capacity_;
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.capacity_ = 0;
    return *this;
}

template<class T, class Allocator>
void Vector<T, Allocator>::init_vector(value_type* start, size_type count, const value_type& default_value) {
    for (size_t i = 0; i < count; ++i) {
        alloc_.construct(&start[i], default_value);
    }
}

template<class T, class Allocator>
void Vector<T, Allocator>::reallocate(size_t new_capacity) {
    assert(new_capacity >= size_);
    value_type* new_data = alloc_.allocate(new_capacity);
    copy(data_, new_data, size_);
    size_type old_size = size_;
    clear();
    alloc_.deallocate(data_, capacity_);
    data_ = new_data;
    size_ = old_size;
    capacity_ = new_capacity;
}

template<class T, class Allocator>
void Vector<T, Allocator>::check_capacity() {
    if (size_ == capacity_) {
        reallocate(capacity_ ? capacity_ * capacity_mult : 1);
    } else if (size_ < capacity_ / 4) {
        reallocate(capacity_ / capacity_mult);
    }
}

template<class T, class Allocator>
void Vector<T, Allocator>::copy(value_type* from, value_type* to, size_type size) {
    for (size_t i = 0; i < size; i++) {
        alloc_.construct(&to[i], from[i]);
    }
}
