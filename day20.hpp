#include "day.hpp"

class Day20 : public Day {

public:
    Day20() : Day{"input/day20.txt"} {}
    ~Day20() override = default;
    
    void run() override {
        std::string alg = lines[0];
        std::unordered_map<int, std::unordered_map<int, int>> input{};
        int iterations = 50;
        for (int i{2}; i < lines.size(); ++i)
            for (int j{}; j < lines[i].size(); ++j)
                input[i - 2 + iterations][j + iterations] = lines[i][j] == '#' ? 1 : 0;

        int border = 2;
        int numRows = lines.size() - 2 + 2 * iterations + 2 * border;
        int numColumns = lines[2].size() + 2 * iterations + 2 * border;
        for (int count{}; count < iterations; ++count) {
            std::unordered_map<int, std::unordered_map<int, int>> output{};
            for (int i{-border}; i < numRows; ++i) {
                for (int j{-border}; j < numColumns; ++j) {
                    int index{};
                    for (int row{i - 1}; row <= i + 1; ++row) {
                        for (int column{j - 1}; column <= j + 1; ++column) {
                            index = index << 1;
                            if (alg[0] == '#' && (row < -border || column < -border || row >= numRows || column >= numColumns))
                                //special case since the algorithm will flip the bits in the infinite field
                                index |= count % 2;
                            else
                                index |= input[row][column];
                        }
                    }
                    
                    output[i][j] = alg[index] == '#' ? 1 : 0;
                }
            }

            input = output;
        }

        int pixels{};
        for (int i{}; i <= lines.size() - 2 + 2 * iterations; ++i)
            for (int j{}; j <= lines[2].size() + 2 * iterations; ++j)
                pixels += input.at(i).at(j);

        std::cout << pixels << std::endl;
    }

};