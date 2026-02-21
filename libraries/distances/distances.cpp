//
// Created by Regino Kamberaj on 19/02/26.
//

#include <valarray>

float euclideanSquared(const float* a, const float* b, int dim) {
    auto sum = 0.0f;
    for (int i = 0; i < dim; i++) {
        auto diff = a[i] - b[i];
        sum += diff * diff;
    }

    return sum;
}

float euclideanDistance(const float* a, const float* b, int dim) {
    return std::sqrt(euclideanSquared(a, b, dim));
}