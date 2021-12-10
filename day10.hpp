#include "day.hpp"

class Day10 : public Day {

public:
    Day10() : Day{"input/day10.txt"} {}
    ~Day10() override = default;
    
    void run() override {
        // Part 1
        std::map<char, int> errorScoreMap{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
        std::set<char> openers{'(', '[', '{', '<'};
        int errorScore{};
        std::map<char, uint64_t> closingScoreMap{{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
        std::vector<uint64_t> closingScores{};
        for (const auto& line : lines) {
            std::vector<char> opened{};
            int startingScore = errorScore;
            for (const auto& c : line) {
                if (contains(openers, c))
                    opened.push_back(c);
                else {
                    if (closes(*opened.rbegin(), c))
                        opened.pop_back();
                    else {
                        errorScore += errorScoreMap[c];
                        break;
                    }
                }
            }

            // Part 2
            uint64_t closingScore{};
            if (startingScore == errorScore) {
                // incomplete line
                std::reverse(opened.begin(), opened.end());
                for (const auto& open : opened)
                    closingScore = closingScore * 5 + closingScoreMap[open];

                closingScores.emplace_back(closingScore);
            }
        }

        std::cout << errorScore << std::endl;
        std::sort(closingScores.begin(), closingScores.end());
        std::cout << *(closingScores.begin() + closingScores.size() / 2);
    }

    bool closes(const char& open, const char& close) {
        switch (open) {
        case '(':
            return close == ')';
        case '[':
            return close == ']';
        case '{':
            return close == '}';
        case '<':
            return close == '>';
        default:
            return false;
        }
    }

};