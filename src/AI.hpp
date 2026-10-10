#pragma once

#include "board.hpp"
#include "types/difficulty.hpp"

namespace TTT {

class AI {
  private:
    Piece AIPiece = Piece::None;
    Difficulty AIDifficulty = Difficulty::EASY;

  public:
    void AIMove(TTT::Board& board);

    int minimax(TTT::Board& Board, int depth, int maxDepth, bool maximizing);

    int findBestMove(TTT::Board& board, int maxDepth, bool& maximizing);
    int difficultyToInt(Difficulty diff);

    void setDifficulty(Difficulty diff);
};
} // namespace TTT