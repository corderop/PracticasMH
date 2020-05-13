#ifndef _LOCAL_H_
#define _LOCAL_H_

#include "busqueda.h"

class Local : public Busqueda {

    public:

        /**
         * @brief Inicializa los datos necesarios
         * @param _X Conjunto de datos
         * @param _MR Matriz de restricciones
         * @param _k Número de clusters
         */
        Local(vector<vector<double>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

    protected:

        /**
         * @brief Recalcula F para un cambio
         */
        double recalcularF(const pair<int,int> &cambio);

        /**
         * @brief Generamos el vecindario
         */
        vector<pair<int,int>> generamosVecindario();

};

struct copia{
    vector<vector<double>> U;
    vector<vector<int>> C;
    vector<int> S;
    vector<double> c_ic;
    vector<int> n_c;
    double obj;
    double desviacion;
    int inf_total;
};

#endif