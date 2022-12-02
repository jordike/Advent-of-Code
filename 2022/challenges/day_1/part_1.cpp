#include <iostream>
#include <vector>
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

    int highestNumber = 0;

    for (int number : elves) {
        highestNumber = std::max(number, highestNumber);
    }

    std::cout << "Answer: " << highestNumber << '\n';

    return 0;
}
