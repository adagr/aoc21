#include "day.hpp"

class Day16 : public Day {

public:
    Day16() : Day{"input/day16.txt"} {}
    ~Day16() override = default;
    
    int sum{};
    std::map<char, int> hexToInt = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3},
                                    {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
                                    {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11},
                                    {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};

    auto readBits(uint64_t& input, int& bits, int n) {
        if (bits - n < 0) {
            // add more bits from input
            static int index{};
            for (int i{}; i < 4 && index < lines[0].size(); ++i) {
                bits += 4;
                input = input << 4;
                input |= hexToInt[lines[0][index++]];
            }
        }

        auto value = input >> (bits - n);
        // clear read input bits
        input &= ~(((2 << n) - 1) << (bits - n));
        bits -= n;    
        return value;
    }

    std::pair<int, uint64_t> readInput(uint64_t& input, int& bits) {
        auto version = readBits(input, bits, 3);
        auto typeId = readBits(input, bits, 3);
        sum += version;
        auto packetLength{6};
        uint64_t packetValue{};
        if (typeId == 4) {
            while (true) {
                auto value = readBits(input, bits, 5);
                packetLength += 5;
                packetValue = packetValue << 4 | value & 0xF;
                if ((value >> 4) == 0)
                    break;
            }
        } else {
            auto lengthTypeId = readBits(input, bits, 1);
            packetLength += 1;
            auto first{true};
            if (lengthTypeId == 0) {
                auto subPacketLength = readBits(input, bits, 15);
                packetLength += 15 + subPacketLength;
                while (subPacketLength > 0) {
                    auto [length, value] = readInput(input, bits);
                    subPacketLength -= length;
                    setValue(typeId, first, packetValue, value);
                }
            } else {
                auto numSubPacket = readBits(input, bits, 11);
                packetLength += 11;
                for (int i{}; i < numSubPacket; ++i) {
                    auto [length, value] = readInput(input, bits);
                    packetLength += length;
                    setValue(typeId, first, packetValue, value);
                }
            }
        }

        return std::make_pair(packetLength, packetValue);
    }

    void setValue(int typeId, bool& first, uint64_t& packetValue, uint64_t value) {
        if (first) {
            first = false;
            packetValue = value;
            return;
        }

        switch (typeId) {
        case 0:
            packetValue += value;
            break;
        case 1:
            packetValue *= value;
            break;
        case 2:
            packetValue = std::min(packetValue, value);
            break;
        case 3:
            packetValue = std::max(packetValue, value);
            break;
        case 5:
            packetValue = packetValue > value;
            break;
        case 6:
            packetValue = packetValue < value;
            break;
        case 7:
            packetValue = packetValue == value;
            break;
        default:
            break;
        }
    }

    void run() override {
        uint64_t input{};
        int bits{};
        auto [length, value] = readInput(input, bits);
        std::cout << sum << std::endl;
        std::cout << value;
    }

};