# 2D Heat Diffusion Simulation

## Description

This project implements a **2D heat diffusion simulation** that models how heat spreads over a surface grid through iterative convolution. The system supports both **sequential** and **OpenMP-parallel** execution modes, enabling users to compare performance and behavior between single-threaded and parallel computation. The input is a heat matrix stored as a CSV file, and the program outputs the final state of the heat distribution after a specified number of iterations.

The simulation is designed for educational and research purposes, focusing on demonstrating numerical computation, data parallelism, and performance optimization. Users can visualize the simulation results using the provided Python script, which highlights temperature variations in the central region of the grid.

---

## 1. Features

* Load initial heat distribution from `heat_matrix.csv`
* Simulate diffusion for a configurable number of iterations
* Execution modes:

  * **Mode 0**: Sequential
  * **Mode 1**: Parallel (OpenMP)
* Export results to a CSV file (rounded to two decimal places)
* Visualize input/output and difference using Python

---

## 2. Directory Structure

```
.
├── include/                    # Header files
├── src/                        # C++ source files
├── build/                      # Compiled objects and binary
├── Makefile                    # Build automation
├── compare_heatmap_center.py   # Visualization script
└── README.md                   # Documentation
```

---

## 3. Build Instructions

Make sure **g++** with **OpenMP** is installed, then run:

```bash
make
```

The compiled binary will be stored in `build/`.

---

## 4. Run Simulation

```bash
./build/heat_diffusion <mode> <iterations> <output_file>
```

Example:

```bash
./build/heat_diffusion 1 10 heat_output.csv
```

| Argument        | Description                         |
| --------------- | ----------------------------------- |
| `<mode>`        | 0 = sequential, 1 = OpenMP parallel |
| `<iterations>`  | Number of simulation iterations     |
| `<output_file>` | Output CSV file name                |

---

## 5. Visualization

Compare input and output heatmaps using the Python script:

```bash
python compare_heatmap_center.py heat_matrix.csv heat_output.csv
```

The script:

* Focuses on the 400×400 central area
* Displays input, output, and difference heatmaps side-by-side
* Uses a diverging color scheme to emphasize thermal changes
* Saves the figure as a `.png` file

---

## 6. Clean Build Files

```bash
make clean
```

Deletes all generated build files.

---

## 7. Author

**Hà Chí Trung**
Ho Chi Minh City University of Technology
Simulation and Parallel Programming Project
