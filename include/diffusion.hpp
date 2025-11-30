#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;
#define PADDING_VALUE 30.0
void run_sequential(Matrix& grid, int steps);
void run_openmp_static(Matrix& grid, int steps);
void run_openmp_dynamic(Matrix& grid, int steps);

