#ifndef _ILS_H_
#define _ILS_H_

#include "local.h"

class ILS : public Local {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        ILS(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Local(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusquedaILS();

    protected:

        void mutacion();

        ILS& operator=(const Solucion &s);
};

#endif