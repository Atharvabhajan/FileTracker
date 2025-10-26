#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "FileWatcher.h"
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class CommandProcessor {
private:
    std::unique_ptr<FileWatcher> watcher;
    std::string currentDirectory;
    bool isRunning;

    // Command handlers
    void handleStart(const std::vector<std::string>& args);
    void handleStatus();
    void handleLog(const std::vector<std::string>& args);
    void handleDuplicates();
    void handleStop();
    void showHelp();

    // Helper functions
    static std::vector<std::string> splitCommand(const std::string& cmd);
    bool ensureWatcher() const;

public:
    CommandProcessor();
    ~CommandProcessor();

    void processCommand(int argc, char* argv[]);
    void processCommand(const std::string& command);
    void startInteractiveMode();
    bool isActive() const { return isRunning; }
};

#endif