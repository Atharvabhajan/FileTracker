#pragma once
#include <string>
#include <thread>
#include <unordered_map>
#include "DirectorySnapshot.h"

class FileWatcher {
private:
    std::string directoryPath;
    int intervalSeconds;
    bool running;
    std::thread watcherThread;
    DirectorySnapshot oldSnap;

    void watchLoop();

public:
    FileWatcher(const std::string& dir, int interval = 5);
    ~FileWatcher();

    void start();
    void stop();
    bool isActive() const { return running; }
};
