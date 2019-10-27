#include <iostream>

#include "allocator.hpp"

LinearAllocator::~LinearAllocator() {
    delete[] buf;
}

char* LinearAllocator::alloc(size_t size) {
    if (offset + size > max_size || size > max_size) {
        return nullptr;
    }
    size_t old_offset = offset;
    offset += size;
    return buf + old_offset;
}

void LinearAllocator::reset() {
    offset = 0;
}
