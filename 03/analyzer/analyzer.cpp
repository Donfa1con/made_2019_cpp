#include <algorithm>
#include <future>
#include <sstream>

#include "analyzer.hpp"


void Analyzer::add_on_parse_begin_callback(const ParseCallback& on_parse_begin) {
    on_parse_begin_callbacks.push_back(on_parse_begin);
}

void Analyzer::add_on_parse_end_callback(const ParseCallback& on_parse_end) {
    on_parse_end_callbacks.push_back(on_parse_end);
}

void Analyzer::add_on_number_token_callback(const TokenCallback& on_number) {
    on_number_callbacks.push_back(on_number);
}

void Analyzer::add_on_string_token_callback(const TokenCallback& on_string) {
    on_string_callbacks.push_back(on_string);
}

std::vector<std::future<void>> Analyzer::async_call_callbacks(const std::vector<ParseCallback>& callbacks) const {
    std::vector<std::future<void>> futures;
    for (int i = 0; i < callbacks.size(); ++i) {
        futures.push_back(std::async(callbacks[i]));
    }
    return futures;
}

void Analyzer::call_token_callbacks(const std::vector<TokenCallback>& callbacks, const std::string& token) const {
    for (int i = 0; i < callbacks.size(); ++i) {
        callbacks[i](token);
    }
}

bool Analyzer::is_number(const std::string& token) const {
    return std::all_of(token.begin(), token.end(), [](unsigned char ch){
        return std::isdigit(ch);
    });
}

void Analyzer::parse(const std::string& data) {
    for (auto& fut : async_call_callbacks(on_parse_begin_callbacks)) {
        fut.get();
    }
    
    std::istringstream stream(data);
    std::string token;
    while (stream >> token) {
        bool number = is_number(token);
        if (number) {
            call_token_callbacks(on_number_callbacks, token);
        } else {
            call_token_callbacks(on_string_callbacks, token);
        }
    }
    
    for (auto& fut : async_call_callbacks(on_parse_end_callbacks)) {
        fut.get();
    }
}
