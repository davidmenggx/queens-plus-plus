#pragma once

#include "puzzle.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace qpp {
// Mutable game board that player interacts with.
class Board {
public:
  enum class CellState { Empty, X, Queen };

  // TODO: Probably should reconsider this, where will we construct a Board?
  // Could we just pass in the Puzzle straight up?
  // also this should be in a cpp file LMAO
  explicit Board(std::size_t width)
      : width_{checked_width(width)}, cells_(width * width) {}

  static std::size_t checked_width(std::size_t width) {
    if (width < Puzzle::MIN_WIDTH) {
      throw std::invalid_argument("Board width must be at least 4");
    }
    return width;
  }

  CellState state_at(std::size_t row, std::size_t col) const {
    return cells_[row * width_ + col];
  }

  void reset() { std::fill(cells_.begin(), cells_.end(), CellState::Empty); }

private:
  // This should be declared first, so the width check happens first.
  std::size_t width_;

  // Flattened grid of cell states, such that 0 <= ID < Width.
  std::vector<CellState> cells_;

  // TODO: Move history for undo, timer, etc. (Or store these elsewhere)
};
} // namespace qpp