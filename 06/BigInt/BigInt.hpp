#pragma once

#include <cstdint>
#include <iostream>

class BigInt {
  public:
    BigInt(int value);
    BigInt(const std::string& str);
    BigInt(const BigInt& copied);
    BigInt(BigInt&& moved);
    BigInt& operator=(const BigInt& copied);
    BigInt& operator=(BigInt&& moved);
    ~BigInt();
    
    bool operator==(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    BigInt operator-() const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& out, const BigInt& obj);
    friend BigInt operator+(const int& first, const BigInt& second);
    friend BigInt operator-(const int& first, const BigInt& second);
    
    friend bool operator==(const int& first, const BigInt& second);
    friend bool operator<(const int& first, const BigInt& second);
    friend bool operator!=(const int& first, const BigInt& second);
    friend bool operator>(const int& first, const BigInt& second);
    friend bool operator<=(const int& first, const BigInt& second);
    friend bool operator>=(const int& first, const BigInt& second);

  private:
    void init(const std::string& str);
    void reallocate(size_t new_capacity);
    void check_capacity();
    
    char* data_;
    bool sign_;
    size_t size_;
    size_t capacity_;
    static constexpr size_t min_capacity_ = 8;
};
