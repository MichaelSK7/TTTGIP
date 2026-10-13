#!/bin/bash

if ! cmake -S . -B build -G Ninja > /dev/null; then
    echo "CMake configuration failed."
    exit 1
fi

if ! cmake --build build > /dev/null; then
    echo "Build failed."
    exit 1
fi

for exe in bin/*; do
    "$exe"
    break
done