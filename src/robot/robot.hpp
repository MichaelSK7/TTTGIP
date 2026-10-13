/*
    AI WAS USED IN THIS DOCUMENT
*/

#pragma once

#include <string>

namespace TTT {
class robot {
  private:
    int sock = -1;

  public:
    bool sendCommand(const std::string& cmd);
    bool connectToRobot(const std::string& ip);
    void setPositionRegisterXYZ(int pr_num, double x, double y, double z);
    void setDataRegister(int r_num, int value);
    void disconnect();

    bool placeX(int slot);
    bool placeO(int slot);

    ~robot();
};
} // namespace TTT
