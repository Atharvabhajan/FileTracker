#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>
#include <iomanip>
#include <sstream>

namespace Logger {

inline void ensureLogFolder() {
    if (!std::filesystem::exists("logs")) {
        std::filesystem::create_directory("logs");
    }
}

inline std::string getCurrentDate() {
    auto t = std::time(nullptr);
    std::tm tm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

inline std::string formatEvent(const std::string& message) {
    auto t = std::time(nullptr);
    std::tm tm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S") << " - " << message;
    return oss.str();
}

inline void logEvent(const std::string& message) {
    ensureLogFolder();
    std::string filename = "logs/tracker_" + getCurrentDate() + ".log";
    std::ofstream logFile(filename, std::ios::app);
    logFile << formatEvent(message) << "\n";
}
}
