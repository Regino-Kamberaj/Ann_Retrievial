//
// Created by Regino Kamberaj on 19/02/26.
//

#include "Dataset.h"

Dataset::Dataset(float *data, int num, int dim)
    : data(data), num_vectors(num), dim(dim) {}

const float *Dataset::getVector(int i) const {
    return &data[i*dim];
}

int Dataset::get_num_vectors() const {
    return num_vectors;
}

int Dataset::getDim() const {
    return dim;
}

