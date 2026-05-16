//
// Created by Regino Kamberaj on 18/04/26.
//

#ifndef ANN_RETRIEVIAL_KNN_PARALLEL_H
#define ANN_RETRIEVIAL_KNN_PARALLEL_H
#include <vector>

#include "kNN.h"


std::vector<std::vector<Neighbor>> knn_parallel(
    const Dataset &dataset,
    const std::vector<const float*>& queries,
    int k,
    DistanceMetric metric = Euclidean);

#endif //ANN_RETRIEVIAL_KNN_PARALLEL_H
