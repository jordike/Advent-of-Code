#include "util.h"

inline int charToInt(char character) {
    // Ascii codes for alphabetical letters start at 96. By removing that,
    // we get 1 for a, and 26 for z.
    // Uppercase letters have a different ascii code, so we make them lowercase first.
    return static_cast<int>(std::tolower(character)) - 96;
}

int getPriority(char character) {
    int priority = charToInt(character);

    // If the letter is uppercase, add 26 to the priority.
    if (std::toupper(character) == character) {
        priority += 26;
    }

    return priority;
}

char getCommonCharacter(const std::string &line1, const std::string &line2, const std::string &line3) {
    // Both lines are guaranteed to have one common character.
    // Therefore, we do not need another return statement outside of this loop.
    for (char character : line1) {
        // We only need to loop through one line, and check the others, because one character is guaranteed
        // to be in all of them. If they do not get through this if-statement, it cannot be the correct
        // character.
        if (line2.find(character) != std::string::npos && line3.find(character) != std::string::npos) {
            return character;
        }
    }
}

int main() {
    std::string input = read_input_file("../2022/input/day_3.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    int totalPriority = 0;

    std::vector<std::string> group;
    int lineCount = 0;

    for (const std::string &line : lines) {
        group.emplace_back(line);

        if (group.size() != 3) {
            continue;
        }

        std::string &line1 = group[0];
        std::string &line2 = group[1];
        std::string &line3 = group[2];

        char commonCharacter = getCommonCharacter(line1, line2, line3);
        int priority = getPriority(commonCharacter);

        totalPriority += priority;

        // Clear the group.
        group = {};

        lineCount++;
    }

    std::cout << "Answer: " << totalPriority << '\n';

    return 0;
}
