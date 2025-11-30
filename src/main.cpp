#include <iostream>
#include <chrono>
#include <omp.h>
#include <string>
#include "diffusion.hpp"
#include "utils.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " [mode] [steps] [output.csv]\n";
        cerr << "mode: 0=sequential, 1=openmp_static, 2=openmp_dynamic\n";
        return 1;
    }

    int mode = stoi(argv[1]);
    int steps = stoi(argv[2]);
    string out_filename = argv[3];

    cout << "Loading heat_matrix.csv ...\n";
    Matrix grid = load_csv("../heat_matrix.csv");
    if (grid.empty()) {
        cerr << "Failed to load input matrix.\n";
        return 1;
    }

    cout << "Loaded " << grid.size() << "x" << grid[0].size() << " matrix.\n";

    auto start = chrono::high_resolution_clock::now();

    if (mode == 0) {
        cout << "Running sequential version...\n";
        run_sequential(grid, steps);
    } else if (mode == 1) {
        #ifdef _OPENMP
        cout << "Using " << omp_get_max_threads() << " threads.\n";
        #endif
        cout << "Running OpenMP Static Schedule version...\n";
        run_openmp_static(grid, steps);
        
    } else if (mode == 2) {
        #ifdef _OPENMP
        cout << "Using " << omp_get_max_threads() << " threads.\n";
        #endif
        cout << "Running OpenMP Dynamic Schedule version...\n";
        run_openmp_dynamic(grid, steps);
    } else {
        cerr << "Invalid mode\n";
        return 1;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Simulation completed in " << elapsed.count() << " seconds.\n";

    save_csv(out_filename, grid);
    return 0;
}