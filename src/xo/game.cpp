#include "xo/game.hpp"
#include "robot/robot.hpp"
#include "types/difficulty.hpp"

#include <iostream>

TTT::Game::Game() {
    startGame();
}

void TTT::Game::startGame() {
    TTT::Board board;
    TTT::AI ai;
    TTT::robot robot;
    bool isRunning = true;
    char input;
    char playerPiece;

    welcomeMessage();

    // Replace with actual configured robot ip
    // if (!robot.connectToRobot("10.150.6.27")) {
    //     std::cerr << "Connection failed!\n";
    //     return;
    // }

    // Diff is not bound check. Will be done later.
    int diff;
    std::cout << "What difficulty do you want the AI to be?\n";

    std::cin >> diff;

    switch (diff) {
    case 1:
        ai.setDifficulty(Difficulty::EASY);
        break;
    case 2:
        ai.setDifficulty(Difficulty::MEDIUM);
        break;
    case 3:
        ai.setDifficulty(Difficulty::HARD);
        break;
    case 4:
        ai.setDifficulty(Difficulty::IMPOSSIBLE);
        break;
    }

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
        // X PATH
        std::cout << "You begin!\n";
        board.showBoard();
        std::cout << '\n';

        while (isRunning) {
            // Player
            int playerChoice = playerTurn(board);

            robot.placeX(playerChoice);

            if (board.gameOver()) {
                std::cout << "Game over TEST!\n";
                return;
            };

            // AI
            std::cout << "AI's move:\n";
            int aiChoice = ai.AIMove(board);
            totalPlayedMoves++;
            board.showBoard();

            robot.placeO(aiChoice);

            if (board.gameOver()) {
                std::cout << "Game over! TEST\n";
                return;
            };

            std::cout << '\n';
        }
    } else {
        // O PATH
        std::cout << "AI begins!\n";
        while (isRunning) {
            // AI
            std::cout << "AI's move:\n";
            int aiChoice = ai.AIMove(board);

            board.showBoard();

            robot.placeX(aiChoice);

            if (board.gameOver()) {
                std::cout << "Game over!\n";
                return;
            };

            std::cout << '\n';

            // Player
            std::cout << "Your turn!\n";
            int choice = playerTurn(board);
            totalPlayedMoves++;

            robot.placeO(choice);

            if (board.gameOver()) {
                std::cout << "Game over!\n";
                return;
            };

            std::cout << '\n';
        }
    }
}

int TTT::Game::playerTurn(TTT::Board& board) {
    while (true) {
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "QUIT\n";
            exit(0);

        } else if (choice < 1 || choice > 9) {
            std::cout << "Please enter a valid number.\n";
        }

        if (!(board.place(choice, board.getPlayerPiece()))) {
            board.showBoard();
            continue;
        };

        board.showBoard();
        return choice;
    }
}

// misc
void TTT::Game::welcomeMessage() {
    std::cout << "Welcome to our TicTacToe project.\n";
}

void TTT::Game::startMessage() {
    std::cout << "Who are you going to play?\n X or O\n";
}
