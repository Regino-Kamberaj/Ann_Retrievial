//
// Created by Regino Kamberaj on 23/05/26.
//

#include "SoADataset.h"

SoADataset::SoADataset(const float *data, int num, int dim): n_vectors(num), dimension(dim) {

    dimensions.resize(dim);
    for (int i = 0; i < dim; i++) {
        dimensions[i].resize(num);
    }

    //riorganizzo correttamente i dati
    for (int i = 0; i < num; i++) {
        for (int dim_idx = 0; dim_idx < dim; dim_idx++) {
            dimensions[dim_idx][i] = data[i * dim + dim_idx];
        }
    }

}

float SoADataset::get(int i, int dim) const {
    return dimensions[dim][i];
}

const float * SoADataset::get_dim_ptr(int dim) const {
    return dimensions[dim].data(); // ritorna il ptr all'array sottostante
}

std::vector<float> SoADataset::get_vector(int i) const {
    std::vector<float> temp(dimension);

    for (int dim_idx = 0; dim_idx < dimension; dim_idx++) {
        temp[dim_idx] = dimensions[dim_idx][i];
    }

    return temp;
}

int SoADataset::get_num_vectors() const {
    return n_vectors;
}

int SoADataset::get_dimension() const {
    return dimension;
}
