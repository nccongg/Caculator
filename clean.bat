@echo off
REM Clean script for STM32 Calculator Project

echo === Cleaning STM32 Calculator Project ===

REM Remove build directory
if exist build (
    echo Removing build directory...
    rmdir /s /q build
    echo Build directory removed.
) else (
    echo Build directory not found.
)

REM Remove executable files
if exist calculator_demo.exe (
    echo Removing calculator_demo.exe...
    del calculator_demo.exe
    echo calculator_demo.exe removed.
) else (
    echo calculator_demo.exe not found.
)

REM Remove object files
if exist *.o (
    echo Removing object files...
    del *.o
    echo Object files removed.
) else (
    echo No object files found.
)

REM Remove dependency files
if exist *.d (
    echo Removing dependency files...
    del *.d
    echo Dependency files removed.
) else (
    echo No dependency files found.
)

echo.
echo === Clean completed! ===
pause
