#include "AI.hpp"
#include "Board.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace TTT;

void AI::AIMove(TTT::Board& board) {
    bool maximizing;

    switch (board.getPlayerPiece()) {
    case Piece::x:
        AIPiece = Piece::o;
        maximizing = false;
        break;
    case Piece::o:
        AIPiece = Piece::x;
        maximizing = true;
        break;
    }

    board.setSlotValue(findBestMove(board, difficultyToInt(AIDifficulty), maximizing), AIPiece);
}

int AI::minimax(TTT::Board& thisBoard, int depth, int maxDepth, bool maximizing) {
    if (thisBoard.gameOver()) {
        return thisBoard.score(thisBoard, depth);
    }

    if (depth >= maxDepth) {
        return thisBoard.evaluate();
    }

    std::vector<int> scores;

    for (int move : thisBoard.getAvailableMoves()) {
        Piece player = maximizing ? Piece::x : Piece::o;

        thisBoard.forceSetSlotValue(move, player);

        int result = minimax(thisBoard, depth + 1, maxDepth, !maximizing);

        scores.push_back(result);

        thisBoard.forceSetSlotValue(move, Piece::None);
    }

    if (maximizing) {
        return *std::max_element(scores.begin(), scores.end());
    } else {
        return *std::min_element(scores.begin(), scores.end());
    }
}

int AI::findBestMove(TTT::Board& board, int maxDepth, bool& maximizing) {
    int bestScore = maximizing ? -1000 : 1000;
    int bestMove = -1;

    for (int move : board.getAvailableMoves()) {
        board.forceSetSlotValue(move, AIPiece);

        int result = minimax(board, 1, maxDepth, !maximizing);

        board.forceSetSlotValue(move, Piece::None);

        if ((maximizing && result > bestScore) || (!maximizing && result < bestScore)) {
            bestScore = result;
            bestMove = move;
        }
    }

    return bestMove;
}

int AI::difficultyToInt(Difficulty diff) {
    switch (diff) {
    case Difficulty::EASY:
        return 1;
    case Difficulty::MEDIUM:
        return 3;
    case Difficulty::HARD:
        return 5;
    case Difficulty::IMPOSSIBLE:
        return 9;
    }
    return 1;
};

void AI::setDifficulty(Difficulty diff) {
    AIDifficulty = diff;
};