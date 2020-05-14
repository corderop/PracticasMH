#ifndef _BMB_H_
#define _BMB_H_

#include "local.h"

class BMB : public Local {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        BMB(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Local(_X, _MR, _k){};  

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusquedaBMB();

    protected:
    
        BMB& operator=(const Solucion &s);
};

#endif