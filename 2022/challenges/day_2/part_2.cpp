#include "util.h"

// Rock     = A; 1 point
// Paper    = B; 2 points
// Scissors = C; 3 points

// Lose = X; 0 points
// Draw = Y; 3 points
// Win  = Z; 6 points

enum Option {
    ROCK,
    PAPER,
    SCISSORS
};

Option parseCharacter(char character) {
    switch (character) {
        case 'A':
            return Option::ROCK;

        case 'B':
            return Option::PAPER;

        case 'C':
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

Option chooseResponse(Option opponentOption, char desiredResult) {
    #define CHECK_OPTION(option, result) if (getWinner(option, opponentOption) == result) \
                                             return option;

    if (desiredResult == 'Z') { // Win
        CHECK_OPTION(Option::ROCK, 1)
        CHECK_OPTION(Option::PAPER, 1)
        CHECK_OPTION(Option::SCISSORS, 1)
    } else if (desiredResult == 'X') { // Lose
        CHECK_OPTION(Option::ROCK, -1)
        CHECK_OPTION(Option::PAPER, -1)
        CHECK_OPTION(Option::SCISSORS, -1)
    } else if (desiredResult == 'Y') { // Draw
        CHECK_OPTION(Option::ROCK, 0)
        CHECK_OPTION(Option::PAPER, 0)
        CHECK_OPTION(Option::SCISSORS, 0)
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
        char desiredResult = line[2];

        Option opponentChoiceOption = parseCharacter(opponentChoice);
        Option yourChoiceOption = chooseResponse(opponentChoiceOption, desiredResult);

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

    std::cout << "Total score: " << totalScore << '\n';

    return 0;
}
