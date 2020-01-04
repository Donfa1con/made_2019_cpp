#include "BigInt.hpp"


void BigInt::init(const std::string& str) {
    capacity_ = str.size();
    data_ = new char[capacity_];
    sign_ = str[0] == '-';
    for (size_t i = str.size(); i > sign_; --i) {
        data_[size_] = str[i - 1] - 48;
        ++size_;
    }
}

BigInt::BigInt(const std::string& str): size_(0), capacity_(min_capacity_) {
    init(str);
}

BigInt::BigInt(int value): size_(0), capacity_(min_capacity_) {
    std::string str = std::to_string(value);
    init(str);
}

BigInt::~BigInt() {
    delete[] data_;
}

BigInt::BigInt(const BigInt& copied)
    : data_(new char[copied.size_])
    , size_(copied.size_)
    , sign_(copied.sign_)
    , capacity_(copied.capacity_) {
    std::copy(copied.data_, copied.data_ + size_, data_);
}

BigInt::BigInt(BigInt&& moved)
    : data_(moved.data_)
    , size_(moved.size_)
    , sign_(moved.sign_)
    , capacity_(moved.capacity_) {
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.sign_ = false;
    moved.capacity_ = min_capacity_;
}

BigInt& BigInt::operator=(const BigInt& copied) {
    if (this == &copied) {
        return *this;
    }
    char* ptr = new char[copied.size_];
    delete[] data_;
    data_ = ptr;
    size_ = copied.size_;
    sign_ = copied.sign_;
    capacity_ = copied.capacity_;
    std::copy(copied.data_, copied.data_ + size_, data_);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& moved) {
    if (this == &moved) {
        return *this;
    }
    delete[] data_;
    data_ = moved.data_;
    size_ = moved.size_;
    sign_ = moved.sign_;
    capacity_ = moved.capacity_;
    moved.data_ = nullptr;
    moved.size_ = 0;
    moved.sign_ = false;
    moved.capacity_ = min_capacity_;
    return *this;
}

void BigInt::reallocate(size_t new_capacity) {
    if (capacity_ < min_capacity_) {
        return;
    }
    assert(new_capacity >= size_);
    char* new_data = new char[new_capacity];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
}

void BigInt::check_capacity() {
    if (size_ == capacity_) {
        reallocate(capacity_ * 2);
    } else if (size_ < capacity_ / 4) {
        reallocate(capacity_ / 2);
    }
}

bool BigInt::operator==(const BigInt& other) const {
    if (this == &other) {
        return true;
    }
    if (sign_ != other.sign_ || size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator<(const BigInt& other) const {
    if (sign_ > other.sign_) {
        return true;
    } else if (sign_ < other.sign_) {
        return false;
    }
    if (sign_ && size_ < other.size_) {
        return false;
    } else if (!sign_ && size_ < other.size_) {
        return true;
    }
    for (size_t i = size_; i > 0; --i) {
        if (data_[i - 1] < other.data_[i - 1]) {
            return !sign_;
        } else if (data_[i - 1] > other.data_[i - 1]) {
            return sign_;
        }
    }
    return false;
}

bool BigInt::operator!=(const BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator>(const BigInt& other) const {
    return other < *this;
}

bool BigInt::operator<=(const BigInt& other) const {
    return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const {
    return !(*this < other);
}

BigInt BigInt::operator-() const {
    BigInt tmp(*this);
    tmp.sign_ = !tmp.sign_;
    return tmp;
}

BigInt BigInt::operator+(const BigInt& other) const {
    if (sign_ == other.sign_) {
        BigInt first((other.size_ > this->size_ ? other : *this));
        const BigInt& second = (other.size_ <= this->size_ ? other : *this);
        char transfer = 0;
        first.check_capacity();
        for (size_t i = 0; i < second.size_; ++i) {
            transfer = first.data_[i] + second.data_[i] + transfer;
            first.data_[i] = transfer % 10;
            transfer /= 10;
        }
        if (transfer != 0) {
            size_t i = second.size_;
            first.data_[first.size_] = 0;
            while (first.data_[i] + transfer > 9) {
                first.check_capacity();
                transfer = first.data_[i] + transfer;
                first.data_[i] = transfer % 10;
                transfer /= 10;
                ++i;
             }
            first.data_[i] = transfer;
            first.size_ = i + 1;
        }
        return first;
    } else {
        bool condition = (!other.sign_ && other > -(*this)) || (other.sign_ && other < -(*this));
        BigInt first((condition ? other : *this));
        const BigInt& second = (!condition ? other : *this);
        char transfer = 0;
        for (size_t i = second.size_; i > 0; --i) {
            transfer = first.data_[i - 1] - second.data_[i - 1];
            if (transfer >= 0) {
                first.data_[i - 1] = transfer;
            } else {
                size_t j = i;
                while (first.data_[j] == 0) {
                    ++j;
                }
                first.data_[j]--;
                if (first.data_[j] == 0 && j == first.size_ - 1) {
                    --first.size_;
                }
                while (j != i - 1) {
                    first.data_[--j] = 9;
                }
                first.data_[i - 1] = 10 + static_cast<int>(transfer);
                first.check_capacity();
            }
        }
        return first;
    }
}

BigInt BigInt::operator-(const BigInt &other) const {
    return *this + (-other);
}

std::ostream& operator<<(std::ostream& out, const BigInt& obj) {
    if (obj.sign_) {
        out << '-';
    }
    for (size_t i = obj.size_; i > 0; --i) {
        out << static_cast<char>(obj.data_[i - 1] + 48);
    }
    return out;
}

BigInt operator+(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) + second;
}

BigInt operator-(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) - second;
}

bool operator==(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) == second;
}

bool operator<(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) < second;
}

bool operator!=(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) != second;
}

bool operator>(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) > second;
}

bool operator<=(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) <= second;
}

bool operator>=(const int& first, const BigInt& second) {
    return BigInt(std::to_string(first)) >= second;
}
