#pragma once

#include <sstream>
#include <string>
#include <utility>
#include <vector>


std::pair<bool, size_t> parse_substr(const std::string& substr, size_t args_size);

std::string set_args(const std::string& str, const std::vector<std::string>& args_vec);

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
