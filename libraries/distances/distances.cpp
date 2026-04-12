//
// Created by Regino Kamberaj on 19/02/26.
//

#include <complex>
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


float manhattanDistance(const float* a, const float* b, int dim) {
    auto sum = 0.0f;
    for (int i = 0; i < dim; i++) {
        sum += std::abs(a[i] - b[i]);
    }
    return sum;
}

float dotProduct(const float* a, const float* b, int dim) {
    auto sum = 0.0f;
    for (int i = 0; i < dim; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

float norm(const float * p, int dim) {
    return std::sqrt(dotProduct(p, p, dim));
}

float cosineDistance(const float* a, const float* b, int dim) {
    float dot = dotProduct(a, b, dim);
    float norm_a = norm(a,dim);
    float norm_b = norm(b,dim);

    if (norm_a == 0.0f || norm_b == 0.0f) {
        return 1.0f; //distanza max
    }

    float similarity = dot / (norm_a * norm_a);

    // tengo la similarità fra -1 e 1
    if (similarity < -1.0f) {
        return -1.0f;
    }
    if (similarity > 1.0f) {
        return 1.0f;
    }

    return 1.0f - similarity;
}
