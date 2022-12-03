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

char getCommonCharacter(const std::string &firstCompartment, const std::string &secondCompartment) {
    // Both compartments are guaranteed to have one common character.
    // Therefore, we do not need another return statement outside of this loop.
    for (char character : firstCompartment) {
        if (secondCompartment.find(character) != std::string::npos) {
            return character;
        }
    }
}

int main() {
    std::string input = read_input_file("../2022/input/day_3.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    int totalPriority = 0;

    for (const std::string &line : lines) {
        int halfway = line.size() / 2;

        std::string firstCompartment = line.substr(0, halfway);
        std::string secondCompartment = line.substr(halfway);

        char commonCharacter = getCommonCharacter(firstCompartment, secondCompartment);
        int priority = getPriority(commonCharacter);

        totalPriority += priority;
    }

    std::cout << "Answer: " << totalPriority << '\n';

    return 0;
}
