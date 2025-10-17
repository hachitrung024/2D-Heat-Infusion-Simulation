#include "diffusion.hpp"

static const double K[3][3] = {
    {0.05, 0.1, 0.05},
    {0.1,  0.4, 0.1},
    {0.05, 0.1, 0.05}
};

void run_sequential(Matrix& grid, int steps) {
    int rows = grid.size();
    int cols = grid[0].size();
    Matrix new_grid = grid;

    for (int s = 0; s < steps; ++s) {
        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                double val = 0.0;
                for (int ki = -1; ki <= 1; ++ki)
                    for (int kj = -1; kj <= 1; ++kj)
                        val += grid[i + ki][j + kj] * K[ki + 1][kj + 1];
                new_grid[i][j] = val;
            }
        }
        grid.swap(new_grid);
    }
}
