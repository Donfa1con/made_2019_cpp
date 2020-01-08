#include <iostream>

#include "format/format.hpp"

struct Custom {};

std::ostream& operator<<(std::ostream& out, const Custom& obj) {
    out << "custom object";
    return out;
}

void test_one_arg() {
    auto text = format("{0}+{0} != {0}", 2);
    assert(text == "2+2 != 2");
}

void test_multiple_args() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void test_custom_object() {
    Custom obj;
    auto text = format("{0}+{0} = {0}", obj);
    assert(text == "custom object+custom object = custom object");
}

void test_format_count_more() {
    try {
        auto text = format("{0}+{0} = {1}", 1);
        assert(false);
    } catch (const std::runtime_error& e) {}
}

void test_empty_format() {
    try {
        auto text = format("{0}+{0} {}= {0}", 1);
        assert(false);
    } catch (const std::runtime_error& e) {}
}

void test_word_format() {
    try {
        auto text = format("{0ss}+{0} = {0}", 1);
        assert(false);
    } catch (const std::runtime_error& e) {}
}

void test_braces() {
    auto text = format("}{1}+{1} = }{0}", 2, "one");
    assert(text == "}one+one = }2");
    try {
        auto text = format("{0}+{0} {{0}}= {0}", 1);
        assert(false);
    } catch (const std::runtime_error& e) {}
}

int main() {
    test_one_arg();
    test_multiple_args();
    test_custom_object();
    test_format_count_more();
    test_empty_format();
    test_word_format();
    test_braces();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}


