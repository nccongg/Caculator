@echo off
REM Build script for STM32 Calculator Demo on Windows
REM This script builds the demo program using MinGW or Visual Studio compiler

echo === STM32 Calculator Demo Build Script ===

REM Check if g++ is available
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found!
    echo Please install MinGW-w64 or Visual Studio Build Tools
    echo.
    echo For MinGW-w64:
    echo   1. Download from https://www.mingw-w64.org/
    echo   2. Add MinGW bin directory to PATH
    echo.
    echo For Visual Studio Build Tools:
    echo   1. Install Visual Studio Build Tools
    echo   2. Use Developer Command Prompt
    pause
    exit /b 1
)

echo Found g++ compiler
echo.

REM Create build directory
if not exist build mkdir build

REM Compile source files
echo Compiling source files...
g++ -std=c++11 -Wall -Wextra -g -ICore/Inc -c demo.cpp -o build/demo.o
if %errorlevel% neq 0 (
    echo Error compiling demo.cpp
    pause
    exit /b 1
)

g++ -std=c++11 -Wall -Wextra -g -ICore/Inc -c Core/Src/calculator.cpp -o build/calculator.o
if %errorlevel% neq 0 (
    echo Error compiling calculator.cpp
    pause
    exit /b 1
)

g++ -std=c++11 -Wall -Wextra -g -ICore/Inc -c Core/Src/display.cpp -o build/display.o
if %errorlevel% neq 0 (
    echo Error compiling display.cpp
    pause
    exit /b 1
)

g++ -std=c++11 -Wall -Wextra -g -ICore/Inc -c Core/Src/keypad.cpp -o build/keypad.o
if %errorlevel% neq 0 (
    echo Error compiling keypad.cpp
    pause
    exit /b 1
)

g++ -std=c++11 -Wall -Wextra -g -ICore/Inc -c mock_hal.cpp -o build/mock_hal.o
if %errorlevel% neq 0 (
    echo Error compiling mock_hal.cpp
    pause
    exit /b 1
)

echo All source files compiled successfully!
echo.

REM Link object files
echo Linking object files...
g++ build/demo.o build/calculator.o build/display.o build/keypad.o build/mock_hal.o -o calculator_demo.exe
if %errorlevel% neq 0 (
    echo Error linking program
    pause
    exit /b 1
)

echo.
echo === Build completed successfully! ===
echo.
echo To run the demo:
echo   calculator_demo.exe
echo.
echo To clean build files:
echo   build_demo.bat clean
echo.

REM Check if user wants to run the demo
set /p choice="Do you want to run the demo now? (y/n): "
if /i "%choice%"=="y" (
    echo.
    echo Running demo...
    calculator_demo.exe
)

pause
