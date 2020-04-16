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

    protected:

        // Tamaño de la población
        const int M = 50;
        // Probabilidad de cruce
        const double P_c = 0.7;
        // Probabilidad de mutación
        const double P_m = 0.001;
        // Población actual
        vector<Solucion> P;
        // Solución candidata
        vector<Solucion> P_t;
        // Solución mas alta
        int sol_max = 0;
        // Solución más baja
        int sol_min = 0;
        // Generación
        int t;

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

        /**
         * @brief Torneo binario
         */
        void torneoBinario();

        /**
         * @brief Operador de cruce
         */
        void cruceUniforme(const Solucion &p1, const Solucion &p2);

        /**
         * @brief Genera cromosomas
         */
        void generarSolucionInicial();

        /**
         * @brief Recalcula la solución cuando se ha actualizado S
         */
        void recalcularSolucion();

        /**
         * @brief Realiza la mutación uniforme
         */
        void mutacion();
        
};

#endif