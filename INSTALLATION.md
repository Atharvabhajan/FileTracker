# Detailed Installation Guide for FileTracker

## Building from Source

### Prerequisites
- C++17 or newer
- MinGW / GCC compiler
- Windows, Linux, or macOS

### Build Steps
1. Clone the repository:
```bash
git clone https://github.com/Atharvabhajan/FileTracker.git
cd FileTracker
```

2. Compile the source:
```bash
g++ -std=c++17 -pthread -o FileTracker src/*.cpp
```

## System Integration

### Windows

#### Method 1: Using Installer (Recommended)
1. Download the latest release from GitHub
2. Run the installer
3. Follow the installation wizard
   - The installer will automatically add FileTracker to your PATH
   - Creates start menu shortcuts
   - Sets up file associations

#### Method 2: Manual Installation
1. Create a directory for FileTracker:
```powershell
mkdir "C:\Program Files\FileTracker"
```

2. Copy the executable:
```powershell
copy FileTracker.exe "C:\Program Files\FileTracker"
```

3. Add to System PATH:
   - Open Start Menu
   - Search for "Environment Variables"
   - Click "Edit the system environment variables"
   - Click "Environment Variables" button
   - Under "System Variables", find and select "Path"
   - Click "Edit" → "New"
   - Add `C:\Program Files\FileTracker`
   - Click "OK" on all windows
   - Restart any open terminal windows

### Linux/macOS

#### Method 1: Using Package Manager (Coming Soon)
```bash
# For Ubuntu/Debian (Coming Soon)
sudo apt install filetracker

# For MacOS (Coming Soon)
brew install filetracker
```

#### Method 2: Manual Installation
1. Copy to system bin directory:
```bash
sudo cp FileTracker /usr/local/bin/
sudo chmod +x /usr/local/bin/FileTracker
```

## Verification

After installation, verify FileTracker is correctly installed:

1. Open a new terminal/command prompt
2. Run:
```bash
FileTracker --version
```

You should see the version number of FileTracker displayed.

## Usage After Installation

From any directory in your terminal:

```bash
# Start monitoring current directory
FileTracker start .

# Monitor specific directory
FileTracker start "path/to/directory"

# Get current status
FileTracker status

# View logs
FileTracker log
```

## Troubleshooting

### Common Issues

1. **"Command not found" error**
   - Verify PATH was set correctly
   - Try restarting your terminal
   - Check if the executable exists in the specified directory

2. **Permission Issues (Linux/macOS)**
   - Ensure proper execute permissions:
   ```bash
   chmod +x /usr/local/bin/FileTracker
   ```

3. **Windows PATH not updating**
   - Log out and log back in
   - Or restart your computer

### Getting Help

If you encounter any issues:
1. Check the [FAQ](./FAQ.md)
2. Open an issue on GitHub
3. Contact the maintainers