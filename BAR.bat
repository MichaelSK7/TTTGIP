@echo off

cmake -S . -B build -G Ninja >nul
if errorlevel 1 (
    echo CMake configuration failed.
    exit /b 1
)

cmake --build build >build_output.txt 2>&1
if errorlevel 1 (
    type build_output.txt
    del build_output.txt
    exit /b 1
)

del build_output.txt 2>nul

for /r bin %%F in (*.exe) do (
    "%%F"
    goto :done
)

:done