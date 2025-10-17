#include <iostream>
#include <chrono>
#include "diffusion.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " [mode] [steps] [output.csv]\n";
        std::cerr << "mode: 0=sequential, 1=openmp\n";
        return 1;
    }

    int mode = std::stoi(argv[1]);
    int steps = std::stoi(argv[2]);
    std::string out_filename = argv[3];

    std::cout << "Loading heat_matrix.csv ...\n";
    Matrix grid = load_csv("heat_matrix.csv");
    if (grid.empty()) {
        std::cerr << "Failed to load input matrix.\n";
        return 1;
    }

    std::cout << "Loaded " << grid.size() << "x" << grid[0].size() << " matrix.\n";

    auto start = std::chrono::high_resolution_clock::now();

    if (mode == 0) {
        std::cout << "Running sequential version...\n";
        run_sequential(grid, steps);
    } else if (mode == 1) {
        std::cout << "Running OpenMP version...\n";
        run_openmp(grid, steps);
    } else {
        std::cerr << "Invalid mode\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Simulation completed in " << elapsed.count() << " seconds.\n";

    save_csv(out_filename, grid);
    return 0;
}
