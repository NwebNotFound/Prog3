#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <class T>
class Vector {
public:
    Vector() = default;

    explicit Vector(std::size_t size, const T& value = T{})
        : data_(new T[size]), size_(size), capacity_(size) {
        std::fill(begin(), end(), value);
    }

    Vector(std::initializer_list<T> values)
        : data_(new T[values.size()]), size_(values.size()), capacity_(values.size()) {
        std::copy(values.begin(), values.end(), begin());
    }

    Vector(const Vector& other)
        : data_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
        std::copy(other.begin(), other.end(), begin());
    }

    Vector(Vector&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)),
          size_(std::exchange(other.size_, 0)),
          capacity_(std::exchange(other.capacity_, 0)) {}

    Vector& operator=(Vector other) noexcept {
        swap(other);
        return *this;
    }

    ~Vector() { delete[] data_; }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void push_back(T value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("Vector::pop_back: vector is empty");
        }
        data_[--size_] = T{};
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        T* new_data = new T[new_capacity];
        std::move(begin(), end(), new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void clear() {
        while (!empty()) {
            pop_back();
        }
    }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    T& at(std::size_t index) {
        check_index(index);
        return data_[index];
    }
    const T& at(std::size_t index) const {
        check_index(index);
        return data_[index];
    }

    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[size_ - 1]; }
    const T& back() const { return data_[size_ - 1]; }

    T* data() { return data_; }
    const T* data() const { return data_; }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

private:
    void check_index(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
    }

    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};
