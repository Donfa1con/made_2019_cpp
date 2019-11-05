#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>

#include "analyzer/analyzer.hpp"


int main(int argc, const char * argv[]) {
    std::ostringstream test_cout;
    
    Analyzer analyzer;
    std::string data("he 341 2w2w");
    
    auto before_parse = [&](){test_cout << "start" << std::endl;};
    auto sleep_callback_begin = [&](){
        std::this_thread::sleep_for (std::chrono::seconds(1));
        test_cout << "sleep" << std::endl;;
    };
    auto end_parse = [&](){test_cout << "end" << std::endl;};
    auto on_number_token = [&](const std::string& token){test_cout << ":number: "<< token << std::endl;};
    auto on_string_token = [&](const std::string& token){test_cout << ":string: " << token << std::endl;};
    
    analyzer.add_on_parse_begin_callback(before_parse);
    analyzer.add_on_parse_begin_callback(sleep_callback_begin);
    analyzer.add_on_parse_end_callback(end_parse);
    analyzer.add_on_number_token_callback(on_number_token);
    analyzer.add_on_string_token_callback(on_string_token);
    
    analyzer.parse(data);
    
    std::cout << test_cout.str();
    std::string out("start\nsleep\n:string: he\n:number: 341\n:string: 2w2w\nend\n");
    
    assert(out == test_cout.str());
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
