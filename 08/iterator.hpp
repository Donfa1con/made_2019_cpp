#pragma once

template<typename T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
  public:
    explicit Iterator(T* ptr) : ptr(ptr) {}
    
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }
    
    Iterator& operator++() {
        ++ptr;
        return *this;
    }
    Iterator& operator--() {
        --ptr;
        return *this;
    }
    Iterator operator++(int) {
        Iterator tmp(*this);
        ++ptr;
        return tmp;
    }
    Iterator operator--(int) {
        Iterator tmp(*this);
        --ptr;
        return tmp;
    }
    Iterator& operator+=(int value) {
        ptr += value;
        return *this;
    }
    Iterator& operator-=(int value) {
        ptr -= value;
        return *this;
    }
    Iterator operator+(int value) const {
        return Iterator(ptr + value);
    }
    Iterator operator-(int value) const {
        return Iterator(ptr - value);
    }
    
    bool operator>(const Iterator& other) const {
        return ptr > other.ptr;
    }
    bool operator<(const Iterator& other) const {
        return ptr < other.ptr;
    }
    bool operator==(const Iterator& other) const {
        return ptr == other.ptr;
    }
    bool operator!=(const Iterator& other) const {
        return ptr != other.ptr;
    }
    bool operator>=(const Iterator& other) const {
        return ptr >= other.ptr;
    }
    bool operator<=(const Iterator& other) const {
        return ptr <= other.ptr;
    }
  
  private:
    T* ptr;
};
