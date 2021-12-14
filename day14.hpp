#include "day.hpp"

class Day14 : public Day {

public:
    Day14() : Day{"input/day14.txt"} {}
    ~Day14() override = default;
    
    void run() override {
        std::unordered_map<std::string, uint64_t> polymer{}, polymerNew{};
        for (int i{}; i < lines[0].size() - 1; ++i)
            polymer.emplace(lines[0].substr(i, 2), 1);

        std::unordered_map<std::string, std::string> table{};
        for (int i{2}; i < lines.size(); ++i) {
            const auto& line = lines[i];
            auto delim = line.find(" -> ");
            table.emplace(line.substr(0, delim), line.substr(delim + 4, 1));
        }

        std::map<std::string, uint64_t> quantity{};
        for (const auto& c : lines[0])
            ++quantity[std::string{c}];

        for (int i{}; i < 40; ++i) {
            for (const auto& p : polymer) {
                auto newChar = table[p.first];
                quantity[newChar] += p.second;
                polymerNew[p.first[0] + newChar] += p.second;
                polymerNew[newChar + p.first[1]] += p.second;
            }

            polymer = polymerNew;
            polymerNew.clear();
        }

        std::set<uint64_t> values{};
        for (const auto& q : quantity)
            values.emplace(q.second);
        
        std::cout << *values.rbegin() - *values.begin() << std::endl;
    }

};