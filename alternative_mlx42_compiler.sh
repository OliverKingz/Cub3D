#!/bin/bash
# Use this script only if the original Makefile fails to compile MLX42 correctly (e.g., on WSL or with specific compiler issues)

# Rebuild MLX42 with WSL-specific flags
cd lib/MLX42
rm -rf build && mkdir build && cd build
cmake .. -DCMAKE_C_COMPILER_WORKS=1 -DCMAKE_CXX_COMPILER_WORKS=1
make
cd ../../..

# Next build main project using: make or make bonus