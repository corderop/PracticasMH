#ifndef _BUSQUEDA_H_
#define _BUSQUEDA_H_

#include "aux.h"
#include "global.h"

class Busqueda{


    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Busqueda(vector<vector<float>> _X, vector<vector<int>> _MR, int _k);

        // GLOBAL -------------------------------------------

        /**
         * @brief Muestra el resultado obtenido en el cálculo
         */
        void mostrarResultado();

        /**
         * @brief Realiza la búsqueda de una solución
         */
        virtual void realizarBusqueda() = 0;

    protected:

        // Conjunto de datos
        vector<vector<float>> X;
        // Centroides
        vector<vector<float>> U;
        // Conjunto de restricciones
        vector<vector<int>> MR;
        vector<vector<int>> LR;
        // Reparto por clusters
        vector<vector<int>> C;
        // Solución búsqueda local
        vector<int> S;
        // Número de instancias
        int n;
        // Número de clusters
        int k;
        // Infeasibility total
        int inf_total;
        // Desviación general de la particion
        float desviacion;
        // Tiempo
        float time;
        // Valor objetivos
        float obj;
        // Clusters vacios
        vector<bool> C_vacios;
        // Número de clusters vacíos en un momento
        int num_vacios;
        // Distancia media intracluster
        vector<float> c_ic;
        // Factor
        float lambda;
        // Número de elementos en cada cluster
        vector<int> n_c;

        /**
         * @brief Calcula lambda necesaria para la función objetivo
         */
        void calculoLambda();

        /**
         * @brief Calcula el centroide de un cluster a partir de sus instancias
         * @param a Cluster del que calculamos
         */
        void calcularCentroide(int a);

        /**
         * @brief Calcula el número de restricciones incumplidas a partir de C
         */
        void infeasibilityTotal();

        /**
         * @brief Calcula la distancia media intra-cluster
         */
        void distanciaMediaIntraCluster();

        /**
         * @brief Desviación general de la partición a partir de las desviaciones intra-cluster
         */
        void desviacionGeneral();

        /**
         * @brief Calcula la función objetivo a partir de C
         * @return El valor de la evaluación
         */
        void funcionObjetivo();

};
#endif