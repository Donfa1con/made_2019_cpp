#include <iostream>

#include "matrix/matrix.hpp"

int main(int argc, const char * argv[]) {
    const size_t rows = 4;
    const size_t cols = 4;
    Matrix m(rows, cols);
    Matrix m1(rows, cols);
    std::cout << "Shape: " << m.get_rows() << " " <<  m.get_columns() << std::endl;
    for (int i = 0; i < m.get_rows(); ++i) {
        for (int j = 0; j < m.get_columns(); ++j) {
            m[i][j] = i * j;
            m1[i][j] = m[i][j];
        }
    }
    std::cout << (m1 == m) << std::endl;
    
    for (int i = 0; i < m.get_rows(); ++i) {
        for (int j = 0; j < m.get_columns(); ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < m1.get_rows(); ++i) {
        for (int j = 0; j < m.get_columns(); ++j) {
            std::cout << m1[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
