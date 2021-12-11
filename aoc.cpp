#include <stdio.h>
#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"
#include "day10.hpp"
#include "day11.hpp"

int main(int argc, char const *argv[]) {
    Day* day = new Day11{};
    day->run();
    delete day;
    return 0;
}
