#pragma once

#include "board.hpp"

namespace TTT {
class AI {
  private:
  public:
    int minimax(TTT::Board& Board, bool maximizing);
    int findBestMove(TTT::Board& board);
};
} // namespace TTT