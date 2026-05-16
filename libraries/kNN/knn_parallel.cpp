//
// Created by Regino Kamberaj on 18/04/26.
//

#include "knn_parallel.h"

std::vector<std::vector<Neighbor>> knn_parallel(const Dataset &dataset, const std::vector<const float *> &queries,
    int k, DistanceMetric metric) {
    int num_queries = queries.size();
    int num_vectors = dataset.get_num_vectors();
    int dimension = dataset.getDim();

     std::vector<std::vector<Neighbor>> all_results(num_queries);

    #pragma omp parallel for
    for (int i = 0; i < num_queries; i++) {
        std::vector<Neighbor> neighbors(num_vectors);

        // calcolo le distanze
        for (int j = 0; j < num_vectors; j++) {
            float distance = getDistance(queries[i], dataset.getVector(j), dimension, metric);
            neighbors[j] = {j, distance};
        }

        // Seleziono i k minimi
        std::partial_sort(neighbors.begin(), neighbors.begin() + k, neighbors.end());
        neighbors.resize(k);
        all_results[i] = std::move(neighbors); // evita copie
    }

    return all_results;
}
