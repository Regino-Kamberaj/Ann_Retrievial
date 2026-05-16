//
// Created by Regino Kamberaj on 18/04/26.
//


#include <iostream>
#include <ostream>
#include <omp.h>
#include "fvecs_reader.h"
#include "kNN.h"
#include "knn_parallel.h"

void test_parallel(int num_queries, DistanceMetric metric);

int main() {
    auto num_queries = 10000;
    auto metrics = {Euclidean};
    for (auto metric : metrics) {
        test_parallel(num_queries, metric);
    }
}

void test_parallel(int num_queries, DistanceMetric metric) {
    int k = 10;
    std::cout << "\n=== OpenMP Parallel test ===" << std::endl;
    std::cout << "*** Testing metric: " << metricToString(metric) << " for k=" << k << " ***" << std::endl;

    // Carico il dataset
    auto filename = "../data/siftsmall/siftsmall_base.fvecs";
    int dim, num_vectors;
    auto vectors = fvecs_read(filename, &dim, &num_vectors);

    if (!vectors) {
        std::cerr << "Error reading file " << filename << std::endl;
        return;
    }

    Dataset dataset(vectors, num_vectors, dim);

    // Preparo le query (prendo le prime 100) dal dataset
    std::vector<const float *> queries;
    for (int i = 0; i < num_queries; i++) {
        queries.push_back(dataset.getVector(i));
    }

    // Test con diversi thread
    auto thread_counts = {1,2,4,6,8,10,100};

    std::cout << "Thread\tTime (ms)\tSpeedup\n";
    std::cout << "------\t---------\t-------\n";

    auto base_time = 0.0;

    for (int num_threads: thread_counts) {
        omp_set_num_threads(num_threads);

        auto start = std::chrono::high_resolution_clock::now();
        auto result = knn_parallel(dataset, queries, k, metric);
        auto end = std::chrono::high_resolution_clock::now();

        double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (num_threads == 1)
            base_time = elapsed;
        auto speedup = base_time / elapsed;
        std::cout << num_threads << "\t\t" << elapsed << "\t\t" << speedup << std::endl;
    }

    delete[] vectors;
}