#!/bin/bash

# Check if at least program and image file names are provided
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <program.c> <image.bmp> [num-threads]"
    exit 1
fi

# Compile the OpenMP program
/usr/bin/clang -o omp_run -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp "$1"

# If the number of threads is provided, run the program with that argument
if [ "$#" -eq 3 ]; then
    ./omp_run "$2" "$3"
else
    ./omp_run "$2"
fi
