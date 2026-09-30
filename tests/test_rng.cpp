#include "core/rng.hpp"

#include <gtest/gtest.h>

TEST(RngTest, SameSeedProducesEqualValueU64) {
  Rng rng1{1};
  Rng rng2{1};

  for (std::size_t i{0}; i < 10000; ++i) {
    EXPECT_EQ(rng1.next_u64(), rng2.next_u64());
  }
}

TEST(RngTest, SameSeedProducesEqualValueBelow) {
  Rng rng1{1};
  Rng rng2{1};

  for (std::size_t i{0}; i < 10000; ++i) {
    EXPECT_EQ(rng1.next_below(1000), rng2.next_below(1000));
  }
}

TEST(RngTest, SameSeedProducesEqualValueRange) {
  Rng rng1{1};
  Rng rng2{1};

  for (std::size_t i{0}; i < 10000; ++i) {
    EXPECT_EQ(rng1.next_in_range(1000, 2000), rng2.next_in_range(1000, 2000));
  }
}