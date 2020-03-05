#ifndef _GREEDY_H_
#define _GREEDY_H_

#include "aux.h"

// Genera el vector RSI para tener las componenetes.
void generarVector(vector<int> &i);

float distanciaEuclidea(const vector<int> &a, const vector<int> &b);

// Implementación del algoritmo greedy
vector<vector<int>> greedy(const vector<vector<int>> &X, 
                           const vector<vector<int>> &R,
                           const int k, const vector<vector<int>> &U);

#endif