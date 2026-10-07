#pragma once

#include "types/state.hpp"

#include <string>
#include <vector>

namespace TTT {

enum class Piece : int { None, x, o };

enum class PlaceResult : int { Ok, OutOfRange, SlotTaken, InvalidPiece };

class Board {
  private:
    const int rows = 3;
    const int cols = 3;
    const int slotCount = 9;

    int XCount = 0;
    int OCount = 0;

    Piece playerPiece = Piece::None;

  public:
    Piece currentBoard[3][3] = {};

    void showBoard();
    void clearBoard();

    Piece charToValue(char character);
    char valueToChar(Piece p);

    PlaceResult setSlotValue(int slot, Piece value);
    PlaceResult setSlotValue(int slot, Piece value, bool isForClear);
    void forceSetSlotValue(int slot, Piece piece);
    bool place(int slot, Piece piece);

    std::string getCurrentBoardAsString();
    Piece getPlayerPiece();
    void setPlayerPiece(Piece piece);

    bool gameOver();
    bool boardIsFull();

    bool checkWin(Piece player);
    int score(Board& thisBoard);
    int score(Board& thisBoard, int depth);
    int evaluate();

    std::vector<int> getAvailableMoves();
};

}; // namespace TTT