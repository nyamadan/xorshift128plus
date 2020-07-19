#pragma once

#include <stdint.h>

#include <random>

namespace rng {

inline uint64_t genRandomSeed() {
  std::random_device random;
  uint32_t upper;
  uint32_t lower;
  upper = random();
  lower = random();
  return (static_cast<uint64_t>(upper) << 32) | lower;
}

inline uint64_t murmurHash3(uint64_t h) {
  h ^= h >> 33;
  h *= 0xff51afd7ed558ccd;
  h ^= h >> 33;
  h *= 0xc4ceb9fe1a85ec53;
  h ^= h >> 33;
  return h;
}

inline void randomize(uint64_t &s0, uint64_t &s1, uint64_t seed) {
  s0 = rng::murmurHash3(seed);
  s1 = rng::murmurHash3(~s0);
}

inline void randomize(uint64_t &s0, uint64_t &s1) {
    rng::randomize(s0, s1, rng::genRandomSeed());
}

inline void xorshift128(uint64_t &s0, uint64_t &s1) {
  uint64_t t = s0;
  uint64_t s = s1;
  s0 = s;
  t ^= t << 23;       // a
  t ^= t >> 17;       // b
  t ^= s ^ (s >> 26); // c
  s1 = t;
}

inline double toDouble(const uint64_t &n) {
  const uint64_t x = (n >> 12) | 0x3ff0000000000000;
  return *reinterpret_cast<const double *>(&x) - 1.0;
}

inline int64_t nextInt64(uint64_t &s0, uint64_t &s1) {
  xorshift128(s0, s1);
  return s0 + s1;
}

inline double nextDouble(uint64_t &s0, uint64_t &s1) {
  xorshift128(s0, s1);
  return toDouble(s0);
}
} // namespace rng