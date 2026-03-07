//
// Created by Regino Kamberaj on 19/02/26.
//


#include "kNN.h"
#include "distances.h"

#include <vector>

std::vector<Neighbor> knnQuery(const Dataset& db, const float* query, int k) {

    auto num = db.get_num_vectors();
    std::vector<Neighbor> neighbors(num);

    for (int i = 0; i < num; ++i) {
        auto dist = euclideanSquared(query, db.getVector(i), db.getDim());
        neighbors[i] = {i, dist};
    }

    // K come numero dei vicini che voglio trovare => i primi K ordinati secondo la distanza
    std::partial_sort(neighbors.begin(),
        neighbors.begin()+k, neighbors.end()); // non ordino tutto il vettore ma scelgo solo i primi k elementi

    neighbors.resize(k);
    return neighbors;
}
