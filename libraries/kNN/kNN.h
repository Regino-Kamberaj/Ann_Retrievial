//
// Created by Regino Kamberaj on 19/02/26.
//

#ifndef ANN_RETRIEVIAL_KNN_H
#define ANN_RETRIEVIAL_KNN_H
#include <vector>

#include "../dataset/Dataset.h"


struct Neighbor {
    int index;
    float distance;

    bool operator<(const Neighbor &other) const {
        return distance < other.distance;
    }
};
enum DistanceMetric {
    Euclidean,
    Manhattan,
    Cosine,
};

char* metricToString(DistanceMetric metric);

std::vector<Neighbor> knnQuery(const Dataset& db, const float* query, int k, DistanceMetric metric);
float getDistance(const float* a, const float* b, int dim, DistanceMetric metric);

#endif //ANN_RETRIEVIAL_KNN_H