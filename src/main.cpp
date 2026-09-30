#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct boardData {
    // position data
    std::pair<int, char[3][3]> moves;
};

struct TTTGameData {
    char gameWinner;
    std::vector<char> d;
};

class TicTacToe {
  private:
    char input;

  public:
    TicTacToe() {
        clear();
    }

    void start() {
        while (true) {
            char beginner;

            std::cout << "Enter e to exit. \nWho begins?\nx or o\n";
            beginner = askForInput();

            std::cout << beginner << " BEGINS!!!\n";

            askForInput();

            switch (input) {
            case 'x':
                clear();
                std::cout << "x's turn!\n";
                break;

            case 'o':
                clear();
                std::cout << "o's turn!\n";
                break;
            }
        }
    }

    void displayClearBoard() {
        const int rows = 3;
        const int cols = 3;

        std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, ' '));

        std::cout << "\n";
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                std::cout << " " << grid[r][c] << " ";
                if (c < cols - 1) {
                    std::cout << "|";
                }
            }
            std::cout << "\n";

            if (r < rows - 1) {
                std::cout << std::string(cols * 4 - 1, '-') << "\n";
            }
        }
    }

    char askForInput() {
        while (true) {
            std::cin >> input;

            switch (input) {
            case 'x':
                return 'x';
                break;
            case 'o':
                return 'o';
                break;
            case 'e':
                exit(1);
                break;
            default:
                std::cout << "Invalid input. Choose either 'x' or 'o'!\n";
                continue;
            }

            break;
        }
    };

    void clear() {
        std::cout << "\x1B[2J\x1B[H";
    }
};

int main() {
    TicTacToe ob;
}