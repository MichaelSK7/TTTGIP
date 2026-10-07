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

void TTT::Board::showBoard() {
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

TTT::PlaceResult TTT::Board::setSlotValue(int slot, Piece piece) {
    if (slot < 1 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    if (currentBoard[r][c] != Piece::None) return PlaceResult::SlotTaken;

    currentBoard[r][c] = piece;
    return PlaceResult::Ok;
};

TTT::PlaceResult TTT::Board::setSlotValue(int slot, Piece input, bool isForClear) {
    if (slot < 1 || slot > 9) return PlaceResult::OutOfRange;

    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    currentBoard[r][c] = input;
    return PlaceResult::Ok;
};

void TTT::Board::forceSetSlotValue(int slot, Piece piece) {
    // This function is meant for specific reasons.
    // NOT SAFE
    size_t r = (slot - 1) / rows;
    size_t c = (slot - 1) % cols;

    currentBoard[r][c] = piece;
};

bool TTT::Board::place(int slot, Piece piece) {
    PlaceResult result = setSlotValue(slot, piece);

    switch (result) {
    case PlaceResult::Ok:
        return true;
        break;
    case PlaceResult::OutOfRange:
        std::cout << "Pick 1-9\n";
        return false;
        break;
    case PlaceResult::SlotTaken:
        std::cout << "That slot is taken\n";
        return false;
        break;
    }
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

TTT::Piece TTT::Board::getPlayerPiece() {
    return playerPiece;
}

void TTT::Board::setPlayerPiece(TTT::Piece piece) {
    playerPiece = piece;
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

int TTT::Board::score(TTT::Board& thisBoard, int depth) {
    if (thisBoard.checkWin(Piece::x)) {
        return 10 - depth;
    }

    if (thisBoard.checkWin(Piece::o)) {
        return depth - 10;
    }

    return 0;
}

int TTT::Board::evaluate() {
    int score;

    // Rows
    for (int i = 0; i < 3; i++) {
        int x = 0;
        int o = 0;

        for (int j = 0; j < 3; j++) {
            if (currentBoard[i][j] == Piece::x) x++;
            if (currentBoard[i][j] == Piece::o) o++;
        }

        if (x == 2 && o == 0) score += 5;
        if (o == 2 && x == 0) score -= 5;
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        int x = 0;
        int o = 0;

        for (int j = 0; j < 3; j++) {
            if (currentBoard[j][i] == Piece::x) x++;
            if (currentBoard[j][i] == Piece::o) o++;
        }

        if (x == 2 && o == 0) score += 5;
        if (0 == 2 && x == 0) score -= 5;
    }

    return score;
};

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