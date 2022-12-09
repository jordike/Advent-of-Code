#include <algorithm>
#include "util.h"
#include "file.h"

File *rootDirectory = nullptr;
File *currentDirectory = nullptr;

void processCommandOutput(const std::string &command, const std::vector<std::string> &output) {
    if (command.find("cd") != std::string::npos) {
        int targetNameStart = command.find(' ', command.find(' ') + 1) + 1;
        const std::string targetName = command.substr(targetNameStart);

        if (targetName == "/") {
            currentDirectory = rootDirectory;
        } else if (targetName == "..") {
            currentDirectory = currentDirectory->parentDirectory;
        } else {
            if (!currentDirectory->fileExists(targetName)) {
                File *file = new File(currentDirectory, targetName, 0);
                currentDirectory->addFile(file);
            }

            File *newDirectory = currentDirectory->findFile(targetName);

            if (newDirectory != nullptr) {
                currentDirectory = newDirectory;
            }
        }
    } else if (command.find("ls") != std::string::npos) {
        for (const std::string &line : output) {
            int fileNameStart = line.find(' ');
            std::string fileSizeString = line.substr(0, fileNameStart);
            std::string fileName = line.substr(fileNameStart + 1);

            if (!currentDirectory->fileExists(fileName)) {
                int size;

                if (fileSizeString == "dir") {
                    size = 0;
                } else {
                    size = std::stoi(fileSizeString);
                }

                File *file = new File(currentDirectory, fileName, size);

                currentDirectory->addFile(file);
            }
        }
    }
}

void processInput(const std::vector<std::string> &input) {
    std::string lastCommand = "";
    std::vector<std::string> commandOutput;

    rootDirectory = new File(nullptr, "/", 0);
    currentDirectory = rootDirectory;

    for (const std::string &line : input) {
        if (line.find('$') != std::string::npos) {
            processCommandOutput(lastCommand, commandOutput);

            lastCommand = line;
            commandOutput.clear();
        } else {
            commandOutput.emplace_back(line);
        }
    }

    // Process the last command that wasn't handled yet.
    if (lastCommand != "" && commandOutput.size() > 0) {
        processCommandOutput(lastCommand, commandOutput);
    }
}

std::vector<File *> getAllDirectories(File *file) {
    std::vector<File *> files;

    // If the size of the file itself is 0, it is a directory.
    if (file->fileSize == 0) {
        files.emplace_back(file);
    }

    for (File *subFile : file->files) {
        for (File *subDirectory : getAllDirectories(subFile)) {
            files.emplace_back(subDirectory);
        }
    }

    return files;
}

int main() {
    std::string input = read_input_file("../2022/input/day_7.txt");
    std::vector<std::string> lines = split_input_in_lines(input);

    processInput(lines);

    std::vector<File *> directories = getAllDirectories(rootDirectory);

    auto sortDirectories = [](File *fileA, File *fileB) {
        return fileA->getTotalSize() < fileB->getTotalSize();
    };

    std::sort(directories.begin(), directories.end(), sortDirectories);

    constexpr int totalDiskSpace = 70000000;
    int unusedSpace = totalDiskSpace - rootDirectory->getTotalSize();

    for (const File *directory : directories) {
        int directoryTotalSize = directory->getTotalSize();
        if (unusedSpace + directoryTotalSize >= 30000000) {
            std::cout << "Answer: " << directoryTotalSize << '\n';

            break;
        }
    }

    delete rootDirectory;

    return 0;
}
