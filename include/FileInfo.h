#ifndef FILEINFO_H
#define FILEINFO_H

#include "SHA256.h"
#include "ISerializable.h"
#include <string>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <optional>

class FileInfo : public ISerializable {
private:
    std::string fullpath;
    std::string filename;
    std::string lastmodified;
    uintmax_t filesize;
    mutable std::optional<std::string> hash;  // Lazy computation

public:
    FileInfo() = default;
    FileInfo(const std::filesystem::path& p);
    static std::string getlastwritetime(const std::filesystem::path& p);
    std::string computeFileHash(const std::filesystem::path& p) const;

    std::string getfullpath() const;
    std::string getfullname() const;
    std::string getlastmodifiedtime() const;
    uintmax_t getfilesize() const;
    std::string getfilehash() const;

    void printCLI() const override;
    std::string toCSV() const override;
};

#endif