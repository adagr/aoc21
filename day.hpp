#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <numeric>
#include <array>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_map>

class Day {

public:
    explicit Day(std::string fileName) {
        std::ifstream input{fileName};
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

    template<typename T = int>
    std::vector<T> getNumbersInLine(const std::string& line, char delim) {
        //delim needs to be char for day4
        std::vector<T> numbers{};
        auto s = line;
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
    
    template<typename T = std::string>
    std::vector<T> getFromLine(const std::string& line, std::string delim) {
        std::vector<T> data{};
        auto s = line;
        while(true) {
            auto pos = s.find(delim);
            if (pos == std::string::npos) {
                data.emplace_back(s);
                break;
            }
                
            data.emplace_back(s.substr(0, pos));
            s = s.erase(0, pos + delim.size());
        }

        return data;
    }

    template<typename Container, typename Value>
    bool contains(const Container& container, Value value) {
        return container.find(value) != container.end();
    }

    std::vector<std::string> lines{};
};