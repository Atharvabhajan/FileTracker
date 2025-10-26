#include "ChangeDetector.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include "Logger.h"

ChangeDetector::ChangeDetector(const DirectorySnapshot& oldSnap, const DirectorySnapshot& newSnap)
    : oldSnapshot(oldSnap), newSnapshot(newSnap) {
    detectChanges();
}

// void ChangeDetector::detectChanges() {
//     changes.clear();

//     const auto& oldFiles = oldSnapshot.getFiles();
//     const auto& newFiles = newSnapshot.getFiles();

//     unordered_map<string, FileInfo> oldFileMap;
//     for (const auto& file : oldFiles) {
//         oldFileMap[file.getfullpath()] = file;
//     }

//     for (const auto& newFile : newFiles) {
//         auto it = oldFileMap.find(newFile.getfullpath());
//         if (it == oldFileMap.end()) {
//             changes.emplace_back("[NEW]", newFile.getfullpath());
//         } else {
//             const auto& oldFile = it->second;
//             if (newFile.getfilesize() != oldFile.getfilesize() ||
//                 newFile.getlastmodifiedtime() != oldFile.getlastmodifiedtime()) {
//                 changes.emplace_back("[MODIFIED]", newFile.getfullpath());
//             }
//             oldFileMap.erase(it);
//         }
//     }

//     for (const auto& [path, _] : oldFileMap) {
//         changes.emplace_back("[DELETED]", path);
//     }
// }

void ChangeDetector::detectChanges() {
    changes.clear();
    std::unordered_map<std::string, FileInfo> oldMap;
    for (const auto& file : oldSnapshot.getFiles())
        oldMap[file.getfullpath()] = file;

    for (const auto& file : newSnapshot.getFiles()) {
        auto it = oldMap.find(file.getfullpath());
        if (it == oldMap.end()) {
            changes.emplace_back("[ADDED]", file.getfullpath());
        } else {
            // Special handling for text files - always check content
            bool isTextFile = file.getfullpath().find(".txt") != std::string::npos;
            bool needsHashCheck = isTextFile || 
                                file.getfilesize() != it->second.getfilesize() ||
                                file.getlastmodifiedtime() != it->second.getlastmodifiedtime();
            
            if (needsHashCheck && file.getfilehash() != it->second.getfilehash()) {
                changes.emplace_back("[MODIFIED]", file.getfullpath());
            }
            oldMap.erase(it);
        }
    }

    for (const auto& [path, _] : oldMap) {
        changes.emplace_back("[DELETED]", path);
    }
}


const std::vector<std::pair<std::string, std::string>>& ChangeDetector::getChanges() const {
    return changes;
}

void ChangeDetector::printCLI() const {
    std::cout << "Status | File Path\n";
    std::cout << std::string(100,'-') << "\n";
    for(const auto& [status, path] : changes)
        std::cout << status << " | " << path << "\n";
}

std::string ChangeDetector::toCSV() const {
    std::stringstream ss;
    ss << "Status,File Path\n";
    for (const auto& [status, path] : changes)
        ss << "\"" << status << "\",\"" << path << "\"\n";
    return ss.str();
}


// void ChangeDetector::saveChangesCSV(const std::string& filename) const {
//     std::ofstream csv(filename);
//     csv << "Status,File Path\n";
//     for(const auto& [status, path] : changes)
//         csv << "\"" << status << "\",\"" << path << "\"\n";
// }

bool ChangeDetector::saveChangesCSV(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        Logger::logEvent("Error: Failed to open file for CSV output: " + filename);
        return false;
    }
    ofs << toCSV();
    return ofs.good();
}
