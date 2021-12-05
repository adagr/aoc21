#include <stdio.h>
#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"

int main(int argc, char const *argv[]) {
    Day* day = new Day5{};
    day->run();
    return 0;
}
