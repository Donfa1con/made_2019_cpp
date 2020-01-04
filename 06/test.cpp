#include <iostream>
#include <sstream>
#include <cassert>

#include "BigInt/BigInt.hpp"

void test_cmp() {
    BigInt tmp1("-10");
    BigInt tmp2("1000");
    assert(tmp1 < tmp2);
    
    BigInt tmp3("10");
    BigInt tmp4("-1000");
    assert(tmp3 > tmp4);

    BigInt tmp5("-10");
    BigInt tmp6("-1000");
    assert(tmp5 > tmp6);

    BigInt tmp7("10");
    BigInt tmp8("1000");
    assert(tmp7 < tmp8);
    
    BigInt tmp9("1000");
    BigInt tmp10("1000");
    assert(tmp9 == tmp10);
    
    BigInt tmp11("-1000");
    BigInt tmp12("-1000");
    assert(tmp11 == tmp12);
}

void test_unary_minus() {
    BigInt tmp1("-10");
    assert(-tmp1 == 10);
    
    BigInt tmp2("10");
    assert(-tmp2 == -10);
}

void test_plus_minus() {
    BigInt tmp1("99999");
    BigInt tmp2("100");
    assert((tmp1 + tmp2) == 100099);

    BigInt tmp3("9999");
    BigInt tmp4("-100");
    assert(tmp3 + tmp4 == 9899);

    BigInt tmp5("9999");
    BigInt tmp6("100");
    assert(tmp5 - tmp6 == 9899);

    BigInt tmp7("9999");
    BigInt tmp8("-100");
    assert(tmp7 - tmp8 == 10099);
}

void test_stream() {
    BigInt tmp1("99999");
    std::stringstream stream1;
    stream1 << tmp1;
    assert(stream1.str() == "99999");
    
    BigInt tmp2("-8888");
    std::stringstream stream2;
    stream2 << tmp2;
    assert(stream2.str() == "-8888");
}

void test_int_plus_minus() {
    BigInt a = 1;
    BigInt b = a;
    BigInt c = a + b + 2;
    assert(c == 4);
    BigInt d("9999999999999999999999999999999999999999");
    BigInt res1("10000000000000000000000000000000000000003");
    assert(c + d == res1);
    BigInt e("-10101010101010101010101010101");
    BigInt res2("10000000000010101010101010101010101010104");
    assert(res1 - e == res2);
    BigInt res3("9999999999989898989898989898989898989902");
    assert(res1 + e == res3);
}

int main() {
    test_cmp();
    test_unary_minus();
    test_plus_minus();
    test_stream();
    test_int_plus_minus();
    return 0;
}
