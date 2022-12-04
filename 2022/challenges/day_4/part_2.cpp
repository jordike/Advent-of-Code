#include <tuple>
#include "util.h"

std::tuple<int, int> processElf(const std::string &elf) {
    int seperatorIndex = elf.find('-');
    std::string firstHalf = elf.substr(0, seperatorIndex);
    // + 1 to not include the seperator itself.
    std::string secondHalf = elf.substr(seperatorIndex + 1);

    int firstHalfNumber = std::stoi(firstHalf);
    int secondHalfNumber = std::stoi(secondHalf);

    return std::tuple<int, int> {
        firstHalfNumber,
        secondHalfNumber
    };
}

bool overlaps(const std::string &firstElf, const std::string &secondElf) {
    std::tuple<int, int> firstRange = processElf(firstElf);
    std::tuple<int, int> secondRange = processElf(secondElf);

    // I am sure this is not the most efficient method, and I could probably get it
    // done with a few if-statements. I tried those, like in part 1, but I couldn't get it right.
    // So instead I chose to just do this method instead.
    for (int number = std::get<0>(firstRange); number <= std::get<1>(firstRange); number++) {
        if (number >= std::get<0>(secondRange) && number <= std::get<1>(secondRange)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::string input = read_input_file("../2022/input/day_4.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    int overlapCounter = 0;

    for (const std::string &line : lines) {
        int seperatorIndex = line.find(',');

        std::string firstElfRange = line.substr(0, seperatorIndex);
        // + 1 to not include the seperator itself.
        std::string secondElfRange = line.substr(seperatorIndex + 1);

        bool rangesOverlap = overlaps(firstElfRange, secondElfRange);

        if (rangesOverlap) {
            overlapCounter++;
        }
    }

    std::cout << "Answer: " << overlapCounter << '\n';

    return 0;
}
