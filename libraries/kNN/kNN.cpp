//
// Created by Regino Kamberaj on 19/02/26.
//


#include "kNN.h"
#include "distances.h"

#include <vector>

std::vector<Neighbor> knnQuery(const Dataset& db, const float* query, int k) {

    auto num = db.getN();
    std::vector<Neighbor> neighbors(num);

    for (int i = 0; i < num; ++i) {
        auto dist = euclideanSquared(query, db.getVector(i), db.getN());
        neighbors[i] = {i, dist};
    }

    std::partial_sort(neighbors.begin(),
        neighbors.begin()+k, neighbors.end());

    neighbors.resize(k);
    return neighbors;
}
