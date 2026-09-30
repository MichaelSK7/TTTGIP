#include "save.hpp"

#include <iostream>

TTT::GameSave::GameSave() {
    savePath = "gameSaves.txt";
}

TTT::GameSave::GameSave(std::filesystem::path customSavePath) {
    savePath = customSavePath;
}

void TTT::GameSave::save(TTT::Board& board) {
    output.open(savePath);

    if (!output.is_open()) {
        std::cerr << "Could not open save file!\n";
    }

    for (size_t r = 0; r < 3; r++) {
        for (size_t c = 0; c < 3; c++) {
            board << valueToChar(currentBoard[r][c]) << ' ';
        }
        std::cout << '\n';
    }
}