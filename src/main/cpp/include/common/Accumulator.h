
#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>


struct Accumulator {

    size_t capacity;
    std::vector<int64_t> buf;
    size_t index;
    int64_t sum;

    Accumulator(size_t capacity);

    double computeMean() const;
    void push(int64_t val);
};
















