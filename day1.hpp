#include "day.hpp"
#include <numeric>

class Day1 : public Day {

public:
    Day1() : Day{"input/day1.txt"} {}
    ~Day1() override = default;
    
    void run() override {
        // Part 1
        int count{};
        const auto& linesInt{getLinesInt()};
        for (int i{1}; i < linesInt.size(); ++i)
            if (linesInt[i-1] < linesInt[i])
                ++count;

        std::cout << count << std::endl;

        // Part 2
        count = 0;
        int previousSum = 100000;
        for (auto it = linesInt.begin(); it < linesInt.end()-2; ++it) {
            auto sum = std::accumulate(it, it+3, 0);
            if (previousSum < sum)
                ++count;

            previousSum = sum;
        }
        
        std::cout << count << std::endl;
    }

};