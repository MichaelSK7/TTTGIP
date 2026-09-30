#pragma once

#include "types/state.hpp"

#include <stdint.h>

namespace TTT {

enum class Piece : uint8_t { None, x, o };

enum class PlaceResult : uint8_t { Ok, OutOfRange, SlotTaken, InvalidPiece };

class Board {
  private:
    const uint8_t rows = 3;
    const uint8_t cols = 3;
    const uint8_t slotCount = 9;

    uint8_t XCount = 0;
    uint8_t OCount = 0;

    Piece currentTurn = Piece::x;

    Piece currentBoard[3][3] = {};

  public:
    void main();
    void displayBoard();
    void clearBoard();

    Piece charToValue(char character);
    char valueToChar(Piece p);

    PlaceResult setSlotValue(uint8_t slot, Piece value);
    PlaceResult setSlotValue(uint8_t slot, char value, bool isForClear);
    void place(uint8_t slot);

    State SearchTripple();

    const Piece& getCurrentBoard();
};

}; // namespace TTT