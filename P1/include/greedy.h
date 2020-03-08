#ifndef _GREEDY_H_
#define _GREEDY_H_

#include "aux.h"

// Genera el vector RSI para tener las componenetes.
void generarVector(vector<int> &i, int n);

float distanciaEuclidea(const vector<float> &a, const vector<float> &b);

vector<pair<float,int>> distancias(const vector<float> &X, const vector<vector<float>> &U);

bool aniadir(int n, int cluster, const vector<vector<int>> &C, const vector<vector<int>> &MR);

// Calcula si debe de añadir el nodo en un cluster específico. 
// Si lo debe añadir devuelve 1
// Si no tiene porqué devuelve 0
// Si lo debe de añadir en dos devuelve -1
// Devuelve el número con el que tiene que estar en out_pos
int deboAniadir(int &out_pos, const vector<int> &asig, int n, const vector<vector<int>> &MR);

void calcularCentroide(vector<float> &U, vector<int> &C, const vector<vector<float>> &X);

// Implementación del algoritmo greedy
vector<vector<int>> greedy(vector<vector<float>> &X, 
                           vector<vector<int>> &MR,
                           const int k, vector<vector<float>> &U);

#endif