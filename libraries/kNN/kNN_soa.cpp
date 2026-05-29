//
// Created by Regino Kamberaj on 23/05/26.
//

#include "kNN_soa.h"

#include "distances.h"

std::vector<std::vector<Neighbor_SoA>> knn_query_SoA(const SoADataset &dataset, const std::vector<const float*> &queries,
                                                     int k) {
    auto num_queries = static_cast<int>(queries.size());
    auto num_vectors = dataset.get_num_vectors();

    std::vector<std::vector<Neighbor_SoA>> result(num_queries);

#pragma omp parallel for
    for (int i = 0; i < num_queries; i++) {
        std::vector<float> distances(num_vectors);

        // calcolo le distanze
        euclideanSquaredBatched(queries[i], dataset, distances.data());

        // costruisco i vicini
        std::vector<Neighbor_SoA> neighbors(num_vectors);
        for (int j = 0; j < num_vectors; j++) {
            neighbors[j] = {j, distances[j]};
        }

        // ne seleziono i k minimi
        std::partial_sort(neighbors.begin(), neighbors.begin() + k, neighbors.end());
        neighbors.resize(k);
        result[i] = std::move(neighbors);
    }

    return result;
}
