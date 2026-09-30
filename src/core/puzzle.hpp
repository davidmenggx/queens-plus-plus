#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

namespace qpp {
// Immutable puzzle solution.
class Puzzle {
public:
  static constexpr std::size_t MIN_WIDTH = 4;
  static constexpr std::size_t MAX_WIDTH = 16;
  Puzzle(std::vector<std::uint8_t> cell_ids,
         std::vector<std::uint8_t> queen_cols);

private:
  // Flattened grid of IDs (think colors), such that 0 <= ID < Width.
  std::vector<std::uint8_t> cell_ids_;

  // queen_cols_[i] is the column (0-indexed) of the queen on the ith row.
  std::vector<std::uint8_t> queen_cols_;
};
} // namespace qpp