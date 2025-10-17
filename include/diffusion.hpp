#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;

void run_sequential(Matrix& grid, int steps);
void run_openmp(Matrix& grid, int steps);
