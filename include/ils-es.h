#ifndef _ILSES_H_
#define _ILSES_H_

#include "es.h"

class ILS_ES : public ES {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        ILS_ES(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : ES(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusquedaILS();

    protected:

        void mutacion();

        ILS_ES& operator=(const Solucion &s);
};

#endif