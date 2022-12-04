#include <tuple>
#include "util.h"

std::tuple<int, int> processElf(const std::string &elf) {
    int seperatorIndex = elf.find('-');
    std::string firstHalf = elf.substr(0, seperatorIndex);
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

    bool firstRangeContainsSecond = std::get<0>(firstRange) <= std::get<0>(secondRange) &&
                                    std::get<1>(firstRange) >= std::get<1>(secondRange);

    bool secondRangeContainsFirst = std::get<0>(firstRange) >= std::get<0>(secondRange) &&
                                    std::get<1>(firstRange) <= std::get<1>(secondRange);

    return firstRangeContainsSecond || secondRangeContainsFirst;
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
