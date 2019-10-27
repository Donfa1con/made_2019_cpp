#include <iostream>

#include "calculator/calculator.hpp"

int main(int argc, const char * argv[]) {
    if (argc != 2) {
        std::cerr << "error: Invalid number of arguments" << std::endl;
        return 1;
    }
    
    Calculator calc;
    int result = calc.parse_expr(argv[1]);
    
    if (calc.is_success_parse()) {
        std::cout << result << std::endl;
    } else {
        std::cerr << "error: Invalid expression" << std::endl;
        return 1;
    }
    return 0;
}
