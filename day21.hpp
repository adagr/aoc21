#include "day.hpp"

class Day21 : public Day {

public:
    Day21() : Day{"input/day21.txt"} {}
    ~Day21() override = default;

    uint64_t p1Wins{};
    uint64_t p2Wins{};

    struct Player {
        Player(int position) : pos{position - 1}, score{}, player1{} {}
        int pos;
        int score;
        bool player1;
    };
    
    void run() override {
        // Part 1
        Player p1 = Player{std::stoi(std::string{lines[0][lines[0].find(':') + 2]})};
        Player p2 = Player{std::stoi(std::string{lines[1][lines[1].find(':') + 2]})};
        p1.player1 = true;
        int dice{0};
        while(true) {
            play(p1, dice);
            if (checkScore(p1, p2, dice, 1000))
                break;
            play(p2, dice);
            if (checkScore(p2, p1, dice, 1000))
                break;
        }

        // Part 2
        p1 = Player{std::stoi(std::string{lines[0][lines[0].find(':') + 2]})};
        p2 = Player{std::stoi(std::string{lines[1][lines[1].find(':') + 2]})};
        p1.player1 = true;
        playQuant(p1, p2, 3, 1);
        playQuant(p1, p2, 4, 3);
        playQuant(p1, p2, 5, 6);
        playQuant(p1, p2, 6, 7);
        playQuant(p1, p2, 7, 6);
        playQuant(p1, p2, 8, 3);
        playQuant(p1, p2, 9, 1);
        std::cout << p1Wins << std::endl;
        std::cout << p2Wins;
    }

    void playQuant(Player p1, Player p2, int dice, uint64_t universes) {
        p1.pos += dice;
        p1.pos = p1.pos % 10;
        p1.score += p1.pos + 1;
        if (p1.score >= 21) {
            if (p1.player1)
                p1Wins += universes;
            else
                p2Wins += universes;

            return;
        }

        playQuant(p2, p1, 3, universes * 1);
        playQuant(p2, p1, 4, universes * 3);
        playQuant(p2, p1, 5, universes * 6);
        playQuant(p2, p1, 6, universes * 7);
        playQuant(p2, p1, 7, universes * 6);
        playQuant(p2, p1, 8, universes * 3);
        playQuant(p2, p1, 9, universes * 1);
    }

    bool checkScore(const Player& p1, const Player& p2, int dice, int score) {
        if (p1.score >= score) {
            std::cout << p2.score * dice << std::endl;
            return true;
        }

        return false;
    }

    void play(Player& p, int& dice) {
        for (int i{}; i < 3; ++i) {
            p.pos += dice % 100 + 1;
            p.pos = p.pos % 10;
            ++dice;
        }

        p.score += p.pos + 1;
    }

};