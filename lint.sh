#!/bin/bash

# source directory
SRC_DIR="src"

clang-format $(find $SRC_DIR -type f -name "*.cpp" -o -name "*.h") -i --verbose
echo "Formatting completed."