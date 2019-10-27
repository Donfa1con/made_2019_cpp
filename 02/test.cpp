#include <cassert>
#include <iostream>

#include "allocator/allocator.hpp"

int main(int argc, const char * argv[]) {
    LinearAllocator allocator(300);
    assert(allocator.alloc(300) != nullptr);
    assert(allocator.alloc(1) == nullptr);
    allocator.reset();
    
    assert(allocator.alloc(0) != nullptr);
    for (int i = 0; i < 300; ++i) {
        assert(allocator.alloc(1) != nullptr);
    }
    assert(allocator.alloc(1) == nullptr);
    assert(allocator.alloc(-1) == nullptr);
    
    LinearAllocator zero_allocator(0);
    assert(zero_allocator.alloc(1) == nullptr);
    
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
