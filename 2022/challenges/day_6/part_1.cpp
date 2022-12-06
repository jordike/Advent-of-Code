#include <map>
#include "util.h"

bool isUnique(const std::string &slice) {
    std::map<char, bool> usedCharacters;

    for (char character : slice) {
        if (usedCharacters[character]) {
            return false;
        }

        usedCharacters[character] = true;
    }

    return true;
}

int main() {
    std::string input = read_input_file("../2022/input/day_6.txt");

    for (unsigned int index = 0; index < input.size() - 4; index++) {
        std::string slice = input.substr(index, 4);

        if (isUnique(slice)) {
            std::cout << "Answer: " << index + 4 << '\n';

            break;
        }
    }

    return 0;
}
