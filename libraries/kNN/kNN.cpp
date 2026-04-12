//
// Created by Regino Kamberaj on 19/02/26.
//


#include "kNN.h"
#include "distances.h"

#include <vector>

std::vector<Neighbor> knnQuery(const Dataset& db, const float* query, int k, DistanceMetric metric = Euclidean) {

    auto num = db.get_num_vectors();
    auto dim = db.getDim();
    std::vector<Neighbor> neighbors(num);

    for (int i = 0; i < num; ++i) {
        auto dist = getDistance(query, db.getVector(i), dim, metric);
        neighbors[i] = {i, dist};
    }

    // K come numero dei vicini che voglio trovare => i primi K ordinati secondo la distanza
    std::partial_sort(neighbors.begin(),
        neighbors.begin()+k, neighbors.end()); // non ordino tutto il vettore ma scelgo solo i primi k elementi

    neighbors.resize(k);
    return neighbors;
}

float getDistance(const float* a, const float* b, int dim, DistanceMetric metric) {
    switch (metric) {
        case Euclidean:
            return euclideanSquared(a, b, dim);
        case Manhattan:
            return manhattanDistance(a, b, dim);
        case Cosine:
            return cosineDistance(a, b, dim);
        default:
            return 0.0f;
    }
}


char* metricToString(DistanceMetric metric) {
    switch (metric) {
        case Euclidean:
            return "Euclidean (L2)";
        case Manhattan:
            return "Manhattan (L1)";
        case Cosine:
            return "Cosine";
        default:
            return "Unknown";
    }
}