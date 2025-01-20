#!/bin/bash

echo "Creating build directory..."
mkdir -p build
cd build

echo "Running CMake..."
cmake ..
 
echo "Building the project..."
make
