
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
















