#ifndef _POBLACIONES_H_
#define _POBLACIONES_H_

#include "busqueda.h"

class Poblaciones : public Busqueda {

    public:

        /**
         * @brief Inicializa los datos necesarios
         */
        Poblaciones(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

        /**
         * @brief Genera cromosomas
         */
        void generarSolucionInicial();

    protected:

        // Tamaño de la población
        const int M = 50;
        // Población actual
        vector<Solucion> P;
        // Solución mas alta
        int sol_max = 0;
        // Solución más baja
        int sol_min = 0;

        /**
         * @brief Genera la población inicial
         */
        void generarPoblacionInicial();

        /**
         * @brief Evalúa la población
         * @return Número de evaluaciones realizadas
         */
        int evaluarPoblacion();

        /**
         * @brief Evalua una solucion concreta
         * @param s Solución a evaluar
         */
        void evaluarSolucion(Solucion &s);
};

#endif