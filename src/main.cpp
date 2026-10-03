#include "AI.hpp"
#include "board.hpp"
#include "save.hpp"

#include <iostream>

using namespace TTT;

int main() {
    Board B;
    AI A;

    B.setSlotValue(1, Piece::x);
    B.setSlotValue(2, Piece::x);

    B.setSlotValue(4, Piece::o);
    B.setSlotValue(5, Piece::o);

    B.displayBoard();

    std::cout << "AI chooses: " << A.findBestMove(B);
}