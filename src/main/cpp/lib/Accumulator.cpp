
#include "common/Accumulator.h"


Accumulator::Accumulator(size_t capacity) :
    capacity(capacity),
    buf(),
    index(),
    sum() {}


int64_t Accumulator::computeMean() const {

    if (buf.empty()) {
        return -1;
    }

    int64_t rtt = (sum / static_cast<int64_t>(buf.size()));

    return rtt;
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
















