// Copyright (C) 2025 by Brenton Bostick
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


Accumulator::Accumulator(size_t capacity) :
    capacity(capacity),
    buf(),
    index(),
    sum() {}


double Accumulator::computeMean() const {

    if (buf.empty()) {
        return -1;
    }

    double mean = (static_cast<double>(sum) / static_cast<double>(buf.size()));

    return mean;
}


void Accumulator::push(int64_t val) {

    if (buf.size() == capacity) {

        sum -= buf[index];

        buf[index] = val;

        sum += val;

        index = (index + 1) % capacity;

        return;
    }

    buf.push_back(val);

    sum += val;

    index = (index + 1) % capacity;
}
















