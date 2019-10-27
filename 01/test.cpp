#include <iostream>
#include <cassert>

#include "calculator/calculator.hpp"

int main() {
    Calculator calc;

    assert(calc.parse_expr("2 + 3 * 4 - -2") == 16);
    assert(calc.is_success_parse());

    assert(calc.parse_expr("2 + 3 * 4 - -2 / 2") == 15);
    assert(calc.is_success_parse());

    assert(calc.parse_expr("2 / 2 / 2") == 0);
    assert(calc.is_success_parse());

    assert(calc.parse_expr("-1") == -1);
    assert(calc.is_success_parse());

    assert(calc.parse_expr("-5 - -4") == -1);
    assert(calc.is_success_parse());


    calc.parse_expr("--1");
    assert(!calc.is_success_parse());
    
    calc.parse_expr("-1.5 + 2");
    assert(!calc.is_success_parse());
    
    calc.parse_expr("2 + 2 0");
    assert(!calc.is_success_parse());
    
    calc.parse_expr("-5 - --4");
    assert(!calc.is_success_parse());
    
    calc.parse_expr("2 / 0");
    assert(!calc.is_success_parse());

    std::cout << "Tests passed!" << std::endl;
    return 0;
}
