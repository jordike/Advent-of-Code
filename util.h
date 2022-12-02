#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string read_input_file(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Could not open file at path '" << path << "'\n";

        return "";
    }

    std::string lineBuffer;
    std::string content;

    while (std::getline(file, lineBuffer)) {
        content += lineBuffer + '\n';
    }

    file.close();

    return content;
}

std::vector<std::string> split_input_in_lines(const std::string &input) {
    std::vector<std::string> lines;
    std::string lineBuffer = "";

    for (char character : input) {
        if (character == '\n') {
            lines.emplace_back(lineBuffer);
            lineBuffer = "";
        } else {
            lineBuffer += character;
        }
    }

    return lines;
}

#endif
