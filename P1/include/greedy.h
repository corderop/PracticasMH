#ifndef _GREEDY_H_
#define _GREEDY_H_

#include "aux.h"

// Genera el vector RSI para tener las componenetes.
void generarVector(vector<int> &i);

float distanciaEuclidea(const vector<int> &a, const vector<int> &b);

vector<pair<float,int>> distancias(const vector<int> &X, const vector<vector<int>> &U);

bool aniadir(int n, int cluster, const vector<vector<int>> &C, const vector<vector<int>> &MR);

// Calcula si debe de añadir el nodo en un cluster específico. 
// Si lo debe añadir devuelve 1
// Si no tiene porqué devuelve 0
// Si lo debe de añadir en dos devuelve -1
// Devuelve el número con el que tiene que estar en out_pos
int deboAniadir(int &out_pos, const vector<int> &asig, int n, const vector<vector<int>> &MR);

// Implementación del algoritmo greedy
vector<vector<int>> greedy(const vector<vector<int>> &X, 
                           const vector<vector<int>> &R,
                           const int k, const vector<vector<int>> &U);

#endif