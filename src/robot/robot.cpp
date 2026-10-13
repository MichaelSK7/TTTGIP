/*
    AI WAS USED IN THIS DOCUMENT
*/

#include "robot.hpp"
#include "types/piece.hpp"

#include <cstring>
#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace TTT;

bool robot::sendCommand(const std::string& cmd) {
    std::string formatted = cmd + "\r\n";

    ssize_t sent = send(sock, formatted.c_str(), formatted.length(), MSG_NOSIGNAL);

    if (sent < 0) {
        std::cerr << "Send failed: " << strerror(errno) << '\n';
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    char buffer[1024] = {};
    ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);

    if (received > 0) {
        buffer[received] = '\0';
        std::cout << "Robot: " << buffer << '\n';
    }

    return true;
}

bool robot::connectToRobot(const std::string& ip) {
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << '\n';
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(23);

    if (inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid IPv4 address\n";
        close(sock);
        sock = -1;
        return false;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed: " << strerror(errno) << '\n';
        close(sock);
        sock = -1;
        return false;
    }

    std::cout << "TCP connection established.\n";

    // Read the initial greeting, if any.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    char buffer[512] = {};
    ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, MSG_DONTWAIT);

    if (received > 0) {
        buffer[received] = '\0';
        std::cout << "Robot: " << buffer << '\n';
    }

    // Do not send a password blindly until the controller's
    // actual login/prompt protocol has been confirmed.
    return true;
}

void robot::setPositionRegisterXYZ(int pr_num, double x, double y, double z) {
    sendCommand("SET VAR $PRG_GRP[1].$P_RET[" + std::to_string(pr_num) +
                "].$X = " + std::to_string(x));

    sendCommand("SET VAR $PRG_GRP[1].$P_RET[" + std::to_string(pr_num) +
                "].$Y = " + std::to_string(y));

    sendCommand("SET VAR $PRG_GRP[1].$P_RET[" + std::to_string(pr_num) +
                "].$Z = " + std::to_string(z));
}

void robot::setDataRegister(int r_num, int value) {
    sendCommand("SET VAR $NUMREG[" + std::to_string(r_num) + "] = " + std::to_string(value));
}

void robot::disconnect() {
    if (sock >= 0) {
        shutdown(sock, SHUT_RDWR);
        close(sock);
        sock = -1;
    }
}

bool robot::placeX(int slot) {
    std::string command = "PLACE_X" + std::to_string(slot) + "\n";
    return sendCommand(command);
}

bool robot::placeO(int slot) {
    std::string command = "PLACE_O" + std::to_string(slot) + "\n";
    return sendCommand(command);
}

robot::~robot() {
    disconnect();
}