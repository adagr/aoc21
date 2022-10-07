#include "day.hpp"

class Day22 : public Day {

public:
    Day22() : Day{"input/day22.txt"} {}
    ~Day22() override = default;

    struct Cuboid {
        int xMin, xMax, yMin, yMax, zMin, zMax;
        int power;

        bool operator==(const Cuboid& cube) const {
            return cube.xMin == xMin && cube.xMax == xMax && 
                    cube.yMin == yMin && cube.yMax == yMax && 
                    cube.zMin == zMin && cube.zMax == zMax && 
                    cube.power == power;
        }
    };
    
    void run() override {
        // Part 1
        std::map<int, std::map<int, std::map<int, int>>> reactor{};
        std::vector<Cuboid> cubes{};
        for (const auto& line : lines) {
            int power = line.substr(0, line.find(' ')) == "on" ? 1 : 0;
            auto substrings = getFromLine(line, "=");
            int xMin = std::stoi(substrings[1].substr(0, substrings[1].find("..")));
            int xMax = std::stoi(substrings[1].substr(substrings[1].find("..") + 2, substrings[1].size() - substrings[1].find("..") + 2));
            int yMin = std::stoi(substrings[2].substr(0, substrings[2].find("..")));
            int yMax = std::stoi(substrings[2].substr(substrings[2].find("..") + 2, substrings[2].size() - substrings[2].find("..") + 2));
            int zMin = std::stoi(substrings[3].substr(0, substrings[3].find("..")));
            int zMax = std::stoi(substrings[3].substr(substrings[3].find("..") + 2, substrings[3].size() - substrings[3].find("..") + 2));
            cubes.emplace_back(Cuboid{xMin, xMax, yMin, yMax, zMin, zMax, power});

            for (int i{std::max(xMin, -50)}; i <= std::min(xMax, 50); ++i)
                for (int j{std::max(yMin, -50)}; j <= std::min(yMax, 50); ++j)
                    for (int k{std::max(zMin, -50)}; k <= std::min(zMax, 50); ++k)
                        reactor[i][j][k] = power;
        }

        int count{};
        for (const auto& x : reactor)
            for (const auto& y : x.second)
                for (const auto& z : y.second)
                    count += z.second;

        std::cout << count << std::endl;

        // Part 2
        for (const auto& cube : cubes) {
            
        }
    }

};