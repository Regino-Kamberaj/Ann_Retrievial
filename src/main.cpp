#include <iostream>

#include "Dataset.h"
#include "fvecs_reader.h"
#include "kNN.h"

void test_sequential_case(int k);

int main() {
    test_sequential_case(10);
    test_sequential_case(100);
    test_sequential_case(1000);
}

void test_sequential_case(int k) {
    std::cout << "\n*** Testing sequential case for k=" << k << " ***" << std::endl;

    auto filename = "../data/siftsmall/siftsmall_base.fvecs";
    int dim, num;
    auto vectors = fvecs_read(filename, &dim, &num);

    if (!vectors) {
        std::cerr << "Error reading file " << filename << std::endl;
        return;
    }

    Dataset dataset(vectors, num, dim);

    auto query_indices = {0,100,200,500,1000};

    auto start_total_time = std::chrono::high_resolution_clock::now();
    for (auto idx : query_indices) {
        auto query = dataset.getVector(idx);
        auto start = std::chrono::high_resolution_clock::now();
        auto query_result = knnQuery(dataset, query, k);
        auto end = std::chrono::high_resolution_clock::now();

        auto partial_time = std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() / 1000.0;

        std::cout << idx << " " << partial_time << " microseconds" << std::endl;
    }

    auto end_total_time = std::chrono::high_resolution_clock::now();
    auto total_time = std::chrono::duration_cast<std::chrono::microseconds>
    (end_total_time - start_total_time).count() / 1000.0;

    std::cout << "Total time: " << total_time << " microseconds" << std::endl;
    std::cout << "Mean time: " << total_time / query_indices.size() << " microseconds" << std::endl;

    delete[] vectors;
}