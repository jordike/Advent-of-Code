#include <algorithm>
#include <regex>
#include "util.h"

#define CRATE_COUNT 9

std::tuple<int, int, int> processCommand(const std::string &command) {
    auto getNumber = [command](const std::string &keyword) {
        // Keyword is guaranteed to be in the string. Therefore
        // we do not need to check if there is a match.
        unsigned int startIndex = command.find(keyword);
        unsigned int numberStart = startIndex + keyword.size() + 1;
        unsigned int numberEnd = command.find(' ', numberStart);

        if (numberEnd == std::string::npos) {
            numberEnd = command.size() - 1;
        }

        std::string numberAsString = command.substr(numberStart, numberEnd);
        int number = std::stoi(numberAsString);

        return number;
    };

    int amount = getNumber("move");
    int from = getNumber("from");
    int to = getNumber("to");

    return std::tuple<int, int, int> {
        amount,
        from,
        to
    };
}

void processCrates(std::vector<std::vector<char>> &crates, const std::string &line) {
    int crateIndex = 0;

    for (unsigned int characterIndex = 1; characterIndex < line.size(); characterIndex += 4) {
        char character = line[characterIndex];

        if (character != ' ') {
            std::vector<char> &crate = crates[crateIndex];

            crate.emplace_back(character);
        }

        crateIndex++;
    }
}

void transferCrates(std::vector<std::vector<char>> &crates, int amount, int from, int to) {
    std::vector<char> &crateFrom = crates[from - 1];
    std::vector<char> &crateTo = crates[to - 1];

    std::vector<char> toMove;

    for (int index = 0; index < amount; index++) {
        char character = crateFrom[index];

        toMove.emplace_back(character);
    }

    crateFrom.erase(crateFrom.begin(), crateFrom.begin() + amount);

    for (char character : toMove) {
        crateTo.insert(crateTo.begin(), character);
    }
}

int main() {
    std::string input = read_input_file("../2022/input/day_5.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    std::vector<std::vector<char>> crates;

    while (crates.size() != CRATE_COUNT) {
        std::vector<char> newVector;

        crates.emplace_back(newVector);
    }

    bool foundCommands = false;

    for (unsigned int lineCount = 0; lineCount < lines.size(); lineCount++) {
        const std::string &line = lines[lineCount];

        if (line == "") {
            foundCommands = true;

            continue;
        }

        if (foundCommands) {
            std::tuple<int, int, int> command = processCommand(line);

            int amount = std::get<0>(command);
            int from = std::get<1>(command);
            int to = std::get<2>(command);

            transferCrates(crates, amount, from, to);
        } else {
            if (line.find('[') != std::string::npos) {
                processCrates(crates, line);
            }
        }
    }

    std::cout << "Answer: ";

    for (const std::vector<char> &crate : crates) {
        std::cout << crate[0];
    }

    std::cout << '\n';

    return 0;
}
