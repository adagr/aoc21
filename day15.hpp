#include "day.hpp"
#include <queue>

class Day15 : public Day {

public:
    Day15() : Day{"input/day15.txt"} {}
    ~Day15() override = default;
    
    void run() override {
        std::array<std::array<std::pair<int, int>, 500>, 500> grid{};
        std::deque<std::pair<int, int>> nodes{};
        for (int y{}; y < grid.size(); ++y) {
            for (int x{}; x < grid[y].size(); x++) {
                if (x < lines[0].size() && y < lines.size())
                    grid[y][x] = std::make_pair(lines[y][x] - '0', INT_MAX);
                else {
                    int posX, posY{};
                    if (x < lines[0].size()) {
                        posX = x;
                        posY = y - lines.size();
                    } else {
                        posX = x - lines[0].size();
                        posY = y;
                    }

                    auto value = grid[posY][posX].first;
                    value = value * (value < 9) + 1;
                    grid[y][x] = std::make_pair(value, INT_MAX);
                }

            }
        }

        nodes.emplace_back(std::make_pair(0, 0));
        grid[0][0].second = 0;

        while(!nodes.empty()) {
            const auto& node = nodes.front();
            auto cost = grid[node.first][node.second].second;
            updateNeighbour(grid, nodes, node.first, node.second - 1, cost);
            updateNeighbour(grid, nodes, node.first, node.second + 1, cost);
            updateNeighbour(grid, nodes, node.first - 1, node.second, cost);
            updateNeighbour(grid, nodes, node.first + 1, node.second, cost);
            nodes.pop_front();
        }

        std::cout << grid[grid.size() - 1][grid[0].size() - 1].second << std::endl;
    }

    void updateNeighbour(std::array<std::array<std::pair<int, int>, 500>, 500>& grid, std::deque<std::pair<int, int>>& nodes, int y, int x, int cost) {
        if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size())
            return;

        const auto& travelCost = grid[y][x].first;
        auto& nodeCost = grid[y][x].second;
        auto newCost = cost + travelCost;
        if (newCost < nodeCost) {
            nodeCost = newCost;
            auto node = std::make_pair(y, x);
            auto it = std::find(nodes.begin(), nodes.end(), node);
            if (it == nodes.end())
                nodes.emplace_back(node);
        }
    }

};