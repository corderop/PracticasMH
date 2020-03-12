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
float distanciaEuclidea(const vector<float> &a, const vector<float> &b);

/**
 * @brief Genera un vector aleatorio que contenga componentes de 0 a n-1
 * @param v Vector de salida
 * @param n Número a de vector maximo
 */
void generarVector(vector<int> &v, int n);

struct ordena{
    int cluster;
    int inf;
    float distancia;
};

struct compara_ordena{

    bool operator()(ordena const& p1, ordena const& p2){
        bool out = false;

        if( p1.inf > p2.inf || (p1.inf == p2.inf && p1.distancia > p2.distancia) )
            out = true;
        else
            out = false;

        return out;
    }
};

struct copia{
    vector<vector<float>> U;
    vector<vector<int>> C;
    vector<float> c_ic;
    float obj;
    float desviacion;
    int inf_total;
};

#endif