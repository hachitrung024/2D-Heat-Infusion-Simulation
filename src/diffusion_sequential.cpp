#include "diffusion.hpp"

static const double K[3][3] = {
    {0.05, 0.1, 0.05},
    {0.1,  0.4, 0.1},
    {0.05, 0.1, 0.05}
};

void run_sequential(Matrix& grid, int steps) {
    if (grid.empty() || grid[0].empty()) return;
    
    int rows = grid.size();
    int cols = grid[0].size();
    // Create a new matrix of the same size to store temporary results
    Matrix new_grid(rows, std::vector<double>(cols)); 

    // Main loop: Perform STEPS iterations
    for (int s = 0; s < steps; ++s) {
        
        // Loop through all cells including boundaries
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double new_val = 0.0;
                
                // Loop through the 3x3 kernel
                for (int ki = -1; ki <= 1; ++ki) {
                    for (int kj = -1; kj <= 1; ++kj) {
                        
                        int ni = i + ki;
                        int nj = j + kj;
                        double current_temp;

                        // Boundary check (padding logic)
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
        // Swap matrices: current step result becomes input for next step
        grid.swap(new_grid); 
    }
}
