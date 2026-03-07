#include <iostream>

#include "Dataset.h"
#include "fvecs_reader.h"
#include "kNN.h"

void test_sequential_case(int k, bool skip_print = false);

int main() {
    test_sequential_case(10);
    test_sequential_case(20);
    test_sequential_case(50);
    test_sequential_case(100, true);
    test_sequential_case(200, true);
    test_sequential_case(1000, true);
    test_sequential_case(10000, true);
}

void test_sequential_case(int num_queries, bool skip_print) {
    auto k = 10;
    std::cout << "\n*** Testing sequential case for k=" << k
    << " and for " << num_queries << " queries ***" << std::endl;

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
        auto query_result = knnQuery(dataset, query, k);
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