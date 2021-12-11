#include "day.hpp"

class Day11 : public Day {

public:
    Day11() : Day{"input/day11.txt"} {}
    ~Day11() override = default;
    
    void run() override {
        std::array<std::array<int, 10>, 10> grid{};
        for (int y{}; y < 10; ++y)
            for (int x{}; x < 10; ++x)
                grid[y][x] = lines[y][x] - '0';

        int flashes{}, totalFlashes{};
        int steps{};
        // Part 2
        while (flashes < 100) {
            for (int y{}; y < 10; ++y)
                for (int x{}; x < 10; ++x)
                    checkFlashed(grid, x, y, flashes);
            
            for (int y{}; y < 10; ++y)
                for (int x{}; x < 10; ++x)
                    grid[y][x] = grid[y][x] * (grid[y][x] < 10);
                    //if (grid[y][x] > 9)
                    //    grid[y][x] = 0;

            // Part 1
            if (steps == 100)
                std::cout << totalFlashes << std::endl;

            ++steps;
            totalFlashes += flashes;
            flashes = 0;
        }
        
        std::cout << steps;
    }

    void checkFlashed(std::array<std::array<int, 10>, 10>& grid, int x, int y, int& flashes) {
        if (++grid[y][x] == 10) {
            ++flashes;
            flashAdjecent(grid, x - 1, y - 1, flashes);
        }
    }

    void flashAdjecent(std::array<std::array<int, 10>, 10>& grid, int startX, int startY, int& flashes) {
        for (int y = std::max(startY, 0); y < std::min(std::max(startY + 3, 0), 10); ++y)
            for (int x = std::max(startX, 0); x < std::min(std::max(startX + 3, 0), 10); ++x)
                checkFlashed(grid, x, y, flashes);
    }

};