#include "CommandProcessor.h"
#include "Logger.h"
#include "Globals.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <filesystem>

namespace fs = std::filesystem;

CommandProcessor::CommandProcessor() : isRunning(true) {}

CommandProcessor::~CommandProcessor() {
    if (watcher) {
        std::cout<<"destroyed in the destructor!";
        watcher->stop();
    }
}

void CommandProcessor::processCommand(int argc, char* argv[]) {
    if (argc < 2) {
        startInteractiveMode();
        return;
    }

    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    std::string command = args[0];
    args.erase(args.begin());

    if (command == "start") {
        handleStart(args);
    } else if (command == "status") {
        handleStatus();
    } else if (command == "log") {
        handleLog(args);
    } else if (command == "duplicates") {
        handleDuplicates();
    } else if (command == "stop") {
        handleStop();
    } else if (command == "help") {
        showHelp();
    } else {
        std::cout << "Unknown command. Type 'help' for usage.\n";
    }
}

void CommandProcessor::processCommand(const std::string& command) {
    auto args = splitCommand(command);
    if (args.empty()) return;

    std::string cmd = args[0];
    args.erase(args.begin());

    if (cmd == "start") {
        handleStart(args);
    } else if (cmd == "status") {
        handleStatus();
    } else if (cmd == "log") {
        handleLog(args);
    } else if (cmd == "duplicates") {
        handleDuplicates();
    } else if (cmd == "stop") {
        handleStop();
    } else if (cmd == "help") {
        showHelp();
    } else if (cmd == "exit" || cmd == "quit") {
        isRunning = false;
    } else if (cmd == "prompt" && !args.empty() && args[0] == "logs") {
        showlivelogs = true;
        std::cout << "Starting log prompt. Type 'exit' or 'stop' to stop logging.\n";
        std::string line;
        while (true) {
            std::cout << "log> ";
            std::getline(std::cin, line);
            if (line == "stop" || line == "exit") {
                showlivelogs = false;
                std::cout << "Exiting log prompt.\n";
                break;
            } 
            handleLog({line});
        }
    }
    else {
        std::cout << "Unknown command. Type 'help' for usage.\n";
    }
}

void CommandProcessor::startInteractiveMode() {
    std::cout << "FileTracker Interactive Mode\n";
    std::cout << "Type 'help' for commands, 'exit' to quit\n\n";

    std::string command;
    while (isRunning) {
        std::cout << "track> ";
        std::getline(std::cin, command);
        processCommand(command);
    }
}

void CommandProcessor::handleStart(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Error: Directory path required\n";
        return;
    }

    std::string path = args[0];
    if (!fs::exists(path)) {
        std::cout << "Error: Directory does not exist: " << path << "\n";
        return;
    }

    if (!fs::is_directory(path)) {
        std::cout << "Error: Path is not a directory: " << path << "\n";
        return;
    }

    if (watcher) {
        watcher->stop();
    }

    currentDirectory = path;
    watcher = std::make_unique<FileWatcher>(path, 1);
    watcher->start();
    std::cout << "Started watching directory: " << path << "\n";
}

void CommandProcessor::handleStatus() {
    if (!ensureWatcher()) return;

    std::cout << "\nCurrent Status:\n";
    std::cout << "Watching directory: " << currentDirectory << "\n";
    std::cout << "Active: " << (watcher && watcher->isActive() ? "Yes" : "No") << "\n\n";
    
    // to get current snapshot stats
    DirectorySnapshot snapshot(currentDirectory);
    const auto& files = snapshot.getFiles();
    
    size_t totalFiles = files.size();
    uintmax_t totalSize = 0;
    
    for (const auto& file : files) {
        totalSize += file.getfilesize();
    }

    std::cout << "Statistics:\n";
    std::cout << "Total files: " << totalFiles << "\n";
    std::cout << "Total size: " << (totalSize / 1024.0 / 1024.0) << " MB\n\n";

    std::cout << "Recent Changes:\n";
    // Display last few entries from the log
    std::string logPath = "logs/tracker_" + Logger::getCurrentDate() + ".log";
    std::ifstream log(logPath);
    std::vector<std::string> lastLines;
    std::string line;
    
    while (std::getline(log, line)) {
        lastLines.push_back(line);
        if (lastLines.size() > 5) {
            lastLines.erase(lastLines.begin());
        }
    }

    for (const auto& l : lastLines) {
        std::cout << l << "\n";
    }
}

void CommandProcessor::handleLog(const std::vector<std::string>& args) {
    std::string logPath = "logs/tracker_" + Logger::getCurrentDate() + ".log";
    std::ifstream log(logPath);
    
    if (!log) {
        std::cout << "No log file found for today\n";
        return;
    }

    std::string filter;
    if (!args.empty()) {
        filter = args[0];
        std::transform(filter.begin(), filter.end(), filter.begin(), ::toupper);
    }

    std::string line;
    while (std::getline(log, line)) {
        if (filter.empty() || line.find(filter) != std::string::npos) {
            std::cout << line << "\n";
        }
    }
}

void CommandProcessor::handleDuplicates() {
    if (!ensureWatcher()) return;

    DirectorySnapshot snapshot(currentDirectory);
    const auto& files = snapshot.getFiles();
    
    std::unordered_map<std::string, std::vector<std::string>> hashGroups;
    
    // Group files by hash
    for (const auto& file : files) {
        hashGroups[file.getfilehash()].push_back(file.getfullpath());
    }

    // Display duplicates
    bool foundDuplicates = false;
    for (const auto& [hash, paths] : hashGroups) {
        if (paths.size() > 1) {
            foundDuplicates = true;
            std::cout << "\nDuplicate files (SHA256: " << hash.substr(0, 8) << "...):\n";
            for (const auto& path : paths) {
                std::cout << "  " << path << "\n";
            }
        }
    }

    if (!foundDuplicates) {
        std::cout << "No duplicate files found.\n";
    }
}

void CommandProcessor::handleStop() {
    if (watcher) {
        watcher->stop();
        std::cout << "Stopped watching directory: " << currentDirectory << "\n";
    } else {
        std::cout << "No active watcher.\n";
    }
}

void CommandProcessor::showHelp() {
    std::cout << "\nFileTracker Commands:\n";
    std::cout << "  start <dir>    Start watching directory <dir>\n";
    std::cout << "  status         Show current watching status and recent changes\n";
    std::cout << "  log [filter]   Display log (optionally filtered by type)\n";
    std::cout << "  prompt logs    start prompting the logs \n";
    std::cout << "  duplicates     Find duplicate files in watched directory\n";
    std::cout << "  stop           Stop watching current directory\n";
    std::cout << "  help           Show this help message\n";
    std::cout << "  exit           Exit the program\n\n";
}

std::vector<std::string> CommandProcessor::splitCommand(const std::string& cmd) {
    std::vector<std::string> args;
    std::istringstream iss(cmd);
    std::string arg;
    
    while (iss >> arg) {
        args.push_back(arg);
    }
    
    return args;
}

bool CommandProcessor::ensureWatcher() const {
    if (!watcher) {
        std::cout << "Error: No directory being watched. Use 'start <dir>' first.\n";
        return false;
    }
    return true;
}