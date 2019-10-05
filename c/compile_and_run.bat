@echo off

:: Set MinGW path
set PATH=%PATH%;C:\msys64\mingw64\bin;C:\msys64\mingw64\x86_64-w64-mingw32\bin
:: Compile C to Assembler
gcc main.c -o main.asm -Wall -O3 -S
:: Compile C to executable
gcc main.c -o main.exe -Wall -O3
:: Run output
main 2>nul

:: Wait for input to exit script
pause