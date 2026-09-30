#include "puzzle.hpp"

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

namespace qpp {
Puzzle::Puzzle(std::vector<std::uint8_t> cell_ids,
               std::vector<std::uint8_t> queen_cols)
    : cell_ids_{std::move(cell_ids)}, queen_cols_{std::move(queen_cols)} {
  const std::size_t board_width{queen_cols_.size()};
  if (board_width < MIN_WIDTH || board_width > MAX_WIDTH) {
    throw std::invalid_argument("Invalid board width");
  }
  if (cell_ids_.size() != board_width * board_width) {
    throw std::invalid_argument(
        "Cell ID size must equal square of board width");
  }
}
} // namespace qpp