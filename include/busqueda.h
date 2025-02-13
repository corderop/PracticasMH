#ifndef _BUSQUEDA_H_
#define _BUSQUEDA_H_

#include "aux.h"
#include "global.h"

struct Solucion;

class Busqueda{


    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Busqueda(vector<vector<double>> _X, vector<vector<int>> _MR, int _k);

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
        vector<vector<double>> X;
        // Centroides
        vector<vector<double>> U;
        // Conjunto de restricciones
        vector<vector<int>> MR;
        vector<vector<int>> LR;
        // Reparto por clusters
        vector<vector<int>> C;
        // Solución en vector
        vector<int> S;
        // Número de instancias
        int n;
        // Número de clusters
        int k;
        // Infeasibility total
        int inf_total;
        // Desviación general de la particion
        double desviacion;
        // Tiempo
        double time;
        // Valor objetivos
        double obj;
        // Clusters vacios
        vector<bool> C_vacios;
        // Número de clusters vacíos en un momento
        int num_vacios;
        // Distancia media intracluster
        vector<double> c_ic;
        // Factor
        double lambda;
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

        /**
         * @brief Genera una solución inicial para la BL
         */
        void generarSolucionInicial();

        /**
         * @brief Recalcula la solución cuando se ha actualizado S
         */
        void recalcularSolucion();

        friend class Solucion;
};

struct Solucion{
    vector<int> S;
    double obj;

    bool operator<(const Solucion &s2){
        return obj < s2.obj;
    }

    bool operator>(const Solucion &s2){
        return obj > s2.obj;
    }

    Solucion& operator=(const Solucion &s2){
        S = s2.S;
        obj = s2.obj;

        return *this;
    }

    Solucion& operator=(const Busqueda &b){   
        this->S = b.S;              
        this->obj = b.obj;    

        return *this;   
    }
};
#endif