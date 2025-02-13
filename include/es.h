#ifndef _ES_H_
#define _ES_H_

#include "busqueda.h"

class ES : public Busqueda {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        ES(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

    protected:

        // Características del algoritmo
        double _mu = 0.3;
        double _phi = 0.3;
        double T_f = 0.001;
        int max_ev = 100000;
        bool nueva_sol = true;

        /**
         * @brief Calcula una solución vecina para una dada
         * @param s Solución actual
         * @return Solución vecina generada aleatoriamente
         */
        Solucion solucionVecina(const Solucion &s);

        ES& operator=(const Solucion &s);
};

#endif