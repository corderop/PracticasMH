#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "aux.h"

/**
 * @brief Convierte las restricciones MR en LR
 * @param m Restricciones en formato MR
 * @return Restricciones en formato LR
 */
vector<vector<int>> restriccionesALista(const vector<vector<int>> &m);

/**
 * @brief Calcula la distancia euclídea de dos vectores
 * @param a Vector 1
 * @param b Vector 2
 * @return Distancia
 */
double distanciaEuclidea(const vector<double> &a, const vector<double> &b);

/**
 * @brief Genera un vector aleatorio que contenga componentes de 0 a n-1
 * @param v Vector de salida
 * @param n Número a de vector maximo
 */
void generarVector(vector<int> &v, int n);

#endif