#pragma once

#include <array>
#include <cstdint>

// xoshiro256**
class Rng {
public:
  explicit Rng(std::uint64_t seed);

  // Uniform integer in [0, bound). Requires bound > 0.
  std::uint32_t next_below(std::uint32_t bound);

  // Uniform integer in [lo, hi] (inclusive). Requires lo <= hi.
  std::int32_t next_in_range(std::int32_t lo, std::int32_t hi);

  // Raw 64 random bits.
  std::uint64_t next_u64();

private:
  std::uint32_t next_u32();

  std::array<std::uint64_t, 4> state_;
};