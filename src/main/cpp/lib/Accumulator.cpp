// Copyright (C) 2026 by Brenton Bostick
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "common/Accumulator.h"

#undef NDEBUG

#include "common/assert.h"

#include <algorithm>
#include <cmath>


Accumulator::Accumulator(size_t capacity) :
    capacity(capacity),
    buf(),
    index(),
    filteredMean() {}


double Accumulator::getFilteredMean() const {

    ASSERT(!buf.empty());

    return filteredMean;
}

double Accumulator::_computeFilteredMean() const {

    ASSERT(2 <= buf.size());

    std::vector<int64_t> tmp = buf;

    double sum = 0.0;
    for (int64_t x : tmp) {
        sum += static_cast<double>(x);
    }

    double mean = sum / static_cast<double>(buf.size());

    sum = 0.0;
    for (int64_t x : tmp) {
        sum += (static_cast<double>(x) - mean) * (static_cast<double>(x) - mean);
    }

    double sd = ::sqrt(sum / static_cast<double>(buf.size() - 1));

    std::sort(tmp.begin(), tmp.end()); // NOLINT(*-use-ranges)

    double median; // NOLINT(*-init-variables)
    if (tmp.size() % 2 == 0) {

        median = static_cast<double>(tmp[(tmp.size() - 1) / 2] + tmp[tmp.size() / 2]) / 2.0;

    } else {

        median = static_cast<double>(tmp[tmp.size() / 2]);
    }

    std::vector<int64_t> tmp2;
    for (int64_t x : tmp) {
        if (std::abs(static_cast<double>(x) - median) <= sd) {
            tmp2.push_back(x);
        }
    }

    sum = 0.0;
    for (int64_t x : tmp2) {
        sum += static_cast<double>(x);
    }

    mean = sum / static_cast<double>(tmp2.size());

    return mean;
}


int64_t Accumulator::last() const {

    if (buf.empty()) {
        return -1;
    }

    size_t i = (index + capacity - 1) % capacity;

    return buf[i];
}


void Accumulator::push(int64_t val) {

    if (buf.size() == capacity) {

        buf[index] = val;

    } else {

        buf.push_back(val);
    }

    index = (index + 1) % capacity;

    if (buf.size() == 1) {

        filteredMean = static_cast<double>(buf[0]);

    } else {

        filteredMean = _computeFilteredMean();
    }
}


bool Accumulator::empty() const {
    return buf.empty();
}
















