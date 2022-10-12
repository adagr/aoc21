#include "day.hpp"
#include <stack>

class Day24 : public Day {

public:
    Day24() : Day{"input/day24.txt"} {}
    ~Day24() override = default;

    void run() override {
        //     1  2  3  4  5  6  7  8  9 10 11 12 13 14
        //p1 [ 1  1  1  1 26  1  1 26  1 26 26 26 26 26]
        //p2 [15 11 10 12-11 11 14 -6 10 -6 -6-16 -4 -2]
        //p3 [ 9  1 11  3 10  5  0  7  9 15  4 10  4  9]

        // inp5 = inp4 + 3 - 11 = inp4 - 8
        // inp8 = inp7 + 0 - 6 = inp7 - 6
        // inp10 = inp9 + 9 - 6 = inp9 + 3
        // inp11 = inp6 + 5 - 6 = inp6 - 1
        // inp12 = inp3 + 11 - 16 = inp3 - 5
        // inp13 = inp2 + 1 - 4 = inp2 - 3
        // inp14 = inp1 + 9 - 2 = inp1 + 7

        // max = 29991993698469
        // min = 14691271141118

        struct Block {
            bool p1;
            int p2, p3;
            int index;
        };

        std::vector<Block> instructions{};
        Block b{};
        int index{};
        for (int i{1}; i < lines.size(); ++i) {
            if (i == 4 + i/18 * 18 || i == 5 + i/18 * 18 || i == 15 + i/18 * 18) {
                if (i == 4 + i/18 * 18) {
                    b.p1 = '1' == lines[i][6];
                } else if (i == 5 + i/18 * 18) {
                    b.p2 = std::stoi(lines[i].substr(6, lines[i].size() - 6));
                } else if (i == 15 + i/18 * 18) {
                    b.p3 = std::stoi(lines[i].substr(6, lines[i].size() - 6));
                    b.index = index;
                    ++index;
                    instructions.emplace_back(b);
                }
            }
        }

        std::stack<Block> blocks{};
        std::string serialNumberMax{"00000000000000"};
        std::string serialNumberMin{"00000000000000"};
        for (const auto& instruction : instructions) {
            if (instruction.p1) {
                blocks.emplace(instruction);
            } else {
                auto b = blocks.top();
                auto diff = b.p3 + instruction.p2;
                if (diff < 0) {
                    serialNumberMax[b.index] = '9';
                    serialNumberMax[instruction.index] = *std::to_string(9 + diff).c_str();
                    serialNumberMin[b.index] = *std::to_string(1 - diff).c_str();
                    serialNumberMin[instruction.index] = '1';
                } else {
                    serialNumberMax[b.index] = *std::to_string(9 - diff).c_str();
                    serialNumberMax[instruction.index] = '9';
                    serialNumberMin[b.index] = '1';
                    serialNumberMin[instruction.index] = *std::to_string(1 + diff).c_str();
                }
                blocks.pop();
            }
        }
        
        std::cout << serialNumberMax << std::endl << serialNumberMin;
    }

};