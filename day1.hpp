#include "day.hpp"
#include <numeric>

class Day1 : public Day {

public:
    Day1() : Day{"input/day1.txt"} {}
    ~Day1() override = default;
    
    void run() override {
        int count{};
        const auto& linesInt{getLinesInt()};
        for (int i{1}; i < linesInt.size(); ++i)
            if (linesInt[i-1] < linesInt[i])
                ++count;

        std::cout << count << std::endl;

        count = 0;
        int previousSum = 100000;
        for (int i{2}; i < linesInt.size(); ++i) {
            auto sum = linesInt[i] + linesInt[i-1] + linesInt[i-2];
            if (previousSum < sum)
                ++count;

            previousSum = sum;
        }
        
        std::cout << count << std::endl;
    }

};