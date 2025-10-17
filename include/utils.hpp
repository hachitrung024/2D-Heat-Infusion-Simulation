#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>  // thêm thư viện này để setprecision

using Matrix = std::vector<std::vector<double>>;

inline Matrix load_csv(const std::string& filename) {
    Matrix data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: cannot open file " << filename << "\n";
        return data;
    }

    while (std::getline(file, line)) {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            row.push_back(std::stod(value));
        }
        data.push_back(row);
    }
    return data;
}

inline void save_csv(const std::string& filename, const Matrix& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: cannot write to " << filename << "\n";
        return;
    }

    file << std::fixed << std::setprecision(2);  // luôn ghi 2 chữ số sau dấu phẩy

    for (const auto& row : data) {
        for (size_t j = 0; j < row.size(); ++j) {
            file << row[j];
            if (j + 1 < row.size())
                file << ',';
        }
        file << '\n';
    }

    file.close();
    std::cout << "Saved to " << filename << "\n";
}
