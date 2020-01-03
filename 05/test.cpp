#include <iostream>
#include <sstream>
#include <fstream>

#include "serializer.hpp"
#include "deserializer.hpp"

struct Data1 {
    uint64_t a;
    bool b;
    uint64_t c;
    
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct Data2 {
    uint64_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

struct Data3 {
    bool a;
    uint64_t b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

struct Data4 {
    uint8_t a;
    bool b;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b);
    }
};

void test_equal() {
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Data1 x{1, true, 2};
    Data1 y;
    const Error err1 = serializer.save(x);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test_small2large() {
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Data1 x{1, true, 2};
    Data2 y;
    const Error err1 = serializer.save(x);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
}

void test_diff_type() {
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Data2 x{1, true};
    Data3 y;
    const Error err1 = serializer.save(x);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::CorruptedArchive);
}

void test_empty_stream() {
    std::stringstream stream;
    Deserializer deserializer(stream);
    Data3 y;
    const Error err = deserializer.load(y);
    assert(err == Error::CorruptedArchive);
}

void test_large2small() {
    std::stringstream stream;
    Serializer serializer(stream);
    Deserializer deserializer(stream);
    Data2 x{2, true};
    Data1 y;
    const Error err1 = serializer.save(x);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::CorruptedArchive);
    assert(x.a == y.a);
    assert(x.b == y.b);
}

void test_filestream() {
    std::fstream file("/tmp/test.txt");
    Serializer serializer(file);
    Deserializer deserializer(file);
    Data1 x{1, true, 2};
    Data1 y;
    const Error err1 = serializer.save(x);
    file.seekg(0, std::ios::beg);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test_unsupported_type() {
    std::stringstream stream;
    Serializer serializer(stream);
    Data4 x{1, true};
    const Error err1 = serializer.save(x);
    assert(err1 == Error::UnsupportedType);
}

int main() {
    test_equal();
    test_small2large();
    test_large2small();
    test_diff_type();
    test_empty_stream();
    test_filestream();
    test_unsupported_type();
    std::cout << "Tests passed!" << std::endl;
    return 0;
}
