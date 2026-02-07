# RGB to Grayscale -- OpenMP

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![OpenMP](https://img.shields.io/badge/OpenMP-Parallel-blue)

A BMP image RGB-to-grayscale converter in C with both sequential and OpenMP-parallelized versions. Includes a benchmarking script that compares performance across 1-8 threads on multiple test images, outputting results to CSV.

## How It Works

Each pixel is converted using the luminance formula:

```
gray = R * 0.30 + G * 0.59 + B * 0.11
```

The parallel version uses `#pragma omp parallel for` to distribute pixel processing across threads.

## Usage

**Compile** (macOS with Homebrew libomp):

```bash
clang -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o rgb_to_gray rgb_to_gray.c
clang -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o rgb_to_gray_parallel rgb_to_gray_parallel.c
```

**Run:**

```bash
# Sequential
./rgb_to_gray images/blackbuck.bmp

# Parallel (default 4 threads)
./rgb_to_gray_parallel images/blackbuck.bmp

# Parallel with custom thread count
./rgb_to_gray_parallel images/blackbuck.bmp 8
```

Output is saved as `<input>_grayscale.bmp`.

## Benchmarking

Run the full benchmark suite across all test images and thread counts (1-8):

```bash
./results.sh
```

Results are written to `results.csv`.
