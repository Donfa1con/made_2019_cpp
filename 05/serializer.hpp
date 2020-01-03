#pragma once

#include <sstream>
#include <utility>

#include "error.hpp"


class Serializer {
    static constexpr char Separator = ' ';
  public:
    explicit Serializer(std::ostream& out): out_(out) {}
    Serializer(const Serializer&) = delete;
    Serializer(Serializer&&) = delete;
    Serializer& operator=(const Serializer&) = delete;
    Serializer& operator=(Serializer&&) = delete;

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args&&... args) {
        return process(std::forward<Args>(args)...);
    }

  private:
    std::ostream& out_;

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
    
    Error process(bool value) {
        out_ << (value ? "true" : "false") << Separator;
        return Error::NoError;
    }
    
    Error process(uint64_t value) {
        out_ << value << Separator;
        return Error::NoError;
    }
    
    template<class T>
    Error process(T value) {
        return Error::UnsupportedType;
    }
};


