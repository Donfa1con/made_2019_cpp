#pragma once

#include <sstream>
#include <string>
#include <utility>
#include <vector>


std::pair<bool, size_t> parse_substr(const std::string& substr, size_t args_size) {
    bool correct = true;
    size_t num = 0;
    if (substr.size()) {
        for (size_t i = 0; i < substr.size(); ++i) {
            if (std::isdigit(substr[i])) {
                num *= 10;
                num += substr[i] - 48;
            } else {
                correct = false;
                break;
            }
            if (num >= args_size) {
                correct = false;
                break;
            }
        }
    } else {
        correct = false;
    }
    return std::make_pair(correct, num);;
}

std::string set_args(const std::string& str, const std::vector<std::string>& args_vec) {
    std::string format_string = "";
    bool start_brace = false;
    int braces_count = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '{') {
            start_brace = true;
            braces_count = 1;
        }
        if (start_brace) {
            size_t j = i;
            while(j < str.size()) {
                j++;
                if (str[j] == '}') braces_count--;
                if (str[j] == '{') braces_count++;
                if (str[j] == '}' && braces_count == 0) break;
            }
            if (j != str.size() && !braces_count) {
                std::string substr = str.substr(i + 1, j - i - 1);
                bool correct = false;
                size_t num = 0;
                std::tie(correct, num) = parse_substr(substr, args_vec.size());
                if (correct) {
                    format_string += args_vec[num];
                } else {
                    throw std::runtime_error("Incorrect format");
                }
            } else {
                throw std::runtime_error("Parse error");
            }
            i = j;
            start_brace = false;
        } else {
            format_string += str[i];
        }
    }
    return format_string;
}

template<class T>
void extract_args(std::vector<std::string>& args_vec, T&& value) {
    std::stringstream stream;
    stream << value;
    args_vec.emplace_back(stream.str());
}

template<class T, class... Args>
void extract_args(std::vector<std::string>& args_vec, T&& value, Args&&... args) {
    extract_args(args_vec, value);
    extract_args(args_vec, std::forward<Args>(args)...);
}

template<class... Args>
std::string format(const std::string& str, Args&&... args) {
    std::vector<std::string> args_vec;
    extract_args(args_vec, std::forward<Args>(args)...);
    return set_args(str, args_vec);
}
