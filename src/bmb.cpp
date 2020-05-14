#include "bmb.h"

void BMB::realizarBusquedaBMB(){
    unsigned t0, t1;
    int ev = 0;
    Solucion mejor_sol;
    mejor_sol.obj = 999999;
    this->nueva_sol = false;
    this->max_ev = 10000;


    t0 = clock();

    for(int i=0; i<10; i++){
        generarSolucionInicial();
        funcionObjetivo();

        // Aplicar BL
        realizarBusqueda();

        // Comparar si es la mejor
        if(mejor_sol.obj > this->obj)
            mejor_sol = (*this);
    }

    (*this) = mejor_sol;
    this->recalcularSolucion();
    this->funcionObjetivo();

    t1 = clock();
    time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

BMB& BMB::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;

    return *this;
}