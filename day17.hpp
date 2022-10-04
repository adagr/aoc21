#include "day.hpp"

class Day17 : public Day {

public:
    Day17() : Day{"input/day17.txt"} {}
    ~Day17() override = default;
    
    void run() override {
        auto input = getFromLine(lines[0], "=");
        int targetXMin = std::stoi(input[1].substr(0, input[1].find("..")));
        int targetXMax = std::stoi(input[1].substr(input[1].find("..")+2, input[1].find(',')));
        int targetYMin = std::stoi(input[2].substr(0, input[2].find("..")));
        int targetYMax = std::stoi(input[2].substr(input[2].find("..")+2, input[2].length()));
        int maxHeight{}, count{};
        for (int velX{}; velX < targetXMax+1; ++velX) {
            for (int velY{targetYMin}; velY < 500; ++velY) {
                int x{}, y{}, height{};
                for (int i{}; i < 500; ++i) {
                    x += std::max(velX - i, 0);
                    y += velY - i;
                    height = std::max(height, y);
                    if (x >= targetXMin && x <= targetXMax &&
                        y >= targetYMin && y <= targetYMax) {
                            ++count;
                            maxHeight = std::max(maxHeight, height);
                            break;
                        }
                }
            }
        }

        std::cout << maxHeight << std::endl;
        std::cout << count;
    }

};