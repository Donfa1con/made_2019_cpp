#pragma once

#include <cassert>
#include <vector>

class Matrix {
  public:
    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix&) = delete;
    Matrix(Matrix&&) = delete;
    Matrix& operator= (const Matrix&) = delete;
    Matrix& operator= (Matrix&&) = delete;
    ~Matrix();
    
    class Row {
      public:
        Row(size_t row, const Matrix& matrix): row(row), matrix(matrix) {};
        const int& operator[](size_t col) const;
        int& operator[](size_t col);
      private:
        const size_t row;
        const Matrix& matrix;
    };
    const Row operator[] (size_t row) const;
    Row operator[] (size_t row);

    size_t get_rows() const;
    size_t get_columns() const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;
    Matrix& operator*=(int value);

  private:
    size_t nrows;
    size_t ncols;
    int* data;
};
