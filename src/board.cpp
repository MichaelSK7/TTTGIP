#include "board.hpp"

#include <iostream>
#include <stdint.h>

char TTT::Board::valueToChar(Piece p) {
    if (p == Piece::o) return 'o';
    if (p == Piece::x) return 'x';
    return '.';
}

TTT::Piece TTT::Board::charToValue(char character) {
    switch (character) {
    case 'x':
        return Piece::x;
    case 'o':
        return Piece::o;
    default:
        return Piece::None;
    }
};

void TTT::Board::main() {
    place(2);
    place(3);
    place(5);
    place(1);
    place(8);
    displayBoard();
}

void TTT::Board::displayBoard() {
    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            std::cout << valueToChar(currentBoard[r][c]) << ' ';
        }
        std::cout << '\n';
    }
}

void TTT::Board::clearBoard() {
    for (size_t i = 1; i <= slotCount; i++) {
        setSlotValue(i, 'F', true);
    }
}

TTT::PlaceResult TTT::Board::setSlotValue(uint8_t slot, Piece input) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    if (currentBoard[r][c] != Piece::None) return PlaceResult::SlotTaken;

    currentBoard[r][c] = input;
    return PlaceResult::Ok;
};

TTT::PlaceResult TTT::Board::setSlotValue(uint8_t slot, char input, bool isForClear) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / cols;
    size_t c = (slot - 1) % cols;

    currentBoard[r][c] = charToValue(input);
    return PlaceResult::Ok;
};

void TTT::Board::place(uint8_t slot) {
    PlaceResult result = setSlotValue(slot, currentTurn);

    switch (result) {
    case PlaceResult::Ok:
        break;
    case PlaceResult::OutOfRange:
        std::cout << "Pick 1-9\n";
        break;
    case PlaceResult::SlotTaken:
        std::cout << "That slot is taken\n";
        break;
    }
};

// TTT::State TTT::Board::SearchTripple() {
//     for (size_t i = 0; i <= slotCount - 1; i++) {
//         switch ()
//     }
// }

const TTT::Piece& TTT::Board::getCurrentBoard() {
    return currentBoard;
};
