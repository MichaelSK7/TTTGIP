#pragma once

#include "board.hpp"

#include <filesystem>
#include <fstream>

namespace TTT {
class GameSave : Board {
  private:
    std::filesystem::path savePath;
    std::ofstream saveFile;
    std::filesystem::path savesDirPath;

  public:
    GameSave();
    GameSave(std::filesystem::path customSavePath);

    void saveBoard(TTT::Board board);
};
} // namespace TTT
