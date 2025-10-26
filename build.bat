@echo off
echo ==========================================
echo   Building FileTracker Project...
echo ==========================================
echo.

REM Compile all source files from src/ and include headers from include/
g++ -std=c++17 src/*.cpp -I include -o FileTracker.exe

if %errorlevel%==0 (
    echo.
    echo Compilation successful!
    echo ------------------------------------------
    echo To run: FileTracker.exe
    echo ------------------------------------------
) else (
    echo.
    echo Compilation failed. Check for errors.
)

pause
