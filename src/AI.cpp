#include "AI.hpp"
#include "Board.hpp"

#include <algorithm>
#include <vector>

using namespace TTT;

int AI::minimax(TTT::Board& thisBoard, bool maximizing) {
    if (thisBoard.gameOver()) {
        return thisBoard.score(thisBoard);
    }

    std::vector<int> scores;

    for (int move : thisBoard.getAvailableMoves()) {
        Piece player = maximizing ? Piece::x : Piece::o;

        thisBoard.setSlotValue(move, player);

        int result = minimax(thisBoard, !maximizing);

        scores.push_back(result);

        thisBoard.setSlotValue(move, Piece::None);
    }

    if (maximizing) {
        return *std::max_element(scores.begin(), scores.end());
    } else {
        return *std::min_element(scores.begin(), scores.end());
    }
}

int AI::findBestMove(TTT::Board& board) {
    int bestScore = -1000;
    int bestMove = -1;

    for (int move : board.getAvailableMoves()) {
        board.setSlotValue(move, Piece::x);

        int result = minimax(board, false);

        board.setSlotValue(move, Piece::None);

        if (result > bestScore) {
            bestScore = result;
            bestMove = move;
        }
    }

    return static_cast<int>(bestMove);
}