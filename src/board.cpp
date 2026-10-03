#include "board.hpp"

#include <iostream>
#include <string>

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
    std::cout << getCurrentBoardAsString();
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
        setSlotValue(i, Piece::None, true);
    }
}

TTT::PlaceResult TTT::Board::setSlotValue(int slot, Piece input) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    if (currentBoard[r][c] != Piece::None) return PlaceResult::SlotTaken;

    currentBoard[r][c] = input;
    return PlaceResult::Ok;
};

TTT::PlaceResult TTT::Board::setSlotValue(int slot, Piece input, bool isForClear) {
    if (slot < 0 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    currentBoard[r][c] = input;
    return PlaceResult::Ok;
};

void TTT::Board::place(int slot) {
    PlaceResult result = setSlotValue(slot, currentPlayer);

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

    totalPlayedTurns++;
    currentPlayer = (currentPlayer == Piece::x) ? Piece::o : Piece::x;
};

std::string TTT::Board::getCurrentBoardAsString() {
    std::string result;

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            result.push_back(valueToChar(currentBoard[r][c]));
            result.push_back(' ');
        }
        result.push_back('\n');
    }
    return result;
};

bool TTT::Board::gameOver() {
    return checkWin(Piece::x) || checkWin(Piece::o) || boardIsFull();
}

bool TTT::Board::boardIsFull() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (currentBoard[r][c] == Piece::None) {
                return false;
            }
        }
    }

    return true;
}

bool TTT::Board::checkWin(Piece player) {
    for (int i = 0; i < 3; i++) {
        if (currentBoard[i][0] == player && currentBoard[i][1] == player &&
            currentBoard[i][2] == player)
            return true;
        if (currentBoard[0][i] == player && currentBoard[1][i] == player &&
            currentBoard[2][i] == player)
            return true;
    }

    // for diagonals
    if (currentBoard[0][0] == player && currentBoard[1][1] == player &&
        currentBoard[2][2] == player)
        return true;
    if (currentBoard[0][2] == player && currentBoard[1][1] == player &&
        currentBoard[2][0] == player)
        return true;

    return false;
}

int TTT::Board::score(TTT::Board& thisBoard) {
    if (thisBoard.checkWin(Piece::x)) {
        return +10;
    }

    if (thisBoard.checkWin(Piece::o)) {
        return -10;
    }

    return 0;
}

std::vector<int> TTT::Board::getAvailableMoves() {
    std::vector<int> moves;

    for (int slot = 1; slot <= 9; slot++) {
        size_t r = (slot - 1) / cols;
        size_t c = (slot - 1) % cols;

        if (currentBoard[r][c] == Piece::None) {
            moves.push_back(slot);
        }
    }
    return moves;
};