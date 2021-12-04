#include "day.hpp"
#include <array>

class Day3 : public Day {

public:
    Day3() : Day{"input/day3.txt"} {}
    ~Day3() override = default;
    
    void run() override {
        // Part 1
        std::array<int, 12> numInts{};
        for (const auto& line : lines)
            for (int i{}; i < line.size(); ++i)
                numInts[i] += line[i] == '1' ? 1 : 0;

        uint16_t gamma{}, epsilon{};
        for (int i{}; i < 12; ++i)
            gamma |= numInts[i] * 2 > lines.size() ? (1 << (11 - i)) : 0;

        epsilon = ~gamma;
        epsilon &= 0x0FFF;
        std::cout << gamma * epsilon << std::endl;
        
        // Part 2
        std::cout << static_cast<uint32_t>(getRating(true)) * static_cast<uint32_t>(getRating(false));
    }

    uint16_t getRating(bool mostCommon) {
        std::vector<std::string> zeroes{}, ones{};
        std::vector<std::string> remainingLines = lines;
        for (int i{}; i < 12; ++i) {
            for (const auto& line : remainingLines) {
                if (line[i] == '1') {
                    ones.emplace_back(line);
                } else
                    zeroes.emplace_back(line);
            }

            if (ones.size() * 2 >= remainingLines.size())
                remainingLines = mostCommon ? ones : zeroes;
            else
                remainingLines = mostCommon ? zeroes : ones;

            if (remainingLines.size() == 1)
                break;

            ones.clear();
            zeroes.clear();
        }

        uint16_t result{};
        for (int i{}; i < 12; ++i)
            result |= remainingLines[0][i] == '1' ? (1 << (11 - i)) : 0;

        return result;
    }

};