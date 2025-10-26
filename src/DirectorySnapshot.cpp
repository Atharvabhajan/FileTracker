#include "DirectorySnapshot.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

DirectorySnapshot::DirectorySnapshot(const std::string& path)
    : directoryPath(path) {
    scan();  // Ensure snapshot is populated on construction
}

void DirectorySnapshot::scan(bool skip_permission_denied) {
    files.clear();

    for (const auto& entry : fs::recursive_directory_iterator(
             directoryPath,
             skip_permission_denied
                 ? fs::directory_options::skip_permission_denied
                 : fs::directory_options::none)) {

        if (entry.is_regular_file()) {
            try {
                files.emplace_back(entry.path());
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error accessing file " << entry.path()
                          << ": " << e.what() << std::endl;
            }
        }
    }
}

void DirectorySnapshot::printCLI() const {
    std::cout << std::left << std::setw(50) << "File Path"
         << std::setw(25) << "File Name"
         << std::setw(15) << "Size (bytes)"
         << "Last Modified Time" << "Hash" << "\n";
    std::cout << std::string(110, '-') << "\n";

    for (const auto& file : files) {
        file.printCLI();
    }
}

std::string DirectorySnapshot::toCSV() const {
    std::stringstream ss;
    ss << "File Path,File Name,Size (bytes),Last Modified,SHA256\n";
    for (const auto& file : files)
        ss << file.toCSV();
    return ss.str();
}


void DirectorySnapshot::saveToCSV(const std::string& filename) const {
    std::ofstream csvFile(filename);
    if (!csvFile.is_open()) {
        std::cerr << "Error: Could not create CSV file.\n";
        return;
    }
    csvFile << toCSV();
    csvFile.close();
}


const std::vector<FileInfo>& DirectorySnapshot::getFiles() const {
    return files;
}

