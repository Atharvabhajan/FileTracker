# 🧩 FileTracker

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

**FileTracker** is a **real-time directory monitoring and logging system** built in **C++**.  
It continuously monitors file changes (creation, modification, deletion) in a directory and logs every detected event.  
Includes a **command-line interface (CLI)** for controlling the watcher and analyzing files.

This project is **open-source** — feel free to use, modify, and contribute!

---

## 📜 Table of Contents
1. [Overview](#-overview)
2. [Features](#-features)
3. [Installation](#-installation)
4. [Steps](#-steps)
5. [Usage](#-usage)
6. [Commands](#-commands)
7. [Contributing](#-contributing)
8. [License](#-license)  
9. [Future Enhancements](#-future-enhancements)
10. [Contributors](#-contributors)

---

## 🔍 Overview
**FileTracker** is a C++ utility that monitors any directory for:
- File **creation**
- File **modification**
- File **deletion**
- **Duplicate detection** using SHA256 hashing

The system is useful for IT administrators, developers, or security analysts who need to track filesystem activities in real time.


---

## ✨ Features
✅ Detects file creation, modification, and deletion  
✅ Tracks duplicates based on file hashes (SHA256)  
✅ Logs all activities in a timestamped log file  
✅ Interactive **CLI interface** for control  
✅ Efficient and multithreaded  
✅ Modular architecture for scalability  

---

## ⚙️ Installation

 Prerequisites
- C++17 or newer  
- MinGW / GCC compiler  
- Windows, Linux, or macOS

---

## Steps
```bash
git clone https://github.com/yourusername/FileTracker.git
cd FileTracker
g++ -std=c++17 -pthread -o FileTracker main.cpp FileWatcher.cpp DirectorySnapshot.cpp ChangeDetector.cpp Logger.cpp CommandProcessor.cpp
```
---

## Usage

### Basic Usage
```bash
# Run interactively
./FileTracker

# Run directly with a directory
./FileTracker start "C:\Users\HP\Documents\admission_doc"
```

### Global Installation (Command Line Access from Anywhere)

#### Windows
1. Copy the `FileTracker.exe` to a permanent location (e.g., `C:\Program Files\FileTracker\`)
2. Add to PATH:
   - Open Start Menu and search for "Environment Variables"
   - Click "Edit the system environment variables"
   - Click "Environment Variables" button
   - Under "System Variables", find and select "Path"
   - Click "Edit" → "New"
   - Add your FileTracker directory (e.g., `C:\Program Files\FileTracker`)
   - Click "OK" on all windows
   - Restart your terminal/command prompt

#### Linux/macOS
1. Copy the FileTracker executable to `/usr/local/bin/`:
```bash
sudo cp FileTracker /usr/local/bin/
sudo chmod +x /usr/local/bin/FileTracker
```

### Using from Command Line
After adding to PATH, you can use FileTracker from any directory:
```bash
# Start monitoring current directory
FileTracker start .

# Monitor specific directory
FileTracker start "path/to/directory"

# Get status
FileTracker status

# View logs
FileTracker log
```

---

## Commands
```bash
Command	           Description
start <dir>	       Start watching the given directory
status	           Show active status and recent changes
log [filter]	     View logs (optionally filter by ADDED / MODIFIED / DELETED)
prompt logs         start logging on window
duplicates	       Find duplicate files by hash
stop	             Stop watching
help	             Show help message
exit	             Exit program
```
---
## Contributing

We love your input! We want to make contributing to FileTracker as easy and transparent as possible, whether it's:

- Reporting a bug 🐛
- Discussing the current state of the code 💬
- Submitting a fix 🔧
- Proposing new features ✨
- Becoming a maintainer 🌟

See [CONTRIBUTING.md](CONTRIBUTING.md) for detailed contribution guidelines.

### Bug Reports 🐛
We use GitHub issues to track public bugs. Report a bug by [opening a new issue](../../issues/new); it's that easy!

### Feature Requests 💡
Have a great idea for FileTracker? We'd love to hear it! Open an issue with the tag "enhancement".

### Good First Issues 🌱
Looking to contribute? Check out our [good first issues](../../issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22) for beginner-friendly tasks. Here are some examples:
- Add file size monitoring
- Implement file type filtering
- Add basic test cases
- Improve error messages
- Add configuration file support

---

## License
This project is licensed under the MIT License — see the LICENSE
 file for details.

 ---
 
## Future Enhancements

Real-time GUI dashboard

Email alerts for critical file changes

Network monitoring and central log storage

Machine learning model to detect unusual change patterns

Integration with cloud drives (Google Drive, OneDrive)

---

## Contributors

Atharva Bhajan — Developer & Architect
