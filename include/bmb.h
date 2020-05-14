#ifndef _BMB_H_
#define _BMB_H_

#include "busqueda.h"

class BMB : public Busqueda {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        BMB(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

    protected:

        /**
         * @brief Calcula una solución vecina para una dada
         * @param s Solución actual
         * @return Solución vecina generada aleatoriamente
         */
        // Solucion solucionVecina(const Solucion &s);

        BMB& operator=(const Solucion &s);
};

#endif