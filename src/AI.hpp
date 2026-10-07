#pragma once

#include "board.hpp"

namespace TTT {

class AI {
  private:
    Piece AIPiece = Piece::None;

  public:
    void AIMove(TTT::Board& board);

    int minimax(TTT::Board& Board, int depth, int maxDepth, bool maximizing);

    int findBestMove(TTT::Board& board, int maxDepth, bool& maximizing);
};
} // namespace TTT