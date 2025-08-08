

#pragma once
#include <iostream>
#include <algorithm>

using namespace std;


class MemoryBlock{
    size_t length_;
    int* data_;
 public:
    explicit MemoryBlock(size_t length): length_(length), data_(new int[length_]) {
        std::cout << "In memoryBlock(size_t) .length:" << length << std::endl;
    }
    ~MemoryBlock() {
        std::cout << "In ~MemoryBlock(). length = " << length_ << ".";
        if (nullptr != data_) {
            delete[] data_;
        }
        std::cout << std::endl;
    }
    // copy constructor
    MemoryBlock(const MemoryBlock& other) noexcept : length_(other.length_), data_(new int[length_]) {
        std::cout << "In MemoryBlock(const MemoryBlock&). length = " << other.length_ << ". Copying resource." << std::endl;
        std::copy(other.data_, other.data_ + other.length_, data_);
    }
    // move constructor
    MemoryBlock(MemoryBlock&& that):length_(that.length_), data_(that.data_) {
        std::cout << "In MemoryBlock(MemoryBlock&&). length = " << that.length_ << ". Moving resource." << std::endl;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        // in other words we steal contents from `that`, cause `that` is a 
        // rvalue so there is no other thread uses the contents of `that` and 
        // therefore we can steal it safely.
        that.length_ = 0;
        that.data_ = nullptr;
    }
    // copy assignment opreator.
    MemoryBlock& operator=(const MemoryBlock& other) {
        std::cout << "In operator=(const MemoryBlock&). length = "<< other.length_ << ". Copying resource." << std::endl;
        if (this == &other) {
            return *this;
        }
        if (data_) {
            delete[] data_;
        }
        length_ = other.length_;
        data_ = new int[length_];
        std::copy(other.data_, other.data_ + other.length_, data_);
        return *this;
    }
    // move assignment operator
    MemoryBlock& operator=(MemoryBlock&& other) {
        std::cout << "In operator=(MemoryBlock&&). length = " << other.length_ << "." << std::endl;
        if (this != &other) {
            if (nullptr != data_) {
                delete[] data_;
            }
            data_ = other.data_;
            length_ = other.length_;
            other.data_ = nullptr;
            other.length_ = 0;
        }
        return *this;
    }
    auto length() const -> size_t {return length_;}
};