#ifndef _LOCAL_H_
#define _LOCAL_H_

#include "aux.h"
#include "global.h"

class BusquedaLocal{

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
        // Infeasibility total
        int inf_total;
        // Distancia media intra-cluster
        

        /**
         * @brief Inicializa y calcula el resultado
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        BusquedaLocal(vector<vector<float>> _X, vector<vector<int>> _MR, int _k);

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
         * @return Priotity queue con el mejor candidato el primero
         */
        priority_queue<ordena, vector<ordena>, compara_ordena> distancias(int a);

        /**
         * @brief Calcula la distancia de una instancia con los diferentes centroides de los clusters vacios
         *        Minimizará la infeasibility y cumplirá la restricción de que todos los nodos deben tener una instancia
         * @param a instancia
         * @return Priotity queue con el mejor candidato el primero
         */
        priority_queue<ordena, vector<ordena>, compara_ordena> distanciasVacios(int a);

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
         */
        void aniadir(int inst, int cluster);

        /**
         * @brief Calcula el centroide de un cluster a partir de sus instancias
         * @param a Cluster del que calculamos
         */
        void calcularCentroide(int a);

        /**
         * @brief Calcula la infeasibility de una instancia respecto a un cluster
         * @param a Instancia para la que calcular
         * @param b Cluster para el que calcular
         * @return Valor de la infeasibility
         */
        int infeasibilityUna(int a, int b);
};
#endif