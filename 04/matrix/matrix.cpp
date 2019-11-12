#include "matrix.hpp"

Matrix::Matrix(size_t rows, size_t columns): nrows(rows), ncols(columns), data(new int[nrows * ncols]) {};

Matrix::~Matrix() {
    delete[] data;
}

size_t Matrix::get_rows() const {
    return nrows;
}

size_t Matrix::get_columns() const {
    return ncols;
}

bool Matrix::operator==(const Matrix& other) const {
    if (this == &other) {
        return true;
    }
    if (nrows != other.nrows || ncols != other.ncols) {
        return false;
    }
    for (size_t i = 0; i < nrows * ncols; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix& Matrix::operator*=(int value) {
    for (size_t i = 0; i < nrows * ncols; ++i) {
        data[i] *= value;
    }
    return *this;
}

const Matrix::Row Matrix::operator[](size_t row) const {
    return Row(row, *this);
}

Matrix::Row Matrix::operator[](size_t row) {
    return Row(row, *this);
}

const int& Matrix::Row::operator[](size_t col) const {
    if (row >= matrix.nrows) {
        throw std::out_of_range("Row index is out of range");
    }
    if (col >= matrix.ncols) {
        throw std::out_of_range("Column index is out of range");
    }
    return matrix.data[row * matrix.ncols + col];
}

int& Matrix::Row::operator[](size_t col) {
    if (row >= matrix.nrows) {
        throw std::out_of_range("Row index is out of range");
    }
    if (col >= matrix.ncols) {
        throw std::out_of_range("Column index is out of range");
    }
    return matrix.data[row * matrix.ncols + col];
}
