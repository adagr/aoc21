#include "day.hpp"

class Day9 : public Day {

public:
    Day9() : Day{"input/day9.txt"} {}
    ~Day9() override = default;
    
    void run() override {
        // Part 1
        std::array<std::array<int, 100>, 100> grid{};
        std::vector<std::pair<int, int>> lowPoints{};
        for (int y{}; y < lines.size(); ++y)
            for (int x{}; x < lines[y].size(); ++x)
                grid[y][x] = lines[y][x] - '0';

        int sum{};
        for (int y{}; y < grid.size(); ++y) {
            for (int x{}; x < grid[y].size(); ++x) {
                const auto& value = grid[y][x];
                bool lowPoint{true};
                lowPoint &= (0 < x && value < grid[y][x - 1]) || x == 0;
                lowPoint &= (x < grid[y].size() - 1 && value < grid[y][x + 1]) || x == grid[y].size() - 1;
                lowPoint &= (0 < y && value < grid[y - 1][x]) || y == 0;
                lowPoint &= (y < grid.size() - 1 && value < grid[y + 1][x]) || y == grid.size() - 1;
                sum += lowPoint * (value + 1);
                if (lowPoint)
                    lowPoints.emplace_back(std::make_pair(y, x));
            }
        }

        std::cout << sum << std::endl;

        // Part 2
        std::vector<int> basins{};
        for (const auto& lowPoint : lowPoints) {
            std::vector<std::pair<int, int>> locationsToSearch{}, visitedLocations{};
            locationsToSearch.push_back(lowPoint);
            int sumLocations{};
            while(!locationsToSearch.empty()) {
                int y = locationsToSearch.front().first;
                int x = locationsToSearch.front().second;
                auto searched = std::find_if(visitedLocations.begin(), visitedLocations.end(), [&](const std::pair<int, int> location){ 
                    return y == location.first && x == location.second;
                });
                if (grid[y][x] < 9 && searched == visitedLocations.end()) {
                    ++sumLocations;
                    // add adjecent locations
                    if (0 < y)
                        locationsToSearch.push_back(std::make_pair(y - 1, x));
                    if (y < grid.size() - 1)
                        locationsToSearch.push_back(std::make_pair(y + 1, x));
                    if (0 < x)
                        locationsToSearch.push_back(std::make_pair(y, x - 1));
                    if (x < grid[y].size() - 1)
                        locationsToSearch.push_back(std::make_pair(y, x + 1));
                }

                visitedLocations.push_back(locationsToSearch.front());
                locationsToSearch.erase(locationsToSearch.begin());
            }

            basins.emplace_back(sumLocations);
        }

        std::sort(basins.rbegin(), basins.rend());
        std::cout << basins[0] * basins[1] * basins[2];
    }

};