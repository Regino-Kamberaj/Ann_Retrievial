//
// Created by Regino Kamberaj on 18/02/26.
//

#ifndef FVECS_READER_H
#define FVECS_READER_H
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Legge un file in formato .fvecs
 * @param filename percorso del file
 * @param dim_out dimensione dei vettori in output
 * @param n_out numero di vettori in output
 * @return puntatore ad un array di floats, oppure nullptr se errato
 */
inline float* fvecs_read(const char* filename, int* dim_out, int* n_out);

/**
 * Leggo file .ivecs (stesso formato ma con interi)
 */
inline int* ivecs_read(const char* filename, int* dim_out, int* n_out);

std::vector<float> fvecs_read_vector(const char* filename, int* dim_out);

#ifdef __cplusplus
    }
#endif

#endif //ANN_RETRIEVIAL_FVECS_READER_H


