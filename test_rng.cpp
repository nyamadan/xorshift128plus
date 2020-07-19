#include "rng.hpp"

#include "gtest/gtest.h"

TEST(RandomNumberGeneratorTest, NextDouble) {
    uint64_t s0, s1;
    rng::randomize(s0, s1);

    auto v = rng::nextDouble(s0, s1);
    EXPECT_GE(v, 0.0);
    EXPECT_LT(v, 1.0);
}