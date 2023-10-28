#!/bin/bash

# CSV Header
echo "version,filename,threads,time taken" > results.csv

# List of files
files=("images/blackbuck.bmp" "images/map.bmp" "images/snail.bmp")

# Compiler options for OpenMP support
omp_compiler_options="-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp"

# Compile the sequential program with OpenMP support
/usr/bin/clang -o rgb_to_gray $omp_compiler_options rgb_to_gray.c

# Loop through each file for the sequential version
for file in "${files[@]}"; do
    # Run the program
    ./rgb_to_gray "$file"
    # Read the time taken from the file
    time_taken=$(cat time.txt)
    # Output to CSV
    echo "Sequential,$file,1,$time_taken" >> results.csv
done

# Compile the parallel program with OpenMP support
/usr/bin/clang -o rgb_to_gray_parallel $omp_compiler_options rgb_to_gray_parallel.c

# Loop through each file for the parallel version
for file in "${files[@]}"; do
    # Loop through thread counts 1 to 8
    for threads in {1..8}; do
        # Run the program
        ./rgb_to_gray_parallel "$file" "$threads"
        # Read the time taken from the file
        time_taken=$(cat time.txt)
        # Output to CSV
        echo "Parallel,$file,$threads,$time_taken" >> results.csv
    done
done
