#!/bin/bash

# Rebuild MLX42 with WSL-specific flags
cd lib/MLX42
rm -rf build && mkdir build && cd build
cmake .. -DCMAKE_C_COMPILER_WORKS=1 -DCMAKE_CXX_COMPILER_WORKS=1
make
cd ../../..

# Build main project
make