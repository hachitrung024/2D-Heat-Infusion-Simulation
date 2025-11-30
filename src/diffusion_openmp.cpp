#include "diffusion.hpp"
#include <omp.h>

static const double K[3][3] = {
    {0.05, 0.1, 0.05},
    {0.1,  0.4, 0.1},
    {0.05, 0.1, 0.05}
};

void run_openmp_static(Matrix& grid, int steps) {
    if (grid.empty() || grid[0].empty()) return;
    
    int rows = grid.size();
    int cols = grid[0].size();
    Matrix new_grid(rows, std::vector<double>(cols)); 

    // Main loop: Perform STEPS iterations
    for (int s = 0; s < steps; ++s) {
        
        // OPENMP DIRECTIVE: Parallelize the outermost loop (i) with STATIC schedule
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double new_val = 0.0;
                
                // Loop through the 3x3 kernel
                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        
                        int ni = i + ki;
                        int nj = j + kj;
                        double current_temp;

                        // Inline boundary check logic (Padding 30.0)
                        if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) {
                            current_temp = PADDING_VALUE;
                        } else {
                            current_temp = grid[ni][nj];
                        }

                        new_val += current_temp * K[ki + 1][kj + 1];
                    }
                }
                new_grid[i][j] = new_val;
            }
        }
        // Swap matrices: grid = new_grid
        grid.swap(new_grid); 
    }
}

void run_openmp_dynamic(Matrix& grid, int steps) {
    if (grid.empty() || grid[0].empty()) return;
    
    int rows = grid.size();
    int cols = grid[0].size();
    Matrix new_grid(rows, std::vector<double>(cols)); 

    for (int s = 0; s < steps; ++s) {
        
        #pragma omp parallel for schedule(dynamic)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double new_val = 0.0;
                
                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        
                        int ni = i + ki;
                        int nj = j + kj;
                        double current_temp;

                        if (ni < 0 || ni >= rows || nj < 0 || nj >= cols) {
                            current_temp = PADDING_VALUE;
                        } else {
                            current_temp = grid[ni][nj];
                        }

                        new_val += current_temp * K[ki + 1][kj + 1];
                    }
                }
                new_grid[i][j] = new_val;
            }
        }
        grid.swap(new_grid); 
    }
}