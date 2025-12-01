#include "FileWatcher.h"
#include "Logger.h"
#include "ChangeDetector.h"
#include "DirectorySnapshot.h"
#include "Globals.h"
#include <iostream>
#include <thread>
#include <chrono>

FileWatcher::FileWatcher(const std::string& dir, int interval)
    : directoryPath(dir), intervalSeconds(interval < 1 ? 1 : interval), running(false), oldSnap(dir) {}

FileWatcher::~FileWatcher() {
    stop();
}

void FileWatcher::start() {
    if (running) return;
    running = true;

    // Make sure logs folder exists
    Logger::ensureLogFolder();

    // Log all existing files on start
    for (const auto& file : oldSnap.getFiles()) {
        std::string msg = "[EXISTING] " + file.getfullpath();
        std::cout << Logger::formatEvent(msg) << std::endl;
        Logger::logEvent(msg);
    }


    // Start watcher thread
    watcherThread = std::thread(&FileWatcher::watchLoop, this);
    std::cout << Logger::formatEvent("Started watching directory: " + directoryPath) << std::endl;
}

void FileWatcher::stop() {
    if (!running) return;
    running = false;
    if (watcherThread.joinable()) {
        watcherThread.join();
    }
    std::cout << "Stopped watching directory." << std::endl;
}

void FileWatcher::watchLoop() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));

        // Create a fresh snapshot of the directory
        DirectorySnapshot newSnap(directoryPath);

        // Detect changes compared to old snapshot
        ChangeDetector detector(oldSnap, newSnap);
        const auto& changes = detector.getChanges();

        // Log and print changes
        for (const auto& [status, path] : changes) {
            std::string msg = status + " " + path;

           if (showlivelogs) {
            std::lock_guard<std::mutex> lock(coutMutex);
            std::cout << Logger::formatEvent(msg) << std::endl;
           }
            
            Logger::logEvent(msg);
        }

        // Update old snapshot for next iteration
        oldSnap = newSnap;
    }
}
