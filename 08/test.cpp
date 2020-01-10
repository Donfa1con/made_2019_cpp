#include <cassert>
#include <iostream>

#include "vector.hpp"

void test_vector_int() {
    Vector<int> vec = {1, 2, 3, 4};
    assert(vec.size() == 4);
    assert(vec.capacity() == 4);
    
    vec.push_back(5);
    assert(vec.size() == 5);
    assert(vec.capacity() == 8);
    
    vec.clear();
    assert(vec.size() == 0);
    assert(vec.capacity() == 8);
    
    vec.push_back(1);
    assert(vec.size() == 1);
    assert(vec.capacity() == 4);
    
    vec.pop_back();
    assert(vec.size() == 0);
    assert(vec.capacity() == 2);
    
    vec.resize(20);
    assert(vec.size() == 20);
    assert(vec.capacity() == 20);
    
    vec.reserve(10);
    assert(vec.size() == 20);
    assert(vec.capacity() == 20);
    
    vec.reserve(100);
    assert(!vec.empty());
    assert(vec.size() == 20);
    assert(vec.capacity() == 100);
    
    vec.resize(0);
    vec.reserve(0);
    assert(vec.empty());
    assert(vec.size() == 0);
    assert(vec.capacity() == 50);
        
    for (int i = 0; i < 100; ++i) { vec.push_back(i); }
    assert(vec.size() == 100);
    assert(vec.capacity() == 192);
    
    for (int i = 0; i < 70; ++i) { vec.pop_back(); }
    assert(vec.size() == 30);
    assert(vec.capacity() == 96);
    
    int i = 0;
    for (auto val: vec) {
        assert(val == i++);
    }
    assert(i == 30);
}

void test_vector_string() {
    Vector<std::string> vec;
    vec.push_back(std::string());
    assert(vec[0] == "");
    
    Vector<std::string> vec2(10, "test");
    assert(vec2.size() == 10);
    assert(vec2.capacity() == 10);
    assert(vec2[5] == "test");
    
    Vector<std::string> vec3(10);
    assert(vec3.size() == 10);
    assert(vec3.capacity() == 10);
    assert(vec3[5] == "");
    
    assert(vec3.begin() + 10 == vec3.end());
    assert(vec3.begin() == vec3.end() - 10);
    
    vec3[5] = "T";
    assert(*(vec3.rbegin() - 5) == *(vec3.rend() + 5));
    assert(*(vec3.begin() + 5) == "T");
    assert(*(vec3.rbegin() - 6) == "T");
}

void test_vector_iterator() {
    Vector<int> vec(100);
    for (int i = 0; i < 100; ++i) {
        vec[i] = i;
    }
    auto begin_it = vec.begin();
    auto end_it = vec.end();
    assert(begin_it < end_it);
    begin_it += 10;
    end_it -= 90;
    assert(*begin_it = 10);
    assert(*end_it == 10);
    assert(begin_it == end_it);
    assert(begin_it-- == end_it);
    assert(--begin_it < end_it);
}

int main() {
    test_vector_int();
    test_vector_string();
    test_vector_iterator();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
