#include <vector>
#include <string>
#include <fstream>
#include <iostream>

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

protected:
    std::vector<std::string> lines{};
};