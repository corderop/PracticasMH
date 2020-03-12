#ifndef _BUSQUEDA_H_
#define _BUSQUEDA_H_

#include "aux.h"
#include "global.h"

class Busqueda{

    public:
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
        // Número de componentes de cada instancia de X
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

        /**
         * @brief Inicializa y calcula el resultado
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Busqueda(vector<vector<float>> _X, vector<vector<int>> _MR, int _k);

        /**
         * @brief Muestra el resultado obtenido en el cálculo
         */
        void mostrarResultado();

        /**
         * @brief Realiza la búsqueda de la solución mediante el método Greedy
         */
        void busquedaGreedy();

        /**
         * @brief Realiza la búsqueda de la solución mediante el método de búsqueda local
         */
        void busquedaLocal();

    private:
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

        // -- MÉTODOS GLOABLES -----------------------------------------

        /**
         * @brief Calcula lambda necesaria para la función objetivo
         */
        void calculoLambda();

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

        void funcionObjetivoDeS();

        /**
         * @brief Recalcula F para un cambio
         */
        float recalcularF(const pair<int,int> &cambio);

        // -- MÉTODOS BL -----------------------------------------

        /**
         * @brief Genera una solución inicial para la BL
         */
        void generarSolucionInicial();

        /**
         * @brief Generamos el vecindario
         */
        vector<pair<int,int>> generamosVecindario();

};
#endif