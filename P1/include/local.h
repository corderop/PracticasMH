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
        Local(vector<vector<float>> _X, vector<vector<int>> _MR, int _k) 
            : Busqueda(_X, _MR, _k){};    

        /**
         * @brief Realiza la búsqueda del resultado
         */
        void realizarBusqueda();

    protected:

        /**
         * @brief Genera una solución inicial para la BL
         */
        void generarSolucionInicial();

        /**
         * @brief Recalcula F para un cambio
         */
        float recalcularF(const pair<int,int> &cambio);

        /**
         * @brief Generamos el vecindario
         */
        vector<pair<int,int>> generamosVecindario();

};

struct copia{
    vector<vector<float>> U;
    vector<vector<int>> C;
    vector<int> S;
    vector<float> c_ic;
    float obj;
    float desviacion;
    int inf_total;
};

#endif