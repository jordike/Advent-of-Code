#include "util.h"

// Rock     = A == X; 1 point
// Paper    = B == Y; 2 points
// Scissors = C == Z; 3 points

// Lose = 0 points
// Draw = 3 points
// Win  = 6 points

enum Option {
    ROCK,
    PAPER,
    SCISSORS
};

Option parseCharacter(char character) {
    switch (character) {
        case 'A':
        case 'X':
            return Option::ROCK;

        case 'B':
        case 'Y':
            return Option::PAPER;

        case 'C':
        case 'Z':
            return Option::SCISSORS;
    }
}

int getWinner(Option yourChoice, Option opponentChoice) {
    if (yourChoice == Option::ROCK && opponentChoice == Option::PAPER) {
        return -1;
    } else if (yourChoice == Option::ROCK && opponentChoice == Option::ROCK) {
        return 0;
    } else if (yourChoice == Option::ROCK && opponentChoice == Option::SCISSORS) {
        return 1;
    }

    else if (yourChoice == Option::PAPER && opponentChoice == Option::PAPER) {
        return 0;
    } else if (yourChoice == Option::PAPER && opponentChoice == Option::ROCK) {
        return 1;
    } else if (yourChoice == Option::PAPER && opponentChoice == Option::SCISSORS) {
        return -1;
    }

    else if (yourChoice == Option::SCISSORS && opponentChoice == Option::PAPER) {
        return 1;
    } else if (yourChoice == Option::SCISSORS && opponentChoice == Option::ROCK) {
        return -1;
    } else if (yourChoice == Option::SCISSORS && opponentChoice == Option::SCISSORS) {
        return 0;
    }
}

int main() {
    std::string input = read_input_file("../2022/input/day_2.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    int totalScore = 0;

    for (const std::string &line : lines) {
        if (line == "\n") {
            continue;
        }

        int roundScore = 0;

        char opponentChoice = line[0];
        char yourChoice = line[2];

        Option opponentChoiceOption = parseCharacter(opponentChoice);
        Option yourChoiceOption = parseCharacter(yourChoice);

        int result = getWinner(yourChoiceOption, opponentChoiceOption);

        switch (yourChoiceOption) {
            case Option::ROCK:
                roundScore += 1;
                break;

            case Option::PAPER:
                roundScore += 2;
                break;

            case Option::SCISSORS:
                roundScore += 3;
                break;
        }

        if (result == 0) {        // Draw
            roundScore += 3;
        } else if (result == 1) { // Win
            roundScore += 6;
        }

        totalScore += roundScore;
    }

    std::cout << "Answer: " << totalScore << '\n';

    return 0;
}
