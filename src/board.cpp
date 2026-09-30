#include "board.hpp"

#include <iostream>
#include <stdint.h>

char TTT::Board::valueToChar(Piece p) {
    if (p == Piece::O) return 'O';
    if (p == Piece::X) return 'X';
    return '.';
}

TTT::Piece TTT::Board::charToValue(char character) {
    switch (character) {
    case 'X':
        return Piece::X;
    case 'O':
        return Piece::O;
    default:
        return Piece::None;
    }
};

void TTT::Board::main() {
    displayBoard();

    place(3, 'X');
    displayBoard();

    clearBoard();
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
    for (size_t i = 1; i <= 9; i++) {
        setSlotValue(i, 'F', true);
    }
}

TTT::PlaceResult TTT::Board::setSlotValue(uint8_t slot, char input) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    if (currentBoard[r][c] != Piece::None) return PlaceResult::SlotTaken;

    currentBoard[r][c] = charToValue(input);
    return PlaceResult::Ok;
};

TTT::PlaceResult TTT::Board::setSlotValue(uint8_t slot, char input, bool isForClear) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    currentBoard[r][c] = charToValue(input);
    return PlaceResult::Ok;
};

void TTT::Board::place(uint8_t slot, char value) {
    PlaceResult result = setSlotValue(slot, value);

    switch (result) {
    case PlaceResult::Ok:
        break;
    case PlaceResult::OutOfRange:
        std::cout << "Pick 1-9\n";
        break;
    case PlaceResult::SlotTaken:
        std::cout << "That slot is taken\n";
        break;
    case PlaceResult::InvalidPiece:
        std::cout << "Bad piece\n";
        break;
    }
};

TTT::State TTT::Board::SearchTripple(const Piece& board) {
}