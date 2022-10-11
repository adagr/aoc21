#include "day.hpp"

class Day23 : public Day {

public:
    Day23() : Day{"input/day23.txt"} {}
    ~Day23() override = default;
    
    std::vector<int> totalCosts{};
    int cheapestCost{100000};
    enum class Position {
        hallway1,
        hallway2,
        hallway3,
        hallway4,
        hallway5,
        hallway6,
        hallway7,
        roomA,
        roomB,
        roomC,
        roomD
    };


    void run() override {
        std::array<char, 7> hallway{};
        std::deque<char> roomA{}, roomB{}, roomC{}, roomD{};
        hallway.fill('.');
        for (int i{}; i < 4; ++i) {
            roomA.push_back(lines[i + 2][3]);
            roomB.push_back(lines[i + 2][5]);
            roomC.push_back(lines[i + 2][7]);
            roomD.push_back(lines[i + 2][9]);
        }

        run(Position::roomA, 0, roomA, roomB, roomC, roomD, hallway);
        run(Position::roomB, 0, roomA, roomB, roomC, roomD, hallway);
        run(Position::roomC, 0, roomA, roomB, roomC, roomD, hallway);
        run(Position::roomD, 0, roomA, roomB, roomC, roomD, hallway);
        std::sort(totalCosts.begin(), totalCosts.end());
        std::cout << totalCosts.front() << std::endl;
    }

    void run(Position start, int cost, const std::deque<char>& roomA, const std::deque<char>& roomB, const std::deque<char>& roomC, const std::deque<char>& roomD, const std::array<char, 7>& hallway) {
        std::vector<Position> moves{};
        switch (start) {
        case Position::hallway1:
        case Position::hallway2:
        case Position::hallway3:
        case Position::hallway4:
        case Position::hallway5:
        case Position::hallway6:
        case Position::hallway7:
            if (hallway[static_cast<int>(start)] != '.')
                moves = getPossibleMoves(start, hallway[static_cast<int>(start)], roomA, roomB, roomC, roomD, hallway);
            break;
        case Position::roomA:
            if (!roomA.empty()) {
                for (const auto& pos : roomA) {
                    if (pos != 'A') {
                        moves = getPossibleMoves(start, roomA.front(), roomA, roomB, roomC, roomD, hallway);
                        break;
                    }
                }
            }
            break;
        case Position::roomB:
            if (!roomB.empty()) {
                for (const auto& pos : roomB) {
                    if (pos != 'B') {
                        moves = getPossibleMoves(start, roomB.front(), roomA, roomB, roomC, roomD, hallway);
                        break;
                    }
                }
            }
            break;
        case Position::roomC:
            if (!roomC.empty()) {
                for (const auto& pos : roomC) {
                    if (pos != 'C') {
                        moves = getPossibleMoves(start, roomC.front(), roomA, roomB, roomC, roomD, hallway);
                        break;
                    }
                }
            }
            break;
        case Position::roomD:
            if (!roomD.empty()) {
                for (const auto& pos : roomD) {
                    if (pos != 'D') {
                        moves = getPossibleMoves(start, roomD.front(), roomA, roomB, roomC, roomD, hallway);
                        break;
                    }
                }
            }
            break;
        default:
            break;
        }
        char c{};
        switch (start) {
        case Position::hallway1:
        case Position::hallway2:
        case Position::hallway3:
        case Position::hallway4:
        case Position::hallway5:
        case Position::hallway6:
        case Position::hallway7:
            c = hallway[static_cast<int>(start)];
            break;
        case Position::roomA:
            c = roomA.front();
            break;
        case Position::roomB:
            c = roomB.front();
            break;
        case Position::roomC:
            c = roomC.front();
            break;
        case Position::roomD:
            c = roomD.front();
            break;
        default:
            break;
        }
        std::sort(moves.begin(), moves.end(), [&](Position p1, Position p2) {
            return calculateCost(start, p1, c, roomA, roomB, roomC, roomD, hallway) <= calculateCost(start, p2, c, roomA, roomB, roomC, roomD, hallway);
        });
        for (auto& move : moves) {
            auto rA = roomA;
            auto rB = roomB;
            auto rC = roomC;
            auto rD = roomD;
            auto hw = hallway;
            auto co = cost;
            co += calculateCost(start, move, c, rA, rB, rC, rD, hw);
            switch (start) {
            case Position::hallway1:
            case Position::hallway2:
            case Position::hallway3:
            case Position::hallway4:
            case Position::hallway5:
            case Position::hallway6:
            case Position::hallway7:
                hw[static_cast<int>(start)] = '.';
                break;
            case Position::roomA:
                rA.pop_front();
                break;
            case Position::roomB:
                rB.pop_front();
                break;
            case Position::roomC:
                rC.pop_front();
                break;
            case Position::roomD:
                rD.pop_front();
                break;
            default:
                break;
            }
            switch (move) {
            case Position::hallway1:
            case Position::hallway2:
            case Position::hallway3:
            case Position::hallway4:
            case Position::hallway5:
            case Position::hallway6:
            case Position::hallway7:
                hw[static_cast<int>(move)] = c;
                break;
            case Position::roomA:
                rA.push_front(c);
                break;
            case Position::roomB:
                rB.push_front(c);
                break;
            case Position::roomC:
                rC.push_front(c);
                break;
            case Position::roomD:
                rD.push_front(c);
                break;
            default:
                break;
            }

            if (isCompleted(rA, rB, rC, rD)) {
                totalCosts.push_back(co);
                if (co < cheapestCost) {
                    cheapestCost = co;
                    std::cout << co << std::endl;
                }
                return;
            }
            
            run(Position::hallway1, co, rA, rB, rC, rD, hw);
            run(Position::hallway2, co, rA, rB, rC, rD, hw);
            run(Position::hallway3, co, rA, rB, rC, rD, hw);
            run(Position::hallway4, co, rA, rB, rC, rD, hw);
            run(Position::hallway5, co, rA, rB, rC, rD, hw);
            run(Position::hallway6, co, rA, rB, rC, rD, hw);
            run(Position::hallway7, co, rA, rB, rC, rD, hw);
            run(Position::roomA, co, rA, rB, rC, rD, hw);
            run(Position::roomB, co, rA, rB, rC, rD, hw);
            run(Position::roomC, co, rA, rB, rC, rD, hw);
            run(Position::roomD, co, rA, rB, rC, rD, hw);
        }
    }

    bool isCompleted(const std::deque<char>& roomA, const std::deque<char>& roomB, const std::deque<char>& roomC, const std::deque<char>& roomD) {
        auto rows{lines.size() - 3};
        if (roomA.size() != rows || roomB.size() != rows || roomC.size() != rows || roomD.size() != rows)
            return false;

        for (int i{}; i < rows; ++i)
            if (roomA[i] != 'A' || roomB[i] != 'B' || roomC[i] != 'C' || roomD[i] != 'D')
                return false;

        return true;
    }

    std::map<char, int> costs = {{'A', 1}, {'B', 10}, {'C', 100}, {'D', 1000}};
    std::map<char, Position> charToPosition = {{'A', Position::roomA}, {'B', Position::roomB}, {'C', Position::roomC}, {'D', Position::roomD}};

    int calculateCost(Position start, Position goal, char c, const std::deque<char>& roomA, const std::deque<char>& roomB, const std::deque<char>& roomC, const std::deque<char>& roomD, const std::array<char, 7>& hallway) {
        int cost{costs[c]};
        auto rows{lines.size() - 3};
        switch (start) {
        case Position::roomA:
            switch (goal) {
            case Position::roomB:
                cost *= 2 * rows - roomA.size() - roomB.size() + 3;
                break;
            case Position::roomC:
                cost *= 2 * rows - roomA.size() - roomC.size() + 5;
                break;
            case Position::roomD:
                cost *= 2 * rows - roomA.size() - roomD.size() + 7;
                break;
            case Position::hallway1:
                cost *= rows - roomA.size() + 3;
                break;
            case Position::hallway2:
                cost *= rows - roomA.size() + 2;
                break;
            case Position::hallway3:
                cost *= rows - roomA.size() + 2;
                break;
            case Position::hallway4:
                cost *= rows - roomA.size() + 4;
                break;
            case Position::hallway5:
                cost *= rows - roomA.size() + 6;
                break;
            case Position::hallway6:
                cost *= rows - roomA.size() + 8;
                break;
            case Position::hallway7:
                cost *= rows - roomA.size() + 9;
                break;
            default:
                break;
            }
            break;
        case Position::roomB:
            switch (goal) {
            case Position::roomA:
                cost *= 2 * rows - roomB.size() - roomA.size() + 3;
                break;
            case Position::roomC:
                cost *= 2 * rows - roomB.size() - roomC.size() + 3;
                break;
            case Position::roomD:
                cost *= 2 * rows - roomB.size() - roomD.size() + 5;
                break;
            case Position::hallway1:
                cost *= rows - roomB.size() + 5;
                break;
            case Position::hallway2:
                cost *= rows - roomB.size() + 4;
                break;
            case Position::hallway3:
                cost *= rows - roomB.size() + 2;
                break;
            case Position::hallway4:
                cost *= rows - roomB.size() + 2;
                break;
            case Position::hallway5:
                cost *= rows - roomB.size() + 4;
                break;
            case Position::hallway6:
                cost *= rows - roomB.size() + 6;
                break;
            case Position::hallway7:
                cost *= rows - roomB.size() + 7;
                break;
            default:
                break;
            }
            break;
        case Position::roomC:
            switch (goal) {
            case Position::roomA:
                cost *= 2 * rows - roomC.size() - roomA.size() + 5;
                break;
            case Position::roomB:
                cost *= 2 * rows - roomC.size() - roomB.size() + 3;
                break;
            case Position::roomD:
                cost *= 2 * rows - roomC.size() - roomD.size() + 3;
                break;
            case Position::hallway1:
                cost *= rows - roomC.size() + 7;
                break;
            case Position::hallway2:
                cost *= rows - roomC.size() + 6;
                break;
            case Position::hallway3:
                cost *= rows - roomC.size() + 4;
                break;
            case Position::hallway4:
                cost *= rows - roomC.size() + 2;
                break;
            case Position::hallway5:
                cost *= rows - roomC.size() + 2;
                break;
            case Position::hallway6:
                cost *= rows - roomC.size() + 4;
                break;
            case Position::hallway7:
                cost *= rows - roomC.size() + 5;
                break;
            default:
                break;
            }
            break;
        case Position::roomD:
            switch (goal) {
            case Position::roomA:
                cost *= 2 * rows - roomD.size() - roomA.size() + 7;
                break;
            case Position::roomB:
                cost *= 2 * rows - roomD.size() - roomB.size() + 5;
                break;
            case Position::roomC:
                cost *= 2 * rows - roomD.size() - roomC.size() + 3;
                break;
            case Position::hallway1:
                cost *= rows - roomD.size() + 9;
                break;
            case Position::hallway2:
                cost *= rows - roomD.size() + 8;
                break;
            case Position::hallway3:
                cost *= rows - roomD.size() + 6;
                break;
            case Position::hallway4:
                cost *= rows - roomD.size() + 4;
                break;
            case Position::hallway5:
                cost *= rows - roomD.size() + 2;
                break;
            case Position::hallway6:
                cost *= rows - roomD.size() + 2;
                break;
            case Position::hallway7:
                cost *= rows - roomD.size() + 3;
                break;
            default:
                break;
            }
            break;
        case Position::hallway1:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 2;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 4;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 6;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 8;
                break;
            default:
                break;
            }
            break;
        case Position::hallway2:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 1;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 3;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 5;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 7;
                break;
            default:
                break;
            }
            break;
        case Position::hallway3:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 1;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 1;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 3;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 5;
                break;
            default:
                break;
            }
            break;
        case Position::hallway4:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 3;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 1;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 1;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 3;
                break;
            default:
                break;
            }
            break;
        case Position::hallway5:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 5;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 3;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 1;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 1;
                break;
            default:
                break;
            }
            break;
        case Position::hallway6:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 7;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 5;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 3;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 1;
                break;
            default:
                break;
            }
            break;
        case Position::hallway7:
            switch (goal) {
            case Position::roomA:
                cost *= rows - roomA.size() + 8;
                break;
            case Position::roomB:
                cost *= rows - roomB.size() + 6;
                break;
            case Position::roomC:
                cost *= rows - roomC.size() + 4;
                break;
            case Position::roomD:
                cost *= rows - roomD.size() + 2;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        return cost;
    }

    std::vector<Position> getPossibleMoves(Position start, char goal, const std::deque<char>& roomA, const std::deque<char>& roomB, const std::deque<char>& roomC, const std::deque<char>& roomD, const std::array<char, 7>& hallway) {
        std::vector<Position> possibleMoves{};
        switch (start) {
        case Position::roomA:
            switch (goal) {
            case 'B':
                if (hallway[2] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[2] == '.' && hallway[3] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            if (!possibleMoves.empty())
                return possibleMoves;
            if (hallway[0] == '.' && hallway[1] == '.')
                possibleMoves.push_back(Position::hallway1);
            if (hallway[1] == '.')
                possibleMoves.push_back(Position::hallway2);
            if (hallway[2] == '.')
                possibleMoves.push_back(Position::hallway3);
            if (hallway[2] == '.' && hallway[3] == '.')
                possibleMoves.push_back(Position::hallway4);
            if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway5);
            if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.')
                possibleMoves.push_back(Position::hallway6);
            if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.' && hallway[6] == '.')
                possibleMoves.push_back(Position::hallway7);
            break;
        case Position::roomB:
            switch (goal) {
            case 'A':
                if (hallway[2] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'C':
                if (hallway[3] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            if (!possibleMoves.empty())
                return possibleMoves;
            if (hallway[0] == '.' && hallway[1] == '.' && hallway[2] == '.')
                possibleMoves.push_back(Position::hallway1);
            if (hallway[1] == '.' && hallway[2] == '.')
                possibleMoves.push_back(Position::hallway2);
            if (hallway[2] == '.')
                possibleMoves.push_back(Position::hallway3);
            if (hallway[3] == '.')
                possibleMoves.push_back(Position::hallway4);
            if (hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway5);
            if (hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.')
                possibleMoves.push_back(Position::hallway6);
            if (hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.' && hallway[6] == '.')
                possibleMoves.push_back(Position::hallway7);
            break;
        case Position::roomC:
            switch (goal) {
            case 'A':
                if (hallway[2] == '.' && hallway[3] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[3] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'D':
                if (hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            if (!possibleMoves.empty())
                return possibleMoves;
            if (hallway[0] == '.' && hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.')
                possibleMoves.push_back(Position::hallway1);
            if (hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.')
                possibleMoves.push_back(Position::hallway2);
            if (hallway[2] == '.' && hallway[3] == '.')
                possibleMoves.push_back(Position::hallway3);
            if (hallway[3] == '.')
                possibleMoves.push_back(Position::hallway4);
            if (hallway[4] == '.')
                possibleMoves.push_back(Position::hallway5);
            if (hallway[4] == '.' && hallway[5] == '.')
                possibleMoves.push_back(Position::hallway6);
            if (hallway[4] == '.' && hallway[5] == '.' && hallway[6] == '.')
                possibleMoves.push_back(Position::hallway7);
            break;
        case Position::roomD:
            switch (goal) {
            case 'A':
                if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[4] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            default:
                break;
            }
            if (!possibleMoves.empty())
                return possibleMoves;
            if (hallway[0] == '.' && hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway1);
            if (hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway2);
            if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway3);
            if (hallway[3] == '.' && hallway[4] == '.')
                possibleMoves.push_back(Position::hallway4);
            if (hallway[4] == '.')
                possibleMoves.push_back(Position::hallway5);
            if (hallway[5] == '.')
                possibleMoves.push_back(Position::hallway6);
            if (hallway[5] == '.' && hallway[6] == '.')
                possibleMoves.push_back(Position::hallway7);
            break;
        case Position::hallway1:
            switch (goal) {
            case 'A':
                if (hallway[1] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[1] == '.' && hallway[2] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[1] == '.' && hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway2:
            switch (goal) {
            case 'A':
                getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[2] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[2] == '.' && hallway[3] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway3:
        switch (goal) {
            case 'A':
                getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[3] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway4:
        switch (goal) {
            case 'A':
                if (hallway[2] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                if (hallway[4] == '.')
                    getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway5:
        switch (goal) {
            case 'A':
                if (hallway[2] == '.' && hallway[3] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[3] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway6:
        switch (goal) {
            case 'A':
                if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[3] == '.' && hallway[4] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[4] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
                getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        case Position::hallway7:
        switch (goal) {
            case 'A':
                if (hallway[2] == '.' && hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.')
                    getPossibleMoves(roomA, possibleMoves, Position::roomA, goal);
                break;
            case 'B':
                if (hallway[3] == '.' && hallway[4] == '.' && hallway[5] == '.')
                    getPossibleMoves(roomB, possibleMoves, Position::roomB, goal);
                break;
            case 'C':
                if (hallway[4] == '.' && hallway[5] == '.')
                    getPossibleMoves(roomC, possibleMoves, Position::roomC, goal);
                break;
            case 'D':
            if (hallway[5] == '.')
                getPossibleMoves(roomD, possibleMoves, Position::roomD, goal);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }

        return possibleMoves;
    }

    void getPossibleMoves (const std::deque<char>& room, std::vector<Position>& possibleMoves, Position goal, char c) {
        if (room.empty())
            possibleMoves.push_back(goal);
        else {
            bool success{true};
            for (const auto& pos : room) {
                if (pos != c) {
                    success = false;
                    break;
                }
            }

            if (success)
                possibleMoves.push_back(goal);
        }
    }

};