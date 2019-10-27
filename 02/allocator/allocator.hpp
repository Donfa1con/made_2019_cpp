#pragma once

#include <iostream>

class LinearAllocator {
  public:
    LinearAllocator(size_t max_size): max_size(max_size), offset(0), buf(new char[max_size]) {}
    LinearAllocator(const LinearAllocator&) = delete;
    LinearAllocator(LinearAllocator&&) = delete;
    LinearAllocator& operator= (const LinearAllocator&) = delete;
    LinearAllocator& operator= (LinearAllocator&&) = delete;
    ~LinearAllocator();

    char* alloc(size_t size);
    void reset();
    
  private:
    size_t max_size;
    size_t offset;
    char* buf;
};
