#include "day.hpp"

class Day8 : public Day {

public:
    Day8() : Day{"input/day8.txt"} {}
    ~Day8() override = default;
    
    void run() override {
        // Part 1
        std::vector<std::vector<std::string>> inputs{}, outputs{};
        for (const auto& line : lines) {
            auto delim = line.find(" | ");
            auto inputLine = line.substr(0, delim);
            auto outputLine = line.substr(delim + 3, line.size() - delim - 3);
            auto input = getFromLine(inputLine, " ");
            for (auto& i : input)
                std::sort(i.begin(), i.end());
            inputs.emplace_back(input);
            auto output = getFromLine(outputLine, " ");
            for (auto& o : output)
                std::sort(o.begin(), o.end());
            outputs.emplace_back(output);
        }

        int sum{};
        for (const auto& output : outputs) {
            sum += std::count_if(output.begin(), output.end(), [](const std::string& s){
                auto size = s.size();
                return size == 2 || size == 3 || size == 4 || size == 7;
            });
        }

        std::cout << sum << std::endl;

        // Part 2
        sum = 0;
        for (int line{}; line < inputs.size(); ++line) {
            auto& input = inputs[line];
            std::array<std::string, 10> numbers{};
            for (auto it = input.begin(); it != input.end();) {
                auto& i = *it;
                switch (i.size()) {
                    case 2: // 1
                        numbers[1] = i;
                        it = input.erase(it);
                        break;
                    case 3: // 7
                        numbers[7] = i;
                        it = input.erase(it);
                        break;
                    case 4: // 4
                        numbers[4] = i;
                        it = input.erase(it);
                        break;
                    case 7: // 8
                        numbers[8] = i;
                        it = input.erase(it);
                        break;
                    default:
                        ++it;
                        break;
                }
            }

            // 1 -> 3
            findNumber(input, numbers, 1, 3, 5, 1.0f);
            // 3 -> 9
            findNumber(input, numbers, 3, 9, 6, 1.0f);
            // 4 -> 5(3/4 match)
            findNumber(input, numbers, 4, 5, 5, 0.75f);
            // 7 -> 0
            findNumber(input, numbers, 7, 0, 6, 1.0f);
            // 2 && 6
            if (input[0].size() == 5) {
                numbers[2] = input[0];
                numbers[6] = input[1];
            } else {
                numbers[2] = input[1];
                numbers[6] = input[0];
            }

            int value{};
            int multiplier = 1000;
            for (const auto& output : outputs[line]) {
                for (int i{}; i < numbers.size(); ++i) {
                    if (output == numbers[i]) {
                        value += i * multiplier;
                        multiplier /= 10;
                        break;
                    }
                }
            }

            sum += value;
        }

        std::cout << sum;
    }

    void findNumber(std::vector<std::string>& input, std::array<std::string, 10>& numbers,  int fromNumber, int toNumber, int size, float matchPercent) {
        for (auto it = input.begin(); it != input.end(); ++it) {
            auto& i = *it;
            float match = 1.0f;
            for (const auto& c : numbers[fromNumber])
                if (i.size() != size || i.find(c) == std::string::npos)
                    match -= 1.0f / numbers[fromNumber].size();

            if (match >= matchPercent) {
                numbers[toNumber] = i;
                input.erase(it);
                break;
            }
        }
    }
};