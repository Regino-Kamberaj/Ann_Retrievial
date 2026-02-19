//
// Created by Regino Kamberaj on 18/02/26.
//

#include "fvecs_reader.h"

#include <cstdio>
#include <iostream>

inline float* fvecs_read(const char* filename, int* dim_out, int* n_out) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return nullptr;
    }

    // Leggo la dimensione del primo vettore
    int dim;
    fread(&dim, sizeof(int), 1, file);

    // Calcolo la dimensione totale del file
    fseek(file, 0, SEEK_END);
    auto file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    auto vector_size_bytes = sizeof(int) + dim * sizeof(float);
    auto n = file_size / vector_size_bytes;

    std::cout << "File: " << filename << std::endl;
    std::cout << "File dimension: " << file_size << " bytes" << std::endl;
    std::cout << "Vector dimension: " << dim << std::endl;
    std::cout << "Number of vectors: " << n << std::endl;
    std::cout << "Bytes for vector: " << vector_size_bytes << std::endl;

    // Alloco memoria per tutti i vettori
    auto data = new float[n * dim];

    // Leggo tutti i vettori
    for (int i = 0; i < n; i++) {
        int header;
        auto read_header = fread(&header, sizeof(int), 1, file);

        if (read_header != 1) {
            std::cerr << "ERROR: Could not read header from file " << filename << std::endl;
            delete[] data;
            fclose(file);
            return nullptr;
        }

        if (header != dim) {
            std::cerr << "ERROR: Header dimension different (" << header
            << ") expected " << dim << " on vector " << i << std::endl;
        }

        auto read_data = fread(&data[i*dim], sizeof(float), dim, file);
        if (read_data != size_t(dim)) {
            std::cerr << "ERROR: Could not read data from vector" << i << std::endl;
            delete[] data;
            fclose(file);
            return nullptr;
        }
    }

    fclose(file);

    *dim_out = dim;
    *n_out = int(n);
    return data;
}

std::vector<float> fvecs_read_vector(const char* filename, int* dim_out) {
    int n;
    auto data = fvecs_read(filename, dim_out, &n);

    if (!data) {
        return std::vector<float>();
    }

    std::vector<float> result(data, data + n * (*dim_out));
    delete[] data;
    return result;
}

inline int* ivecs_read(const char* filename, int* dim_out, int* n_out) {
    FILE* file = fopen(filename, "rb");

    if (!file) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return nullptr;
    }

    // Leggo la dimensione del primo vettore
    int dim;
    fread(&dim, sizeof(int), 1, file);

    // Calcolo la dimensione totale del file
    fseek(file, 0, SEEK_END);
    auto file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    auto vector_size_bytes = sizeof(int) + dim * sizeof(int);
    auto n = file_size / vector_size_bytes;

    std::cout << "File: " << filename << std::endl;
    std::cout << "Number of vectors:" << n << " Vector dimension : " << dim << std::endl;

    // Alloco memoria per tutti i vettori
    auto data = new int[n * dim];

    // Leggo tutti i vettori
    for (int i = 0; i < n; i++) {
        int header;
        fread(&header, sizeof(int), 1, file);
        fread(&data[i*dim], sizeof(int), dim, file);
    }

    fclose(file);

    *dim_out = dim;
    *n_out = int(n);
    return data;
}

