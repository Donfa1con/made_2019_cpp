#pragma once

#include <functional>
#include <future>
#include <vector>

class Analyzer {
  public:
    using ParseCallback = std::function<void()>;
    using TokenCallback = std::function<void(const std::string&)>;

    Analyzer() = default;
    Analyzer(const Analyzer&) = delete;
    Analyzer(Analyzer&&) = delete;
    Analyzer& operator= (const Analyzer&) = delete;
    Analyzer& operator= (Analyzer&&) = delete;
    ~Analyzer() = default;
    
    void parse(const std::string& data);
    void add_on_parse_begin_callback(const ParseCallback& on_parse_begin);
    void add_on_parse_end_callback(const ParseCallback& on_parse_end);
    void add_on_number_token_callback(const TokenCallback& on_number);
    void add_on_string_token_callback(const TokenCallback& on_string);
  private:
    bool is_number(const std::string& token) const;
    std::vector<std::future<void>> async_call_callbacks(const std::vector<ParseCallback>& callbacks) const;
    void call_token_callbacks(const std::vector<TokenCallback>& callbacks, const std::string& token) const;
    
    std::vector<ParseCallback> on_parse_begin_callbacks;
    std::vector<ParseCallback> on_parse_end_callbacks;
    std::vector<TokenCallback> on_number_callbacks;
    std::vector<TokenCallback> on_string_callbacks;
};
