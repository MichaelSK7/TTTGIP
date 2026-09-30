#pragma once

#include "board.hpp"

#include <filesystem>
#include <fstream>

namespace TTT {
class GameSave {
  private:
    std::filesystem::path savePath;
    std::ofstream output;

  public:
    GameSave();
    GameSave(std::filesystem::path customSavePath);

    void save(TTT::Board& board);
};
} // namespace TTT
