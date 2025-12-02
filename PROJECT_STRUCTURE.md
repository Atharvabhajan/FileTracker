# FileTracker Project Structure

## Table of Contents
1. Directory Layout
2. Core Components
3. File Descriptions
4. Data Flow Architecture
5. Dependencies
6. Build System
7. Extension Points

---

## Directory Layout

FileTracker/
├── src/                          # Source code directory
│   ├── FileTracker.cpp           # Main entry point
│   ├── FileWatcher.cpp           # File system monitoring
│   ├── FileWatcher.h
│   ├── DirectorySnapshot.cpp     # Directory state snapshot
│   ├── DirectorySnapshot.h
│   ├── ChangeDetector.cpp        # Change analysis
│   ├── ChangeDetector.h
│   ├── Logger.cpp                # Logging system
│   ├── Logger.h
│   ├── CommandProcessor.cpp      # CLI command handling
│   ├── CommandProcessor.h
│   ├── FileInfo.cpp              # File metadata
│   ├── FileInfo.h
│   ├── SHA256.cpp                # Hash calculation
│   └── SHA256.h
├── include/                      # Header files
│   ├── ChangeDetector.h
│   ├── CommandProcessor.h
│   ├── DirectorySnapshot.h
│   ├── FileInfo.h
│   ├── FileWatcher.h
│   ├── ISerializable.h
│   ├── Logger.h
│   └── SHA256.h
├── logs/                         # Generated log files
├── .github/                      # GitHub specific files
│   ├── workflows/
│   │   └── cpp_build.yml         # CI/CD workflow
│   ├── ISSUE_TEMPLATE/
│   │   ├── bug_report.md
│   │   └── feature_request.md
│   └── pull_request_template.md
├── README.md                     # Project overview
├── INSTALLATION.md               # Installation guide
├── SYSTEM_USAGE_GUIDE.md         # System usage documentation
├── PROJECT_STRUCTURE.md          # This file
├── CONTRIBUTING.md               # Contribution guidelines
├── CODE_OF_CONDUCT.md            # Community guidelines
├── LICENSE                       # MIT License
├── build.bat                     # Windows build script
└── FileTracker_Project_Report.docx # Formal project report

---

## Core Components

### 1. Main Entry Point (FileTracker.cpp)

Purpose: Program initialization and control flow

Responsibilities:
  - Parse command-line arguments
  - Initialize all subsystems
  - Route user input to CommandProcessor
  - Manage program lifecycle
  - Handle graceful shutdown

Key Functions:
  main() - Entry function receiving command-line arguments
  initializeSystem() - Setup all modules
  shutdownSystem() - Cleanup and exit

### 2. FileWatcher (FileWatcher.cpp / FileWatcher.h)

Purpose: Monitor file system for changes in real-time

Responsibilities:
  - Detect file creation events
  - Detect file modification events
  - Detect file deletion events
  - Trigger callbacks when changes occur
  - Handle recursive directory monitoring
  - Manage system resources efficiently

Technical Details:
  Platform-specific implementation:
    Windows: Uses ReadDirectoryChangesW API
    Linux: Uses inotify API
    macOS: Uses FSEvents or kqueue

Key Classes:
  FileWatcher - Main monitoring class
  ChangeEvent - Represents a detected change

Key Functions:
  startWatching(path) - Begin monitoring directory
  stopWatching() - Stop monitoring
  onFileCreated() - Callback for new files
  onFileModified() - Callback for changed files
  onFileDeleted() - Callback for deleted files

### 3. DirectorySnapshot (DirectorySnapshot.cpp / DirectorySnapshot.h)

Purpose: Create and manage snapshots of directory state

Responsibilities:
  - Scan entire directory structure
  - Store file metadata (name, size, timestamp, hash)
  - Calculate file hashes for duplicate detection
  - Compare snapshots to find differences
  - Track file hierarchy

Data Structure:
  Snapshot contains:
    - List of all files with full paths
    - File sizes
    - Modification timestamps
    - SHA256 hash values
    - File permissions (Unix systems)

Key Classes:
  DirectorySnapshot - Represents directory state at point in time
  FileInfo - Metadata about single file

Key Functions:
  createSnapshot(path) - Scan and store directory state
  getFileInfo(filePath) - Get metadata for specific file
  calculateHash(filePath) - Compute SHA256 hash
  getAllFiles() - Return all files in snapshot

### 4. ChangeDetector (ChangeDetector.cpp / ChangeDetector.h)

Purpose: Analyze differences between directory states

Responsibilities:
  - Compare current and previous snapshots
  - Identify newly created files
  - Identify modified files
  - Identify deleted files
  - Detect duplicate files
  - Build change report

Logic:
  1. Compare file lists from two snapshots
  2. Files in new but not old = ADDED
  3. Files in both with different hash = MODIFIED
  4. Files in old but not new = DELETED
  5. Multiple files with same hash = DUPLICATES

Key Classes:
  ChangeDetector - Main analysis engine
  ChangeReport - Detailed results of analysis
  Change - Single detected change

Key Functions:
  detectChanges(oldSnapshot, newSnapshot) - Compare states
  findAddedFiles() - List newly created files
  findModifiedFiles() - List changed files
  findDeletedFiles() - List removed files
  findDuplicates() - Find files with identical content

### 5. FileInfo (FileInfo.cpp / FileInfo.h)

Purpose: Store and manage file metadata

Responsibilities:
  - Store file path, size, and timestamp
  - Store file hash value
  - Provide comparison operations
  - Enable serialization for storage

Key Classes:
  FileInfo - Single file metadata container

Key Functions:
  getPath() - Return file path
  getSize() - Return file size
  getModificationTime() - Return last modified timestamp
  getHash() - Return SHA256 hash
  operator== - Compare two FileInfo objects

### 6. SHA256 (SHA256.cpp / SHA256.h)

Purpose: Calculate SHA256 cryptographic hashes

Responsibilities:
  - Compute SHA256 hash of files
  - Generate hash from data blocks
  - Provide fast hash computation
  - Enable duplicate detection

Key Classes:
  SHA256 - Hash computation engine

Key Functions:
  hashFile(filePath) - Compute hash of file
  hashData(data) - Compute hash of data block
  hexdigest() - Return hash as hexadecimal string

### 7. Logger (Logger.cpp / Logger.h)

Purpose: Record all file system events to persistent storage

Responsibilities:
  - Write events to log files
  - Format log entries with timestamps
  - Implement log rotation (prevent overflow)
  - Search and filter logs
  - Provide log statistics

Log Format:
  [YYYY-MM-DD HH:MM:SS] EVENT_TYPE | FILE_PATH | FILE_SIZE | FILE_HASH

Log Location:
  Windows: C:\Users\YourName\AppData\Local\FileTracker\logs\
  Linux: ~/.local/share/filetracker/logs/
  macOS: ~/Library/Logs/FileTracker/

Log File Naming:
  filetracker_YYYYMMDD.log - Daily log files
  filetracker.log - Current log

Key Classes:
  Logger - Main logging engine
  LogEntry - Single log record

Key Functions:
  log(event) - Write event to log
  openLogFile(date) - Open or create log file
  searchLogs(filter) - Find entries matching criteria
  getStatistics() - Count events by type
  rotateLogFiles() - Archive old logs

### 8. CommandProcessor (CommandProcessor.cpp / CommandProcessor.h)

Purpose: Process and execute user commands from CLI

Responsibilities:
  - Parse user input
  - Validate commands
  - Execute appropriate actions
  - Display results to user
  - Manage user session

Commands Supported:
  start <path> - Begin monitoring directory
  status - Show current monitoring state
  log [filter] - Display activity logs
  duplicates - Find duplicate files
  stop - Stop monitoring
  help - Show command list
  exit - Exit program

Key Classes:
  CommandProcessor - Command execution engine
  Command - Abstract command class
  StartCommand, StopCommand, etc. - Specific commands

Key Functions:
  processCommand(input) - Parse and execute command
  printHelp() - Display help information
  printStatus() - Show current state
  printLogs(filter) - Display filtered logs

### 9. ISerializable (ISerializable.h)

Purpose: Provide interface for serializable objects

Responsibilities:
  - Define serialization contracts
  - Enable data persistence
  - Support data exchange

Key Classes:
  ISerializable - Abstract interface

Key Functions:
  serialize() - Convert to storable format
  deserialize() - Restore from stored format

---

## Data Flow Architecture

### Monitoring Flow
1. User starts FileTracker with directory path
2. DirectorySnapshot creates initial snapshot
3. FileWatcher begins monitoring specified directory
4. When file changes detected:
   a. FileWatcher notifies ChangeDetector
   b. ChangeDetector compares with last snapshot
   c. Logger records event with timestamp
   d. DirectorySnapshot updated

### Command Flow
1. User enters command in CLI
2. CommandProcessor parses input
3. Command validated against available options
4. Appropriate module invoked (Logger, FileWatcher, etc.)
5. Results formatted and displayed to user

### Log Query Flow
1. User requests log view or filter
2. Logger reads log file from disk
3. Entries parsed and filtered
4. Results sorted by timestamp
5. Formatted output displayed to user

---

## Dependencies

### External Libraries
None - FileTracker uses only C++ Standard Library

### Standard Library Components Used
<iostream> - Console input/output
<fstream> - File operations
<vector> - Dynamic arrays
<string> - String operations
<map> - Hash-based storage
<thread> - Multithreading
<mutex> - Thread synchronization
<chrono> - Time and date handling
<functional> - Function callbacks
<algorithm> - Standard algorithms
<filesystem> - File system operations (C++17)

### System APIs Used
Windows:
  - ReadDirectoryChangesW (directory monitoring)
  - Windows.h (system interfaces)
  - Shlobj.h (special folders)

Linux:
  - inotify.h (file monitoring)
  - unistd.h (POSIX operations)
  - sys/inotify.h (Linux-specific)

macOS:
  - CoreServices.framework (FSEvents)
  - unistd.h (POSIX operations)

---

## Build System

### Current Build Process
Command: g++ -std=c++17 -pthread -o FileTracker src/*.cpp

Components:
  -std=c++17: Use C++17 standard
  -pthread: Link threading library
  -o FileTracker: Output executable name
  src/*.cpp: Compile all source files

### Windows Build Script
File: build.bat
Features:
  - Automatic compilation
  - Error detection
  - Executable placement
  - Optional installation

Usage:
  build.bat

### Compilation Order
1. All .cpp files compiled to object files
2. Object files linked together
3. Final executable created

---

## Extension Points

### Adding New Commands
1. Create new class inheriting from Command
2. Implement execute() method
3. Register in CommandProcessor
4. Add help text

### Adding New Monitoring Features
1. Extend FileWatcher class
2. Add new event type
3. Update ChangeDetector to handle event
4. Add logging for new event

### Adding New Log Filters
1. Extend Logger::searchLogs() method
2. Define filter criteria
3. Implement filtering logic
4. Update help documentation

### Adding Platform Support
1. Create platform-specific FileWatcher implementation
2. Use preprocessor directives for compilation
3. Test on target platform
4. Update installation guides

### Performance Optimization
1. Implement incremental hashing for large files
2. Add caching for directory structures
3. Implement batch event processing
4. Add configurable monitoring intervals

---

## Key Design Patterns

### Observer Pattern
FileWatcher notifies ChangeDetector when changes occur

### Singleton Pattern
Logger instance shared across application

### Strategy Pattern
Different file comparison strategies possible

### Template Method Pattern
Command base class defines execution flow

### Factory Pattern
Create appropriate FileWatcher for platform

---

## File Relationships

```
FileTracker.cpp (main)
    |
    +-- CommandProcessor --> FileWatcher
    |                     --> Logger
    |                     --> DirectorySnapshot
    |
    +-- FileWatcher --> FileInfo
    |             --> SHA256
    |
    +-- DirectorySnapshot --> FileInfo
    |                     --> SHA256
    |
    +-- ChangeDetector --> DirectorySnapshot
    |               --> Logger
    |
    +-- Logger --> FileInfo
```

---

## Conclusion

FileTracker architecture is modular and extensible. Each component has clear responsibility. Data flows logically from file system monitoring through analysis to persistent logging. Design supports future enhancements and platform additions.
