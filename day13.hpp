#include "day.hpp"

class Day13 : public Day {

public:
    Day13() : Day{"input/day13.txt"} {}
    ~Day13() override = default;
    
    void run() override {
        // Part 1
        std::set<std::pair<int, int>> dots{};
        std::vector<std::pair<std::string, int>> instructions{};
        for (const auto& line : lines) {
            if (line.find("fold") != std::string::npos) {
                auto delim = line.find('=');
                instructions.emplace_back(std::make_pair(line.substr(delim-1, 1), std::stoi(line.substr(delim+1, line.size()-delim-1))));
            } else if (line != "") {
                auto dot = getNumbersInLine(line, ',');
                dots.emplace(std::make_pair(dot[1], dot[0]));
            }
        }

        for (const auto& instruction : instructions) {
            std::set<std::pair<int, int>> dotsNew{};
            for (auto it = dots.begin(); it != dots.end();) {
                auto& dot = *it;
                ++it;
                if (instruction.first == "y") {
                    if (dot.first > instruction.second) {
                        dotsNew.emplace(std::make_pair(instruction.second * 2 - dot.first, dot.second));
                        it = dots.erase(--it);
                    }
                } else { // x
                    if (dot.second > instruction.second) {
                        dotsNew.emplace(std::make_pair(dot.first, instruction.second * 2 - dot.second));
                        it = dots.erase(--it);
                    }
                }
            }

            dots.insert(dotsNew.begin(), dotsNew.end());
            std::cout << dots.size() << std::endl;
        }

        // Part 2
        int lastRow{};
        int lastColumn{};
        for (const auto& dot : dots) {
            if (dot.first > lastRow) {
                std::cout << std::endl;
                lastColumn = -1;
                ++lastRow;
            }

            for (int i{}; i < dot.second - lastColumn - 1; ++i)
                std::cout << " ";
            
            lastColumn = dot.second;
            std::cout << "#";
        }
    }

};