#include <iostream>
#include <vector>
#include <algorithm>
#include "util.h"

int main() {
    std::string input = read_input_file("../2022/input/day_1.txt");
    std::vector<std::string> lines = split_input_in_lines(input);
    std::vector<int> elves;

    int totalCalories = 0;

    for (const std::string &line : lines) {
        if (line == "") {
            elves.emplace_back(totalCalories);
            totalCalories = 0;
        } else {
            int calories = std::stoi(line);

            totalCalories += calories;
        }
    }

    std::sort(elves.begin(), elves.end());

    int first = elves[elves.size() - 1];
    int second = elves[elves.size() - 2];
    int third = elves[elves.size() - 3];

    int total = first + second + third;

    std::cout << "Answer: " << total << '\n';

    return 0;
}
