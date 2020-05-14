#include "bmb.h"

void BMB::realizarBusquedaBMB(){
    unsigned t0, t1;
    int ev = 0;
    Solucion s, s_new, mejor_sol;
    Local lcl;

    t0 = clock();

    for(int i=0; i<10; i++){
        generarSolucionInicial();
        funcionObjetivo();

        // Aplicar BL

        // Comparar si es la mejor
    }

    t1 = clock();
    time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

BMB& BMB::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;

    return *this;
}