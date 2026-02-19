//
// Created by Regino Kamberaj on 18/02/26.
//

#include <iomanip>
#include <iostream>
#include "fvecs_reader.h"

int main() {
    auto filename = "/Users/regino_kamberaj/ClionProjects/Ann_Retrievial/data/siftsmall/siftsmall_base.fvecs";

    int dim, n;
    auto vectors = fvecs_read(filename, &dim, &n);

    if (!vectors) {
        std::cerr << "Error reading file " << filename << std::endl;
        return 1;
    }

    std::cout << " \n*** First 5 vectors, first 10 dimensions ***\n";
    for (int i = 0; i < std::min(5, n); ++i) {
        std::cout << "Vector " << i << ": " << std::endl;
        for (int j = 0; j < std::min(10, dim); ++j) {
            std::cout << std::fixed << std::setprecision(2)
            << vectors[i * dim + j] << " ";
        }
        std::cout << (dim > 10 ? "..." : "") << std::endl;
    }

    // Aggiungo il calcolo di alcune statistiche base
    float min = vectors[0], max = vectors[0], sum = 0;
    for (int i = 0; i < n*dim; ++i) {
        if (vectors[i] < min) min = vectors[i];
        if (vectors[i] > max) max = vectors[i];
        sum += vectors[i];
    }

    std::cout << "\n*** Stats ***\n";
    std::cout << "Min: " << min << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Mean: " << sum / (n*dim) << std::endl;

    delete [] vectors;
    return 0;
}
