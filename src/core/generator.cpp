#include "generator.hpp"
#include "puzzle.hpp"
#include "rng.hpp"

#include <cstdint>
#include <vector>

namespace qpp {
Puzzle generate(std::size_t width, /* Difficulty difficulty, */ uint64_t seed) {
  Rng rng{seed};

  // Since the Puzzle object is immutable, we iterate on a "scratchpad".
  std::vector<std::uint8_t> scratch_cell_ids(width * width);
  std::vector<std::uint8_t> scratch_queen_cols(width);

  // A possible approach:
  // 1. Place the queens, ensuring that there are no shared rows, columns, or
  // diagonal touching.
  //
  // notes: this looks like a permutation, but diags cannot touch
  //
  // 2. Using the seed and Rng, randomly grow a region from each of the queens.
  // Randomly choose a queen and let it randomly claim an empty cell orthogonal
  // to it, until the grid is full.
  // 3. Count the number of solutions using a solver (this solver should be
  // producible using pure logic, i.e. should not require extreme brute force).
  // Repeat 1 and 2 until there is only 1 solution. At this stage, you can
  // either completely restart generation or identify the cause of the collision
  // and repair.

  return Puzzle{scratch_cell_ids, scratch_queen_cols};
}
} // namespace qpp