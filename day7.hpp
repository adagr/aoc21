#include "day.hpp"

class Day7 : public Day {

public:
    Day7() : Day{"input/day7.txt"} {}
    ~Day7() override = default;
    
    void run() override {
        auto input = getNumbersInLine(0, ',');
        std::map<int, int> positions{};
        for (const auto& i : input)
            positions[i] += 1;

        std::set<int> possibleFuelAmount{};
        for (int i{(*positions.begin()).first}; i < (*positions.end()).first; ++i) {
            int fuelAmount{};
            for (const auto& pos : positions) {
                // Part 1
                //fuelAmount += std::abs(pos.first - i) * pos.second;
                // Part 2
                auto n = std::abs(pos.first - i);
                fuelAmount += ((n * n + n) / 2) * pos.second;
                
            }

            possibleFuelAmount.insert(fuelAmount);
        }

        std::cout << *possibleFuelAmount.begin();

    }

};