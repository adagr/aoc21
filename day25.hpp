#include "day.hpp"
#include <unordered_set>

class Day25 : public Day {

public:
    Day25() : Day{"input/day25.txt"} {}
    ~Day25() override = default;
    
    struct HashFunction {
        size_t operator()(const std::pair<int, int> &x) const{
            return x.first ^ x.second;
        }
    };

    void run() override {
        int rows = lines.size();
        int columns = lines[0].size();
        std::unordered_set<std::pair<int, int>, HashFunction> east{};
        std::unordered_set<std::pair<int, int>, HashFunction> south{};
        for (int i{}; i < rows; ++i) {
            for (int j{}; j < columns; ++j) {
                if (lines[i][j] == '>')
                    east.emplace(std::make_pair(i,j));
                else if (lines[i][j] == 'v')
                    south.emplace(std::make_pair(i,j));
            }
        }

        int i{};
        while (true) {
            ++i;
            bool moved{};
            std::unordered_set<std::pair<int, int>, HashFunction> movedEast{};
            std::unordered_set<std::pair<int, int>, HashFunction> movedSouth{};
            for (const auto& sc : east) {
                auto newLoc = std::make_pair(sc.first, (sc.second + 1) % columns);
                if (east.find(newLoc) == east.end() && south.find(newLoc) == south.end()) {
                    movedEast.emplace(newLoc);
                    moved = true;
                } else
                    movedEast.emplace(sc);
            }

            east = std::move(movedEast);
            for (const auto& sc : south) {
                auto newLoc = std::make_pair((sc.first + 1) % rows, sc.second);
                if (east.find(newLoc) == east.end() && south.find(newLoc) == south.end()) {
                    movedSouth.emplace(newLoc);
                    moved = true;
                } else
                    movedSouth.emplace(sc);
            }

            south = std::move(movedSouth);
            if (!moved)
                break;
        }

        std::cout << i;
    }

};