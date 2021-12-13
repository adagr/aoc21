#include "day.hpp"

class Day4 : public Day {

public:
    Day4() : Day{"input/day4.txt"} {}
    ~Day4() override = default;
    
    using Board = std::array<std::array<int, 5>, 5>;

    void run() override {
        // Part 1
        // Construct boards
        std::vector<Board> boards{};
        Board board{};
        int y{};
        for (int i{2}; i < lines.size(); ++i) {
            if (y == 5) {
                boards.push_back(board);
                y = 0;
                continue;
            }

            int x{};
            auto lineNumbers = getNumbersInLine(lines[i], ' ');
            for (int j{}; j < lineNumbers.size(); ++j) {
                board[y][x] = lineNumbers[j];
                ++x;
            }
            
            ++y;
        }

        boards.push_back(board);
        // find first bingo of each board
        auto bingoNumbers = getNumbersInLine(0, ',');
        std::vector<int> firstBingos{};
        for (int i{}; i < boards.size(); ++i) {
            auto& board = boards[i];
            for (int j{}; j < bingoNumbers.size(); ++j) {
                drawNumber(board, bingoNumbers[j]);
                if (j >= 5) {
                    if (checkBingo(board)) {
                        firstBingos.emplace_back(j);
                        break;
                    }
                }
            }

            //if the board doesn't have bingo
            if (firstBingos.size() == i)
                firstBingos.emplace_back(-1);
        }

        // find winning board
        auto firstBingo{bingoNumbers.size()};
        int winningBoard{};
        for (int i{}; i < firstBingos.size(); ++i) {
            if (firstBingos[i] < firstBingo) {
                firstBingo = firstBingos[i];
                winningBoard = i;
            }
        }

        std::cout << getBoardSum(boards[winningBoard]) * bingoNumbers[firstBingo] << std::endl;

        // Part 2
        // find losing board
        int lastBingo{}, losingBoard{};
        for (int i{}; i < firstBingos.size(); ++i) {
            if (firstBingos[i] > lastBingo) {
                lastBingo = firstBingos[i];
                losingBoard = i;
            }
        }

        std::cout << getBoardSum(boards[losingBoard]) * bingoNumbers[lastBingo] << std::endl;
    }

    void drawNumber(Board& board, int number) {
        for (int y{}; y < 5; ++y) {
            for (int x{}; x < 5; ++x) {
                if (board[y][x] == number) {
                    board[y][x] = -1;
                    return;
                }
            }
        }
    }

    bool checkBingo(const Board& board) {
        std::array<int, 5> columns{}, rows{};
        for (int y{}; y < 5; ++y) {
            for (int x{}; x < 5; ++x) {
                if (board[y][x] == -1) {
                    columns[x] += 1;
                    rows[y] += 1;
                }
            }
        }

        for (const auto& column : columns)
            if (column == 5)
                return true;

        for (const auto& row : rows)
            if (row == 5)
                return true;

        return false;
    }

    int getBoardSum(const Board& board) {
        int boardSum{};
        for (int y = 0; y < 5; ++y)
            for (int x{}; x < 5; ++x)
                if (board[y][x] != -1)
                    boardSum += board[y][x];

        return boardSum;
    }

};