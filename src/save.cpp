#include "save.hpp"

#include <filesystem>
#include <iostream>

TTT::GameSave::GameSave() {
    std::filesystem::path savesDirPath = "saves";
    std::filesystem::create_directories(savesDirPath);
    savePath = std::filesystem::path("saves/gameSaves.txt");
}

TTT::GameSave::GameSave(std::filesystem::path customSavePath) {
    savePath = customSavePath;
}

void TTT::GameSave::saveBoard(TTT::Board board) {
    saveFile.open(savePath);
    if (!saveFile.is_open()) {
        std::cerr << "Could not open save file!\n";
    }

    saveFile << board.getCurrentBoardAsString();
}