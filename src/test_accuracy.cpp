//
// Created by Regino Kamberaj on 12/04/26.
//

#include <iomanip>
#include <iostream>
#include <omp.h>

#include "Dataset.h"
#include "fvecs_reader.h"
#include "kNN.h"
#include "knn_parallel.h"
#include "kNN_soa.h"
#include "SoADataset.h"

void test_accuracy(DistanceMetric metric);
void test_accuracy_parallel(DistanceMetric metric, int num_threads);

int main() {
   test_accuracy(Euclidean);
    for (int threads : {2,4,8}) {
        test_accuracy_parallel(Euclidean, threads);
    }
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

void test_accuracy_parallel(DistanceMetric metric, int num_threads) {
     std::cout << "\n=== Parallel validation test with Ground Truth for metric: " << metricToString(metric) << " ===" << std::endl;

    // Carico il db
    auto base_file_name = "../data/siftsmall/siftsmall_base.fvecs";
    int dim, num_vectors;
    auto vectors = fvecs_read(base_file_name, &dim, &num_vectors);

    if (!vectors) {
        std::cerr << "Error reading file " << base_file_name << std::endl;
        return;
    }
    Dataset dataset(vectors, num_vectors, dim);
    SoADataset soa_dataset(vectors, num_vectors, dim);

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

    // Preparo tutte le query come vettori di puntatori
    std::vector<const float*> all_queries;
    for (int i = 0; i < num_queries; i++) {
        all_queries.push_back(&query_vectors[i * query_dim]);
    }

    int k = 10;
    omp_set_num_threads(num_threads);

    //Guardo i casi sia nel caso AoS che SoA
    auto aos_results = knn_parallel(dataset, all_queries, k, metric);
    int total_correct_aos = 0;
    int total_correct_soa = 0;
    int total_possible = num_queries*k;
    for (int i = 0; i < num_queries; i++) {
        for (int j = 0; j < k; j++) {
            int gt_index = gt_vectors[i * gt_dim + j];
            int our_index_aos = aos_results[i][j].index;
            int our_index_soa = aos_results[i][j].index;
            total_correct_aos += our_index_aos == gt_index;
            total_correct_soa += our_index_soa == gt_index;
        }
    }
    auto accuracy_aos = 100.0f * total_correct_aos/total_possible;
    auto accuracy_soa = 100.0f * total_correct_soa/total_possible;

    std::cout << "Num_threads = " << num_threads << ", Accuracy AoS: " << std::fixed << std::setprecision(2)<<
        accuracy_aos  << "% (" << total_correct_aos << "/" << total_possible << ")" << std::endl;
    std::cout << "Num_threads = " << num_threads << ", Accuracy SoA: " << std::fixed << std::setprecision(2)<<
           accuracy_soa  << "% (" << total_correct_soa << "/" << total_possible << ")" << std::endl;

    delete[] gt_vectors;
    delete[] vectors;
    delete[] query_vectors;
}