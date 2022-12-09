#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// In order to make the file structure simpler to implement, I will
// emulate the Linux filesystem: everything is a file, even a folder.
class File {
    public:
        File *parentDirectory;
        std::string fileName;
        int fileSize;
        std::vector<File*> files;

        File(File *parentDirectory, const std::string &fileName, int fileSize);
        ~File();

        void addFile(File *file);
        File* findFile(const std::string &fileName) const;
        bool fileExists(const std::string &fileName) const;

        int getTotalSize() const;
};

File::File(File *parentDirectory, const std::string &fileName, int fileSize)
    : parentDirectory(parentDirectory), fileName(fileName), fileSize(fileSize)
{ }

File::~File() {
    for (File *file : this->files) {
        delete file;
    }
}

File* File::findFile(const std::string &fileName) const {
    for (File *file : this->files) {
        if (file == nullptr) {
            continue;
        }

        if (file->fileName == fileName) {
            return file;
        }
    }

    return nullptr;
}

void File::addFile(File *file) {
    this->files.emplace_back(file);
}

bool File::fileExists(const std::string &fileName) const {
    return this->findFile(fileName) != nullptr;
}

int File::getTotalSize() const {
    int size = this->fileSize;

    for (const File *file : this->files) {
        if (file != nullptr) {
            size += file->getTotalSize();
        }
    }

    return size;
}

#endif
