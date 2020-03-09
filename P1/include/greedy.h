#ifndef _GREEDY_H_
#define _GREEDY_H_

#include "aux.h"

/**
 * @brief Genera un vector aleatorio para tomar el orden de procesamiento
 * @param v Vector de salida
 * @param n Número de vectores a asignar
 */
void generarVector(vector<int> &v, int n);

/**
 * @brief Calcula la distancia euclídea de dos vectores
 * @param a Vector 1
 * @param b Vector 2
 * @return Distancia
 */
float distanciaEuclidea(const vector<float> &a, const vector<float> &b);

class Greedy{

    public:
        // Conjunto de datos
        vector<vector<float>> X;
        // Centroides
        vector<vector<float>> U;
        // Conjunto de restricciones
        vector<vector<int>> MR;
        // Reparto por clusters
        vector<vector<int>> C;
        // Número de componentes de cada instancia de X
        int n;
        // Número de clusters
        int k;

        /**
         * @brief Inicializa y calcula el resultado
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Greedy(vector<vector<float>> _X, vector<vector<int>> _MR, int _k);

    private:
        // Cluster asignado a cada nodo
        vector<int> asig;
        // Clusters vacios
        vector<bool> C_vacios;
        int num_vacios;

        /**
         * @brief Calcula los centroides iniciales de forma aleatoria
         */
        void calcularCentroidesIniciales();

        /**
         * @brief Realiza la búsqueda de la solución
         */
        void busqueda();

        /**
         * @brief Calcula la distancia de una instancia con los diferentes centroides
         * @param a instancia
         * @return Vector ordenado de pair donde:
         *         - first: Distancia
         *         - second: Cluster
         */
        vector<pair<float,int>> distancias(int a);

        /** 
         * @brief Calcula si debe de añadir el nodo en un cluster específico. (Restricción ML)
         * @param out_pos Devuelve el número del cluster donde debe añadirse
         * @param inst Instancia que se tiene que checkear
         * @return - Si lo debe añadir devuelve 1
         *         - Si no tiene porqué devuelve 0
         *         - Si lo debe de añadir en dos devuelve -1
         */
        int deboAniadir(int &out_pos, int inst);

        /** 
         * @brief Añade una instancia a un cluster si no se viola una restricción ML
         * @param inst Instancia a añadir
         * @param cluster Cluster donde añadirlo
         * @return true: Cuando se añade
         *         false: Cuando no se añade
         */
        bool aniadir(int inst, int cluster);

        /**
         * @brief Calcula el centroide de un cluster a partir de sus instancias
         * @param a Cluster del que calculamos
         */
        void calcularCentroide(int a);
};
#endif