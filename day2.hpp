#include "day.hpp"

class Day2 : public Day {

public:
    Day2() : Day{"input/day2.txt"} {}
    ~Day2() override = default;
    
    void run() override {
        // Part 1
        std::vector<std::pair<std::string, int>> inputs{};
        for (const auto& line : lines) {
            auto delim = line.find(' ');
            auto input = std::make_pair(line.substr(0,delim), std::stoi(line.substr(delim+1, line.size() - delim)));
            inputs.emplace_back(input);
        }

        int x{}, y{};
        for (const auto& input : inputs) {
            if (input.first == "forward")
                x += input.second;
            else if (input.first == "down")
                y += input.second;
            else if (input.first == "up")
                y -= input.second;
        }

        std::cout << x * y << std::endl;
        
        // Part 2
        x = 0;
        y = 0;
        int aim{};
        for (const auto& input : inputs) {
            if (input.first == "forward") {
                x += input.second;
                y += aim * input.second;
            } else if (input.first == "down")
                aim += input.second;
            else if (input.first == "up")
                aim -= input.second;
        }

        std::cout << x * y;
    }

};