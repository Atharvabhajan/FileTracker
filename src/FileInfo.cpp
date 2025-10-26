#include "FileInfo.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "SHA256.h"

FileInfo::FileInfo(const std::filesystem::path& p) {
    fullpath = p.string();
    filename = p.filename().string();
    lastmodified = getlastwritetime(p);
    filesize = std::filesystem::file_size(p);
    // Hash will be computed only when needed
    hash = std::nullopt;
}   
std::string FileInfo::getlastwritetime(const std::filesystem::path& p) {
    try {
        auto ftime = std::filesystem::last_write_time(p);
        auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
        );

        time_t cftime = std::chrono::system_clock::to_time_t(sctp);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&cftime), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error reading last write time for " << p << ": " << e.what() << std::endl;
        return std::string("N/A");
    }
}
std::string FileInfo::computeFileHash(const std::filesystem::path& p) const {
    return SHA256::hashFile(p.string());
}

std::string FileInfo::getfilehash() const {
    if (!hash.has_value()) {
        // Compute hash only when first requested
        hash = computeFileHash(std::filesystem::path(fullpath));
    }
    return hash.value();
}

std::string FileInfo::getfullpath() const {
    return fullpath;
}

std::string FileInfo::getfullname() const {
    return filename;
}

std::string FileInfo::getlastmodifiedtime() const {
    return lastmodified;
}

uintmax_t FileInfo::getfilesize() const {
    return filesize;
}

void FileInfo::printCLI() const {
    std::cout << std::left
         << std::setw(50) << fullpath
         << std::setw(25) << filename
         << std::setw(15) << filesize
         << std::setw(20) << lastmodified
         << getfilehash() << "\n";
}

std::string FileInfo::toCSV() const {
    std::stringstream ss;
    ss << "\"" << fullpath << "\"," 
       << "\"" << filename << "\"," 
       << filesize << "," 
       << "\"" << lastmodified << "\"," 
       << "\"" << getfilehash() << "\"\n";
    return ss.str();
}