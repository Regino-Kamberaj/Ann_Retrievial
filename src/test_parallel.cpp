//
// Created by Regino Kamberaj on 18/04/26.
//


#include <iomanip>
#include <iostream>
#include <numeric>
#include <ostream>
#include <omp.h>
#include "fvecs_reader.h"
#include "kNN.h"
#include "knn_parallel.h"

void test_parallel(int num_queries, DistanceMetric metric, int num_runs = 5);

int main() {
    auto num_queries = 10000;
    auto metrics = {Euclidean};
    for (auto metric : metrics) {
        test_parallel(num_queries, metric);
    }
}

void test_parallel(int num_queries, DistanceMetric metric, int num_runs) {
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
    auto thread_counts = {1,2,4,6,8,10,20,100};

    std::cout << "Thread\tMean (ms)\tMin (time)\tMax (time)\tStd Dev \tSpeedup \tEfficiency\n";
    std::cout << "------\t---------\t----------\t----------\t--------\t-------- \t----------\n";


    for (int num_threads: thread_counts) {

        std::vector<double> times;

        for (int run = 0; run < num_runs; run++) {
            omp_set_num_threads(num_threads);

            auto start = std::chrono::high_resolution_clock::now();
            auto result = knn_parallel(dataset, queries, k, metric);
            auto end = std::chrono::high_resolution_clock::now();

            double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            times.push_back(elapsed);
        }

        // Aggiungo il calcolo delle statistiche
        auto mean = std::accumulate(times.begin(), times.end(), 0.0) / num_runs;
        auto variance = 0.0;
        for (auto time : times) {
            variance += std::pow(time - mean, 2);
        }

        auto std_dev = std::sqrt(variance / num_runs);
        auto min = *std::min_element(times.begin(), times.end());
        auto max = *std::max_element(times.begin(), times.end());

        static auto base_mean = 0.0;
        if (num_threads == 1)
            base_mean = mean;
        auto speedup = base_mean / mean;
        auto ceiledSpeedup = std::floor(speedup * 10.0) / 10.0;
        auto efficiency = ceiledSpeedup / num_threads * 100;
        std::cout << num_threads << "\t\t" << mean << "\t\t"
                  << min << "\t\t" << max << "\t\t" << std_dev << "\t\t"  << speedup << "\t\t" << efficiency <<"%" << std::endl;
    }

    delete[] vectors;
}