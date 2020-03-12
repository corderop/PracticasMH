#ifndef _GREEDY_H_
#define _GREEDY_H_

#include "busqueda.h"

class Greedy : public Busqueda {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Greedy(vector<vector<float>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

    protected:

        /**
         * @brief Calcula los centroides iniciales de forma aleatoria
         */
        void calcularCentroidesIniciales();

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
         * @brief Añade una instancia a un cluster si no se viola una restricción ML
         * @param inst Instancia a añadir
         * @param cluster Cluster donde añadirlo
         */
        void aniadir(int inst, int cluster);

        /**
         * @brief Calcula la infeasibility de una instancia respecto a un cluster
         * @param a Instancia para la que calcular
         * @param b Cluster para el que calcular
         * @return Valor de la infeasibility
         */
        int infeasibilityUna(int a, int b);
};

#endif