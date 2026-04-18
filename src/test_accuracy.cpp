//
// Created by Regino Kamberaj on 12/04/26.
//

#include <iomanip>
#include <iostream>

#include "Dataset.h"
#include "fvecs_reader.h"
#include "kNN.h"

void test_accuracy(DistanceMetric metric);

int main() {
   test_accuracy(Euclidean);
   test_accuracy(Manhattan);
   test_accuracy(Cosine);
}

void test_accuracy(DistanceMetric metric) {
     std::cout << "\n=== Validation test with Ground Truth for metric: " << metricToString(metric) << " ===" << std::endl;

    // Carico il db
    auto base_file_name = "../data/siftsmall/siftsmall_base.fvecs";
    int dim, num_vectors;
    auto vectors = fvecs_read(base_file_name, &dim, &num_vectors);

    if (!vectors) {
        std::cerr << "Error reading file " << base_file_name << std::endl;
        return;
    }
    Dataset dataset(vectors, num_vectors, dim);

    // Carico le query
    auto query_file_name = "../data/siftsmall/siftsmall_query.fvecs";
    int query_dim, num_queries;
    auto query_vectors = fvecs_read(query_file_name, &query_dim, &num_queries);
    if (!query_vectors) {
        std::cerr << "Error reading file " << query_file_name << std::endl;
        delete[] vectors;
        return;
    }

    std::cout << "Query file: " << num_queries << " queries, "
    << query_dim << " dimensions" << std::endl;

    // Carico il ground truth
    auto gt_file_name = "../data/siftsmall/siftsmall_groundtruth.ivecs";
    int gt_dim, num_gt;
    auto gt_vectors = ivecs_read(gt_file_name, &gt_dim, &num_gt);

    if (!gt_vectors) {
        std::cerr << "Error reading file " << gt_file_name << std::endl;
        delete[] query_vectors;
        delete[] vectors;
        return;
    }

    std::cout << "Ground Truth file: " << num_gt << " query, "
    << gt_dim << " neighbours" << std::endl;

    auto k_values = {1,10,100};
    for (int k:k_values) {
        auto total_correct = 0;
        auto total_possible = num_queries*k;

        for (int i = 0; i < num_queries; i++) {
            auto query = &query_vectors[i * query_dim];

            auto result = knnQuery(dataset, query, k, metric);

            for (int j = 0; j < k; j++) {
                auto our_idx = result[j].index;
                auto gt_idx = gt_vectors[i * gt_dim + j];
                total_correct += our_idx == gt_idx;
            }
        }

        auto accuracy = 100.0f * total_correct/total_possible;
        std::cout << "k = " << k << ", Accuracy: " << std::fixed << std::setprecision(2)<<
            accuracy  << "% (" << total_correct << "/" << total_possible << ")" << std::endl;
    }
}