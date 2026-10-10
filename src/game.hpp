#pragma once

#include "AI.hpp"
#include "board.hpp"
#include "types/difficulty.hpp"
#include "types/state.hpp"

namespace TTT {

class Game {
  private:
    Difficulty gameDiff = Difficulty::EASY;

  public:
    Game();
    void startGame();

    void playerTurn(TTT::Board& board);

    // misc/messages etc
    void welcomeMessage();
    void startMessage();
};
} // namespace TTT
