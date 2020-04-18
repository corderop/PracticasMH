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

        void realizarBusqueda();

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarGeneracional(char tipo);

        void realizarEstacionario(char tipo);

        void busquedaLocalSuave(int e);

    protected:

        // Tamaño de la población
        const int M = 50;
        // Probabilidad de cruce
        const double P_c = 0.7;
        // Probabilidad de mutación
        const double P_m = 0.001;
        // Población actual
        vector<Solucion> P;
        // Padres
        vector<Solucion> P_t;
        // Solución mas alta
        int sol_max = 0;
        // Solución más baja
        int mejor_sol = 0;
        // Padres max
        int mejor_pad = 0;
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
         * @brief Torneo Binario
         */
        void torneoBinarioEstacionario();

        /**
         * @brief Operador de cruce uniforme
         * @param Padre 1
         * @param Padre 2
         * @return Veces que ha recalculado la función objetivo
         */
        int cruceUniforme(Solucion &p1, Solucion &p2);

        int cruceUniformeEstacionario(Solucion &p1, Solucion &p2);

        /**
         * @brief Operador de cruce de segmento fijo
         * @param Padre 1
         * @param Padre 2
         * @return Veces que ha recalculado la función objetivo
         */
        int cruceSegmentoFijo(Solucion &p1, Solucion &p2);
        int cruceSegmentoFijoEstacionario(Solucion &p1, Solucion &p2);

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
         * @param c Número de cromosoma
         * @param g Número de gen
         */
        void mutacion(int c, int g);
        void mutacionEstacionario(int c, int g);

        Poblaciones& operator=(const Solucion &s);
};

#endif