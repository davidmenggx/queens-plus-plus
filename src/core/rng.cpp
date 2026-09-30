#include "rng.hpp"

#include <bit>
#include <cassert>

namespace {
// SplitMix64
std::uint64_t splitmix64(std::uint64_t &x) {
  std::uint64_t z{(x += 0x9E3779B97F4A7C15ULL)};
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
  return z ^ (z >> 31);
}
} // namespace

Rng::Rng(std::uint64_t seed) {
  for (std::uint64_t &word : state_) {
    word = splitmix64(seed);
  }
}

// xoshiro256**
std::uint64_t Rng::next_u64() {
  const std::uint64_t result{std::rotl(state_[1] * 5, 7) * 9};
  const std::uint64_t t{state_[1] << 17};

  state_[2] ^= state_[0];
  state_[3] ^= state_[1];
  state_[1] ^= state_[2];
  state_[0] ^= state_[3];
  state_[2] ^= t;
  state_[3] = std::rotl(state_[3], 45);

  return result;
}

std::uint32_t Rng::next_u32() {
  return static_cast<std::uint32_t>(next_u64() >> 32);
}

std::uint32_t Rng::next_below(std::uint32_t bound) {
  assert(bound > 0 && "next_below: bound must be > 0");

  std::uint64_t m{static_cast<std::uint64_t>(next_u32()) * bound};
  std::uint32_t low{static_cast<std::uint32_t>(m)};

  if (low < bound) {
    const std::uint32_t threshold{static_cast<std::uint32_t>(-bound) % bound};
    while (low < threshold) {
      m = static_cast<std::uint64_t>(next_u32()) * bound;
      low = static_cast<std::uint32_t>(m);
    }
  }
  return static_cast<std::uint32_t>(m >> 32);
}

std::int32_t Rng::next_in_range(std::int32_t lo, std::int32_t hi) {
  assert(lo <= hi && "next_in_range: lo must be <= hi");

  const std::uint32_t ulo{static_cast<std::uint32_t>(lo)};
  const std::uint32_t span{static_cast<std::uint32_t>(hi) - ulo + 1};

  const std::uint32_t offset = (span == 0) ? next_u32() : next_below(span);

  return static_cast<std::int32_t>(ulo + offset);
}