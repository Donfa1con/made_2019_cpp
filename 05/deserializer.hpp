#pragma once

#include <sstream>
#include <utility>

#include "error.hpp"

class Deserializer {
  public:
    explicit Deserializer(std::istream& in): in_(in) {}

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args) {
        return process(std::forward<Args>(args)...);
    }
    
  private:
    std::istream& in_;
    
    template<class T, class... Args>
    Error process(T& value, Args&&... args) {
        Error err1 = process(value);
        Error err2 = process(std::forward<Args>(args)...);
        if (err1 != Error::NoError) {
            return err1;
        }
        if (err2 != Error::NoError) {
            return err2;
        }
        return Error::NoError;
    }
    
    Error process(bool& value) {
        std::string text;
        in_ >> text;
        if (text == "true") {
            value = true;
        } else if (text == "false") {
            value = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }
    
    Error process(uint64_t& value) {
        std::string text;
        in_ >> text;
        if (text.empty()) {
            return Error::CorruptedArchive;
        }
        value = std::strtoull(text.c_str(), nullptr, 10);
        return Error::NoError;
    }
    
    template<class T>
    Error process(T) {
        return Error::UnsupportedType;
    }
    
};
