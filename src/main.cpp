#include <iostream>

#include "Dataset.h"
#include "fvecs_reader.h"
#include "kNN.h"

void test_sequential_case(int num_queries, DistanceMetric metric = Euclidean, bool skip_print = true);


int main() {
    auto num_queries = 1000;
    test_sequential_case(num_queries);
    test_sequential_case(num_queries, Manhattan);
    test_sequential_case(num_queries, Cosine);
}


void test_sequential_case(int num_queries, DistanceMetric metric, bool skip_print) {
    std::cout << "\n*** Testing metric: " << metricToString(metric) << " ***\n" << std::endl;
    int k = 10;
    auto filename = "../data/siftsmall/siftsmall_base.fvecs";
    int dim, num_vectors;
    auto vectors = fvecs_read(filename, &dim, &num_vectors);

    if (!vectors) {
        std::cerr << "Error reading file " << filename << std::endl;
        return;
    }

    Dataset dataset(vectors, num_vectors, dim);

    // Genero indici casuali per le query
    std::vector<int> query_indices;
    for (int i = 0; i < num_queries; i++) {
        query_indices.push_back(i % num_vectors);
    }

    auto start_total_time = std::chrono::high_resolution_clock::now();
    for (auto idx : query_indices) {
        auto query = dataset.getVector(idx);
        auto start = std::chrono::high_resolution_clock::now();
        auto query_result = knnQuery(dataset, query, k, DistanceMetric::Euclidean);
        auto end = std::chrono::high_resolution_clock::now();

        auto partial_time = std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() / 1000.0;

        if (!skip_print)
            std::cout << idx << " " << partial_time << " milliseconds" << std::endl;
    }

    auto end_total_time = std::chrono::high_resolution_clock::now();
    auto total_time = std::chrono::duration_cast<std::chrono::microseconds>
    (end_total_time - start_total_time).count() / 1000.0;

    std::cout << "Total time: " << total_time << " milliseconds" << std::endl;
    std::cout << "Mean time: " << total_time / query_indices.size() << " milliseconds" << std::endl;

    delete[] vectors;
}