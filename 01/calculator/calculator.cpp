#include "calculator.hpp"

int Calculator::parse_num() {
    if (state != '-') {
        expr.putback(state);
    } else {
        update_state();
        if (state == '-') {
            success_parse = false;
            return 0;
        }
    }
    float number = 0;
    expr >> number;
    if (number != int(number)) {
        success_parse = false;
        return 0;
    }
    return number;
}

void Calculator::update_state() {
    do {
        expr.get(state);
    } while (expr && std::isspace(state)); // Skip space symbols
}

int Calculator::parse_expr(const std::string& input_expr) {
    expr.clear();
    expr.str(input_expr);
    return add_sub();
}

int Calculator::add_sub() {
    int left = mul_div();

    while (success_parse) {
        if (state == '+') {
            left += mul_div();
            continue;
        }
        if (state == '-') {
            left -= mul_div();
            continue;
        }
        return left;
    }
    return left;
}

int Calculator::mul_div() {
    int left = parse_expr();
    while (success_parse) {
        
        if (state == '*') {
            left *= parse_expr();
            continue;
        }
        if (state == '/') {
            int right = parse_expr();
            if (right == 0) {
                success_parse = false;
                return left;
            }
            left /= right;
            continue;
        }
        return left;
    }
    return left;
}

bool Calculator::is_unary_minus() {
    update_state();
    if (state == '-') {
        success_parse = false;
        return false;
    }
    expr.putback(state);
    return true;
}

int Calculator::parse_expr() {
    update_state();
    
    if (std::isdigit(state)) {
        int number = parse_num();
        update_state();
        return number;
    }
    if (state == '-' && is_unary_minus()) {
        return -parse_expr();
    }
    success_parse = false;
    return 0;
}


bool Calculator::is_success_parse() {
    return success_parse && !expr;
}
