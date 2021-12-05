#include "day.hpp"
#include <map>

class Day5 : public Day {

public:
    Day5() : Day{"input/day5.txt"} {}
    ~Day5() override = default;
    
    void run() override {
        // Part 1
        std::map<std::pair<int, int>, int> points{};
        for (const auto& line : lines) {
            auto delim = line.find(" -> ");
            auto from = getCoords(line.substr(0, delim));
            auto to = getCoords(line.substr(delim+4, line.size()-delim-4));
            if (from.first == to.first || from.second == to.second) { //straight line
                for (auto x = std::min(from.first, to.first); x <= std::max(from.first, to.first); ++x)
                    for (auto y = std::min(from.second, to.second); y <= std::max(from.second, to.second); ++y)
                        points[std::make_pair(x, y)] += 1;
            } else { // 45° diagonal line
                // Part 2
                auto x = from.first;
                auto y = from.second;
                auto xDir = (to.first - from.first) / std::abs(to.first - from.first);
                auto yDir = (to.second - from.second) / std::abs(to.second - from.second);
                for (int i{}; i <= std::abs(from.first - to.first); ++i) {
                    points[std::make_pair(x, y)] += 1;
                    x += xDir;
                    y += yDir;
                }
            }
        }

        int counter{};
        for (const auto& point : points)
            counter += point.second > 1;

        std::cout << counter << std::endl;
    }

    std::pair<int, int> getCoords(std::string s) {
        auto delim = s.find(',');
        return std::make_pair(std::stoi(s.substr(0, delim)), std::stoi(s.substr(delim+1, s.size()-delim-1)));
    }

};