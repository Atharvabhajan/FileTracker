# Contributing to FileTracker

Thank you for your interest in contributing to FileTracker! We welcome all contributions from the community.

## Code of Conduct

By participating in this project, you agree to maintain a respectful and inclusive environment for everyone.

## How to Contribute

1. **Fork the Repository**
   * Fork the repository to your GitHub account
   * Clone your fork locally: `git clone https://github.com/yourusername/FileTracker.git`

2. **Create a Branch**
   * Create a branch for your feature or fix:
   ```bash
   git checkout -b feature-name
   ```
   * Use descriptive branch names (e.g., `fix-memory-leak`, `add-email-notifications`)

3. **Make Your Changes**
   * Follow the existing code style and conventions
   * Write clear, commented code
   * Test your changes thoroughly
   * Update documentation if needed

4. **Commit Your Changes**
   * Write clear, concise commit messages
   * Use the present tense ("Add feature" not "Added feature")
   * Reference issue numbers in your commits if applicable

5. **Submit a Pull Request**
   * Push to your fork: `git push origin feature-name`
   * Create a Pull Request from your fork to our main repository
   * Describe your changes in detail
   * Link any related issues

## Development Setup

1. Ensure you have the prerequisites:
   * C++17 or newer
   * MinGW / GCC compiler
   * Windows, Linux, or macOS

2. Build the project:
   ```bash
   g++ -std=c++17 -pthread -o FileTracker main.cpp FileWatcher.cpp DirectorySnapshot.cpp ChangeDetector.cpp Logger.cpp CommandProcessor.cpp
   ```

## Code Guidelines

* Follow C++17 best practices
* Use consistent indentation (4 spaces)
* Add comments for complex logic
* Include unit tests for new features
* Update documentation for API changes

## Need Help?

* Create an issue for bug reports or feature requests
* Ask questions in the discussions section
* Review existing issues and pull requests

## License

By contributing to FileTracker, you agree that your contributions will be licensed under the MIT License.
