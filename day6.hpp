#include "day.hpp"
#include <deque>

class Day6 : public Day {

public:
    Day6() : Day{"input/day6.txt"} {}
    ~Day6() override = default;
    
    void run() override {
        auto fish = getNumbersInLine(0, ',');
        std::deque<uint64_t> fishCount{0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (const auto& f : fish)
            fishCount[f] += 1;

        for (int i{}; i < 256; ++i) {
            auto amount = fishCount.front();
            fishCount.pop_front();
            fishCount.push_back(amount);
            fishCount[6] += amount;
        }

        auto sum = std::accumulate(fishCount.begin(), fishCount.end(), static_cast<uint64_t>(0));
        std::cout << sum;
    }

};