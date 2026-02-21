//
// Created by Regino Kamberaj on 19/02/26.
//

#ifndef ANN_RETRIEVIAL_DATASET_H
#define ANN_RETRIEVIAL_DATASET_H

/**
 * Classe per tenere da parte il dataset SIFT
 */
class Dataset {
private:
    float* data;
    int n_vectors;
    int dim;

public:
    Dataset(float* data, int num, int dim);

    const float* getVector(int i) const;
    int getN() const;
    int getDim() const;
};


#endif //ANN_RETRIEVIAL_DATASET_H