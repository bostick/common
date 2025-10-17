
#include "common/random.h"

#include <random>


static std::mt19937 gen;
static std::uniform_int_distribution<int> dis;


int NextRandomInteger() {
    return dis(gen);
}

int NextRandomIntegerInRangeInclusive(int lo, int hi) {
    return lo + (NextRandomInteger() % (hi - lo + 1));
}


void SeedRandom(uint32_t s) {
    gen.seed(s);
}


#define RAND_LIMIT 32767

// Random floating point number in range [lo, hi]
float NextRandomFloatInRangeInclusive(float lo, float hi) {
    auto r = static_cast<float>(NextRandomInteger() & ( RAND_LIMIT ) );
    r /= RAND_LIMIT;
    r = (( hi - lo ) * r) + lo;
    return r;
}
















