//
// Created by Regino Kamberaj on 19/02/26.
//

#include <complex>
#include <valarray>
#include <distances.h>

#include "../dataset/SoADataset.h"

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

float euclideanSquaredSoA(const float *query, const SoADataset &dataset, int idx) {
    auto sum = 0.0f;
    auto dim = dataset.get_dimension();

    for (int i = 0; i < dim; i++) {
        auto diff = query[i] - dataset.get(idx, i);
        sum += diff * diff;
    }

    return sum;
}

void euclideanSquaredBatched(const float *query, const SoADataset &dataset, float *distances) {
    auto num = dataset.get_num_vectors();
    auto dim = dataset.get_dimension();

    for (int i = 0; i < num; i++) {
        distances[i] = 0.0f;
    }

    // per ogni dimensione, processo tutti i vettori in modo contiguo
    for (int i = 0; i < dim; i++) {
        auto dim_ptr = dataset.get_dim_ptr(i);
        auto query_dim = query[i];

        for (int j = 0; j < num; j++) {
            auto diff = query_dim - dim_ptr[j];
            distances[j] += diff * diff;
        }
    }
}

