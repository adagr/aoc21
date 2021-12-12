#include "day.hpp"
#include <cctype>

class Day12 : public Day {

public:
    Day12() : Day{"input/day12.txt"} {}
    ~Day12() override = default;
    
    void run() override {
        // Part 1
        std::map<std::string, std::set<std::string>> nodes{};
        for (const auto& line : lines) {
            auto input = getFromLine(line, "-");
            if (input[1] != "start")
                nodes[input[0]].emplace(input[1]);
            if (input[0] != "start")
                nodes[input[1]].emplace(input[0]);
        }

        int paths{};
        for (const auto& node : nodes["start"]) {
            std::set<std::string> visitedNodes{};
            if (std::islower(node[0]))
                visitedNodes.emplace(node);

            visitNextNode(nodes, visitedNodes, node, paths, true);
        }

        std::cout << paths << std::endl;

    }

    void visitNextNode(const std::map<std::string, std::set<std::string>>& nodes, std::set<std::string> visitedNodes, std::string node, int& paths, bool extraVisit) {
        if (node == "end") {
            ++paths;
            return;
        }

        auto nextNodes = nodes.at(node);
        for (const auto& nn : nextNodes) {
            if (visitedNodes.find(nn) == visitedNodes.end()) {
                auto visitedNodesNew = visitedNodes;
                if (std::islower(nn[0]))
                    visitedNodesNew.emplace(nn);

                visitNextNode(nodes, visitedNodesNew, nn, paths, extraVisit);
            } else if (extraVisit) // Part 2
                visitNextNode(nodes, visitedNodes, nn, paths, false);
        }
    }

};