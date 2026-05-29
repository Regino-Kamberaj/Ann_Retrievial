//
// Created by Regino Kamberaj on 19/02/26.
//

#ifndef ANN_RETRIEVIAL_DISTANCES_H
#define ANN_RETRIEVIAL_DISTANCES_H

class SoADataset;

// Distanza euclidea base
float euclideanSquared(const float* a, const float* b, int dim);
float euclideanDistance(const float* a, const float* b, int dim);

// Distanza di manhattan
float manhattanDistance(const float* a, const float* b, int dim);

// Distanza coseno
float dotProduct(const float* a, const float* b, int dim);
float norm(const float* a, int dim);
float cosineDistance(const float* a, const float* b, int dim);

// Distanza euclidea SoA
float euclideanSquaredSoA(const float *query, const SoADataset &dataset, int idx);

void euclideanSquaredBatched(const float* query, const SoADataset& dataset, float* distances);

#endif //ANN_RETRIEVIAL_DISTANCES_H