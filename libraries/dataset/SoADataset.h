//
// Created by Regino Kamberaj on 23/05/26.
//

#ifndef ANN_RETRIEVIAL_SOADATASET_H
#define ANN_RETRIEVIAL_SOADATASET_H
#include <vector>


class SoADataset {
private:
    std::vector<std::vector<float>> dimensions; // dimensions[dim][i] con dim dimensione dell'i-esimo vettore
    int n_vectors;
    int dimension;

    public:
    // Si converte un dataset formato AoS (da fvecs) a SoA
    SoADataset(const float* data, int num, int dim);

    // Accesso diretto alla dimensione dim del vettore
    float get(int i, int dim) const;

    // Accesso a tutta la dimensione dim (contingua in memoria)
    const float* get_dim_ptr(int dim) const;

    // Vecchio accesso al vettore
    std::vector<float> get_vector(int i) const;

    int get_num_vectors() const;
    int get_dimension() const;

};


#endif //ANN_RETRIEVIAL_SOADATASET_H