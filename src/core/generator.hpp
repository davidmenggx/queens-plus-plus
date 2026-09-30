#pragma once

#include "puzzle.hpp"

#include <cstdint>

namespace qpp {
Puzzle generate(std::size_t size, /* Difficulty difficulty, */ uint64_t seed);
}