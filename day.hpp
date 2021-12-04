#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <array>

class Day {

public:
    explicit Day(std::string fileName) {
        lines.clear();
        std::ifstream input{fileName};
        std::string line;
        for (std::string line; std::getline(input, line);)
            lines.emplace_back(line);
    }
    virtual ~Day() = default;

    virtual void run() = 0;

protected:
    void printLines() {
        for(const auto& line : lines)
            std::cout << line << std::endl;
    }

    std::vector<int> getLinesInt() {
        std::vector<int> linesInt{};
        for (const auto& line : lines)
            linesInt.emplace_back(std::stoi(line));

        return linesInt;
    }

    std::vector<int> getNumbersInLine(int line, char delim) {
        //delim needs to be char for day4
        std::vector<int> numbers{};
        auto s = lines[line];
        while(true) {
            while (s[0] == delim) {
                s = s.erase(0, 1);
            }
            auto pos = s.find(delim);
            if (pos == std::string::npos) {
                numbers.emplace_back(std::stoi(s));
                break;
            }
                
            numbers.emplace_back(std::stoi(s.substr(0, pos)));
            s = s.erase(0, pos);
        }

        return numbers;
    }

    std::vector<std::string> lines{};
};