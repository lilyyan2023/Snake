#ifndef FINAL_PROJECT_RINGBUFFER_H
#define FINAL_PROJECT_RINGBUFFER_H

#include <iostream>
#include <initializer_list>
#include <vector>
#include <ge211.hxx>

using uint = unsigned int;

///
/// Ring Buffer class
///
template <typename T>
class RingBuffer {
private:
    /// Fields
    std::vector<T> data_;
    // Size is the number of elements; capacity is the maximum length.
    uint st_, size_, capacity_;

    /// Helpers
    void resize() { reserve(2 * capacity_ + 1); }

public:
    using value_type = T;

    /// Constructors & destroyer
    // Empty and size = 0.
    RingBuffer() {
        st_ = size_ = capacity_ = 0;
    }
    // Empty ring buffer with size n.
    explicit RingBuffer(uint n) {
        data_ = std::vector<T>(n);
        st_ = size_ = 0;
        capacity_ = n;
    }
    //Initialize with size and value
    RingBuffer(uint n, T value) {
        st_ = 0;
        size_ = capacity_ = n;
        data_ = std::vector<T>(n, value);
    }
    // Using iterators.
    template <typename InputIterator> RingBuffer(InputIterator first, InputIterator last) {
        st_ = 0;
        size_ = capacity_ = last - first;
        data_ = std::vector<T>(first, last);
    }
    // Using initializer_list
    RingBuffer(std::initializer_list<T> list) {
        st_ = 0;
        size_ = capacity_ = list.size();
        data_ = std::vector<T>(list.begin(), list.end());
    }

    /// Accessors
    uint st() const { return st_; }
    uint ed() const { return (st_ + size_) % capacity_; }
    uint size() const { return size_; }
    bool empty() const { return size_ == 0; }
    uint capacity() const { return capacity_; }
    T front() const { return data_[st_]; }
    T back() const { return data_[(st_ + size_ - 1) % capacity_]; }
    const T& operator[](uint ind) const {
        if (ind >= size_)
            throw std::range_error("RingBuffer.operator[]: out of bounds\n");
        return data_[(st_ + ind) % capacity_];
    }

    /// Modifiers
    T& front() { return data_[st_]; }
    T& back() { return data_[(st_ + size_ - 1) % capacity_]; }
    T& operator[](uint ind) {
        if (ind >= size_)
            throw std::range_error("RingBuffer.operator[]: out of bounds\n");
        return data_[(st_ + ind) % capacity_];
    }
    void push_back(T element) {
        if (size_ == capacity_)
            resize();

        data_[ed()] = element;
        ++size_;
    }
    void pop_back() {
        --size_;
    }
    void push_front(T element) {
        if (size_ == capacity_)
            resize();

        st_ = (st_ + capacity_ - 1) % capacity_;
        data_[st_] = element;
        ++size_;
    }
    void pop_front() {
        st_ = (st_ + 1) % capacity_;
        --size_;
    }
    // Enlarge the size of the array to "size".
    void reserve(uint size) {
        if (size < size_)
            throw std::logic_error("RingBuffer.reserve: size too small\n");

        std::vector<T> temp(size);
        for (uint i = 0; i < size_; i++)
            temp[i] = data_[(st_ + i) % capacity_];
        st_ = 0;
        capacity_ = size;
        data_ = temp;
    }
    void clear() {
        size_ = 0;
    }

    /// Iterator classes
    template <typename refT>
    class iterator_type;
    using iterator = iterator_type<RingBuffer<T>&>;
    using const_iterator = iterator_type<const RingBuffer<T>&>;

    iterator begin() { return {st_, *this}; }
    iterator end() { return {ed(), *this}; }
    const_iterator begin() const { return {st_, *this}; }
    const_iterator end() const { return {ed(), *this}; }

    /// Operators
    bool operator==(const RingBuffer<T>& other) const {
        if (size_ != other.size_)
            return false;
        for (uint i = 0; i < size_; i++) {
            if ((*this)[i] != other[i])
                return false;
        }
        return true;
    }
    bool operator!=(const RingBuffer<T>& other) const {
        return !(*this == other);
    }
};

template <typename T>
template <typename refT>
class RingBuffer<T>::iterator_type
        : public std::iterator<std::bidirectional_iterator_tag, T> {
private:
    uint current_; // The ACTUAL index number of array.
    refT super_; // The containing RingBuffer.
    friend RingBuffer<T>;

// Constructor; points to the current_th entry.
    iterator_type(uint ind, refT rb)
            : current_(ind % rb.capacity())
            , super_(rb)
    { }
public:
    T operator*() const {
        return super_.data_[current_];
    }
    T* operator->() const {
        return &super_.data_[current_];
    }
    iterator_type<refT>& operator++() {
        current_ = (current_ + 1) % super_.capacity_;
        return *this;
    }
    iterator_type<refT>& operator--() {
        current_ = (current_ + super_.capacity_ - 1) % super_.capacity_;
        return *this;
    }
    iterator_type<refT> operator++(int) {
        iterator temp(*this);
        ++*this;
        return temp;
    }
    iterator_type<refT> operator--(int) {
        iterator temp(*this);
        --*this;
        return temp;
    }
    bool operator==(iterator_type<refT>& other) const {
        return other.current_ == current_ && other.super_ == super_;
    }
    bool operator!=(iterator_type<refT>& other) const {
        return !(*this == other);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream & os, RingBuffer<T> rb) {
    for (uint i = 0; i < rb.size(); i++)
        os << rb[i] << " ";
    return os;
}

///
/// Added for ge211::Position's default construction
///

class Position : public ge211::Position
{
public:
    Position() : ge211::Position{-1,-1} { }
    Position(int x, int y) : ge211::Position{x,y} { }
    Position(ge211::Position pos) : ge211::Position{pos} { }
};

using Snake = RingBuffer<Position>;

#endif //FINAL_PROJECT_RINGBUFFER_H
