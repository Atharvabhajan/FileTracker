# FileTracker System Usage Guide

## Table of Contents
1. Introduction
2. Prerequisites
3. Installation
4. Quick Start
5. Detailed Commands
6. Configuration
7. Troubleshooting
8. Best Practices

---

## Introduction

FileTracker is a real-time directory monitoring and logging system built in C++. It continuously monitors file changes in a directory and logs every detected event. This guide provides comprehensive instructions for new users to quickly understand and use FileTracker effectively.

---

## Prerequisites

Before installing FileTracker, ensure you have:

- C++17 or newer compiler
- MinGW (Windows) or GCC (Linux/macOS)
- Administrator or sudo privileges for system-wide installation
- At least 100 MB of disk space
- Active terminal or command prompt access

---

## Installation

### Windows Installation

#### Option 1: Automatic Installation (Recommended)
1. Download FileTracker.exe from the GitHub releases page
2. Create directory: C:\Program Files\FileTracker
3. Copy FileTracker.exe to this directory
4. Add to System PATH:
   - Open Start Menu
   - Type "Environment Variables"
   - Click "Edit the system environment variables"
   - Click "Environment Variables" button
   - Under System Variables, select "Path"
   - Click "Edit" and then "New"
   - Enter: C:\Program Files\FileTracker
   - Click OK on all dialogs
   - Close and restart your terminal

#### Option 2: Building from Source
1. Clone repository:
   git clone https://github.com/Atharvabhajan/FileTracker.git
   cd FileTracker

2. Compile:
   g++ -std=c++17 -pthread -o FileTracker src/*.cpp

3. Follow Option 1 steps to add to PATH

### Linux/macOS Installation

#### Option 1: System-Wide Installation
1. Clone and build:
   git clone https://github.com/Atharvabhajan/FileTracker.git
   cd FileTracker
   g++ -std=c++17 -pthread -o FileTracker src/*.cpp

2. Install to system path:
   sudo cp FileTracker /usr/local/bin/
   sudo chmod +x /usr/local/bin/FileTracker

3. Verify installation:
   FileTracker --version

#### Option 2: Local Installation
1. Build as described above
2. Add to your PATH in ~/.bashrc or ~/.zshrc:
   export PATH="$PATH:/path/to/FileTracker"
3. Reload shell:
   source ~/.bashrc

---

## Quick Start

### First Time Usage

1. Open terminal or command prompt
2. Navigate to directory you want to monitor:
   cd "C:\Users\YourName\Documents"

3. Start FileTracker:
   FileTracker start .

4. Observe output showing monitoring has started
5. Try creating, modifying, or deleting files in this directory
6. View detected changes in real-time

### Basic Commands

Start monitoring:
  FileTracker start "C:\path\to\directory"

Check status:
  FileTracker status

View activity logs:
  FileTracker log

Stop monitoring:
  FileTracker stop

Exit program:
  FileTracker exit

---

## Detailed Commands

### START Command
Purpose: Begin monitoring a directory for changes

Syntax: FileTracker start <directory_path>

Examples:
  FileTracker start .
  FileTracker start "C:\Users\HP\Documents"
  FileTracker start "/home/user/projects"

Options:
  . = Current directory
  Relative paths work if valid from current location
  Absolute paths work from any location
  Paths with spaces must be enclosed in quotes

What happens:
  - FileTracker scans directory structure
  - Creates baseline snapshot of all files
  - Begins continuous monitoring
  - Logs initial scan results

### STATUS Command
Purpose: Display current monitoring status and recent activity

Syntax: FileTracker status

Output includes:
  - Current monitoring directory
  - Monitoring status (active/inactive)
  - Number of files in directory
  - Recent changes detected
  - Last update timestamp

Use when:
  - You need quick overview of monitoring state
  - Troubleshooting monitoring issues
  - Checking recent file activities

### LOG Command
Purpose: View detailed activity logs with optional filtering

Syntax: FileTracker log [filter_type]

Filter types:
  ADDED = Show only file creation events
  MODIFIED = Show only file modification events
  DELETED = Show only file deletion events
  No filter = Show all events

Examples:
  FileTracker log
  FileTracker log ADDED
  FileTracker log MODIFIED
  FileTracker log DELETED

Log contains:
  - Timestamp of change
  - Type of change (ADDED/MODIFIED/DELETED)
  - File path
  - File size (if applicable)
  - Hash value for duplicate detection

### DUPLICATES Command
Purpose: Find duplicate files in monitored directory using SHA256 hashing

Syntax: FileTracker duplicates

Output shows:
  - Hash value
  - Files with matching hash
  - File sizes
  - File locations

Use when:
  - Searching for duplicate files
  - Cleaning up redundant files
  - Storage optimization
  - Finding duplicate documents

### STOP Command
Purpose: Stop monitoring the current directory

Syntax: FileTracker stop

Effects:
  - Monitoring ceases immediately
  - Current logs are preserved
  - No new events are logged
  - Monitoring can be resumed with start command

### HELP Command
Purpose: Display available commands and usage information

Syntax: FileTracker help

Shows:
  - All available commands
  - Syntax for each command
  - Brief description of functionality
  - Examples of usage

---

## Configuration

### Log File Location
Logs are automatically stored in:
  Windows: C:\Users\YourName\AppData\Local\FileTracker\logs\
  Linux: ~/.local/share/filetracker/logs/
  macOS: ~/Library/Logs/FileTracker/

### Log File Format
Each log entry contains:
  [TIMESTAMP] EVENT_TYPE FILE_PATH FILE_SIZE HASH_VALUE

Example:
  [2025-12-02 10:30:45] ADDED document.pdf 2048 abc123def456

### Monitoring Multiple Directories
To monitor multiple directories:
  1. Open multiple terminal instances
  2. Run FileTracker start in each with different paths
  3. Each maintains separate logs
  4. Logs are automatically organized by directory

### Persistent Monitoring
To keep FileTracker running in background:

Windows:
  - Use Task Scheduler to run FileTracker at startup
  - Or use background service mode (if available)

Linux/macOS:
  - Create systemd service file
  - Use nohup command: nohup FileTracker start . &
  - Or create background process

---

## Troubleshooting

### Issue: "Command not found" error

Cause: FileTracker not in system PATH

Solution:
  1. Verify installation location exists
  2. Re-add to PATH using instructions above
  3. Restart terminal completely
  4. On Windows, try logging out and in again
  5. Run: echo %PATH% (Windows) or echo $PATH (Linux/Mac) to verify

### Issue: Permission Denied (Linux/macOS)

Cause: Executable lacks proper permissions

Solution:
  1. Check permissions: ls -l /usr/local/bin/FileTracker
  2. Fix permissions: sudo chmod +x /usr/local/bin/FileTracker
  3. Verify: FileTracker --version

### Issue: Directory Not Found

Cause: Invalid path specified

Solution:
  1. Use absolute paths instead of relative paths
  2. Enclose paths with spaces in quotes
  3. Verify path exists: cd "path/to/directory"
  4. Use forward slashes on Linux/macOS
  5. Use backslashes on Windows

### Issue: No Changes Detected

Cause: Changes happening too quickly or monitoring not started properly

Solution:
  1. Verify monitoring is active: FileTracker status
  2. Create test file to confirm detection works
  3. Check file permissions
  4. Ensure you have read permissions on directory
  5. Try different directory to test

### Issue: High CPU Usage

Cause: Monitoring very large directory or rapid file changes

Solution:
  1. Monitor smaller directory instead
  2. Exclude certain file types from monitoring
  3. Reduce monitoring frequency if configurable
  4. Close other applications
  5. Check system resources: Task Manager (Windows) or top (Linux/Mac)

### Issue: Logs Growing Too Large

Cause: Too many file changes being logged

Solution:
  1. Archive old log files manually
  2. Use log filtering to view specific events only
  3. Monitor smaller directory
  4. Configure log rotation if available

---

## Best Practices

### Security
1. Only monitor directories you have permission to access
2. Keep logs in secure location
3. Review logs regularly for unauthorized changes
4. Be cautious with monitored directories containing sensitive data
5. Use strong file permissions on log files

### Performance
1. Monitor most specific directory needed, not entire drive
2. Start with small directories, scale up gradually
3. Monitor during off-peak hours if possible
4. Close FileTracker when not needed
5. Regularly archive and clean old logs

### Maintenance
1. Review logs regularly for patterns
2. Archive logs weekly or monthly
3. Document important file changes
4. Test recovery procedures
5. Keep FileTracker updated to latest version

### Documentation
1. Record which directories you are monitoring
2. Note start and end times of monitoring
3. Document any important changes detected
4. Keep audit trail of monitoring activities
5. Share logs with relevant team members

### Workflow Integration
1. Use FileTracker for development file tracking
2. Monitor backup directories before sync
3. Track uploads to shared directories
4. Monitor configuration file changes
5. Integrate with backup or version control workflows

---

## Additional Resources

Documentation:
  - README.md: Project overview and features
  - CONTRIBUTING.md: How to contribute to project
  - INSTALLATION.md: Detailed installation instructions
  - PROJECT_STRUCTURE.md: Technical architecture details

Support:
  - GitHub Issues: Report bugs or request features
  - GitHub Discussions: Ask questions and get help
  - Code of Conduct: Community guidelines

License:
  - MIT License: See LICENSE file for details
