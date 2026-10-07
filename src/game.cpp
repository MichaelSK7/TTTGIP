#include "game.hpp"
#include <iostream>

TTT::Game::Game() {
    welcomeMessage();

    // Diff is not bound check. Will be done later.
    int diff;
    std::cout << "What difficulty do you want the AI to be?\n";

    std::cin >> diff;

    switch (diff) {
    case 1:
        gameDiff = Difficulty::EASY;
        break;
    case 2:
        gameDiff = Difficulty::MEDIUM;
        break;
    case 3:
        gameDiff = Difficulty::HARD;
        break;
    case 4:
        gameDiff = Difficulty::IMPOSSIBLE;
        break;
    }

    startGame();
}

void TTT::Game::startGame() {
    TTT::Board board;
    TTT::AI ai;
    bool isRunning = true;
    char input;
    char playerPiece;

    startMessage();

    while (true) {
        std::cin >> playerPiece;

        switch (playerPiece) {
        case 'x':
            board.setPlayerPiece(Piece::x);
            std::cout << "You start as x!\n";
            break;

        case 'X':
            board.setPlayerPiece(Piece::x);
            std::cout << "You start as x!\n";
            break;

        case 'o':
            board.setPlayerPiece(Piece::o);
            std::cout << "You start as o!\n";
            break;

        case 'O':
            board.setPlayerPiece(Piece::o);
            std::cout << "You start as o!\n";
            break;

        default:
            std::cout << "Please enter a valid piece!\n";
            continue;
        }
        break;
    }

    std::cout << "You will have to choose numbers between 1-9.\n";

    if (board.getPlayerPiece() == Piece::x) {
        std::cout << "You begin!\n";
        board.showBoard();
        std::cout << '\n';

        while (isRunning) {
            playerTurn(board);

            // AI
            std::cout << "AI's move:\n";
            ai.AIMove(board);
            board.showBoard();
            if (board.gameOver()) {
                std::cout << "Game over!\n";
                break;
            };
            std::cout << '\n';
        }
    } else {
        std::cout << "AI begins!\n";
        while (isRunning) {
            // AI
            std::cout << "AI's move:\n";
            ai.AIMove(board);
            if (board.gameOver()) {
                std::cout << "Game over!\n";
                break;
            };
            board.showBoard();
            std::cout << '\n';

            std::cout << "Your turn!\n";
            playerTurn(board);
            std::cout << '\n';
        }
    }
}

void TTT::Game::playerTurn(TTT::Board& board) {
    while (true) {
        int c;
        std::cin >> c;

        if (c == 0) {
            std::cout << "QUIT\n";
            exit(0);

        } else if (c < 1 || c > 9) {
            std::cout << "Please enter a valid number.\n";
        }

        // Player
        if (!(board.place(c, board.getPlayerPiece()))) {
            continue;
        };

        board.showBoard();

        if (board.gameOver()) {
            std::cout << "Game over!\n";
            break;
        };

        break;
    }
}

// misc
void TTT::Game::welcomeMessage() {
    std::cout << "Welcome to our TicTacToe project.\n"
              << "Press enter to start the game!\n";
}

void TTT::Game::startMessage() {
    std::cout << "Who are you going to play?\n X or O\n";
}
