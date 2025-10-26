#ifndef DIRECTORYSNAPSHOT_H
#define DIRECTORYSNAPSHOT_H

#include "FileInfo.h"
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class DirectorySnapshot : public ISerializable  {
private:
    std::string directoryPath;
    std::vector<FileInfo> files;

public:
    DirectorySnapshot(const std::string& path);

    void scan(bool skip_permission_denied = true);
    void saveToCSV(const std::string& filename) const;

    const std::vector<FileInfo>& getFiles() const;

    std::string toCSV() const override;
    void printCLI() const override;
};

#endif
