#pragma once

#include <iostream>
#include <sstream>

class Calculator {
  public:
    Calculator(): success_parse(true), state('\0') {};
    Calculator(const Calculator&) = delete;
    Calculator(Calculator&&) = delete;
    Calculator& operator= (const Calculator&) = delete;
    Calculator& operator= (Calculator&&) = delete;
    ~Calculator() = default;

    int parse_expr(const std::string& input_expr);
    bool is_success_parse();
    
  private:
    void update_state();
    int parse_expr();
    int parse_num();
    int add_sub();
    int mul_div();
    bool is_unary_minus();

    char state;
    bool success_parse;
    std::istringstream expr;
};
