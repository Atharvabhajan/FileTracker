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
  Run interactively
./FileTracker

Run directly with a directory
./FileTracker start "C:\Users\HP\Documents\admission_doc"

---

## Commands
```bash
Command	           Description
start <dir>	       Start watching the given directory
status	           Show active status and recent changes
log [filter]	     View logs (optionally filter by ADDED / MODIFIED / DELETED)
duplicates	       Find duplicate files by hash
stop	             Stop watching
help	             Show help message
exit	             Exit program
```
---
## Contributing

We welcome contributions! Please follow these steps:
Fork the repository
Create a new branch (git checkout -b feature-name)
Make your changes
Commit your changes (git commit -m "Add feature")
Push to your branch (git push origin feature-name)
Create a Pull Request

Please make sure your code follows existing style and is tested.

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
