#include <chrono>
#include <iostream>
#include <thread>

#include "analyzer/analyzer.hpp"


int main(int argc, const char * argv[]) {
    Analyzer analyzer;
    std::string data("hello 123 world 12 341 2w2w");

    auto before_parse_1 = [](){std::cout << "---" << std::endl;};
    auto before_parse_2 = [](){std::cout << "start parse" << std::endl;};
    auto before_parse_3 = [](){std::cout << "---" << std::endl;};

    auto end_parse_1 = [](){std::cout << "---" << std::endl;};
    auto end_parse_2 = [](){std::cout << "end parse" << std::endl;};
    auto end_parse_3 = [](){std::cout << "---" << std::endl;};

    auto on_number_token_1 = [](const std::string& token){std::cout << ":number: ";};
    auto on_number_token_2 = [](const std::string& token){std::cout << token << std::endl;};

    auto on_string_token_1 = [](const std::string& token){std::cout << ":string: ";};
    auto on_string_token_2 = [](const std::string& token){std::cout << token << std::endl;};

    auto sleep_callback_begin = [](){
        std::this_thread::sleep_for (std::chrono::microseconds(300));
        std::cout << "--begin sleep--" << std::endl;;
    };
    auto sleep_callback_end = [](){
        std::this_thread::sleep_for (std::chrono::microseconds(300));
        std::cout << "--end sleep--" << std::endl;;
    };
    auto sleep_callback_num = [](const std::string& token){
        std::this_thread::sleep_for (std::chrono::microseconds(300));
        std::cout << "--num sleep--" << std::endl;;
    };
    auto sleep_callback_str = [](const std::string& token){
        std::this_thread::sleep_for (std::chrono::microseconds(300));
        std::cout << "--str sleep--" << std::endl;;
    };

    analyzer.add_on_parse_begin_callback(before_parse_1);
    analyzer.add_on_parse_begin_callback(before_parse_2);
    analyzer.add_on_parse_begin_callback(sleep_callback_begin);
    analyzer.add_on_parse_begin_callback(before_parse_3);

    analyzer.add_on_parse_end_callback(end_parse_1);
    analyzer.add_on_parse_end_callback(sleep_callback_end);
    analyzer.add_on_parse_end_callback(end_parse_2);
    analyzer.add_on_parse_end_callback(end_parse_3);

    analyzer.add_on_number_token_callback(on_number_token_1);
    analyzer.add_on_number_token_callback(sleep_callback_num);
    analyzer.add_on_number_token_callback(on_number_token_2);

    analyzer.add_on_string_token_callback(on_string_token_1);
    analyzer.add_on_string_token_callback(sleep_callback_str);
    analyzer.add_on_string_token_callback(on_string_token_2);

    analyzer.parse(data);
    return 0;
}
