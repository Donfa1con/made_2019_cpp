#include <cassert>
#include <iostream>

#include "matrix/matrix.hpp"

int main(int argc, const char * argv[]) {
    const size_t rows = 5;
    const size_t cols = 4;
    Matrix m1(rows, cols);
    Matrix m2(rows, cols);
    for (int i = 0; i < m1.get_rows(); ++i) {
        for (int j = 0; j < m1.get_columns(); ++j) {
            m1[i][j] = i * j;
        }
    }
    for (int i = 0; i < m2.get_rows(); ++i) {
        for (int j = 0; j < m2.get_columns(); ++j) {
            m2[i][j] = i * j * 2;
        }
    }

    m1 *= 2;
    assert(m1 == m2);
    assert(!(m1 != m2));
    assert(m1.get_rows() == rows);
    assert(m1.get_columns() == cols);

    m1[3][3] = 55;
    int tmp = m1[3][3];
    assert(tmp == 55);

    try {
        m1[1][5];
        assert(false);
    } catch (std::out_of_range) {
        assert(true);
    }

    std::cout << "Tests passed!" << std::endl;
    return 0;
}
