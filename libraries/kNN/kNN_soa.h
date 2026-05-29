//
// Created by Regino Kamberaj on 23/05/26.
//

#ifndef ANN_RETRIEVIAL_SOAKNN_H
#define ANN_RETRIEVIAL_SOAKNN_H
#include <vector>

#include "SoADataset.h"


struct Neighbor_SoA {
    int index;
    float distance;

    bool operator<(const Neighbor_SoA &other) const {
        return distance < other.distance;
    }
};

std::vector<std::vector<Neighbor_SoA>> knn_query_SoA(
    const SoADataset& dataset,
    const std::vector<const float*>& queries,
    int k
);

#endif //ANN_RETRIEVIAL_SOAKNN_H