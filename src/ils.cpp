#include "ils.h"

void ILS::realizarBusqueda(){
    unsigned t0, t1;
    int ev = 0;
    Solucion s, s_new, mejor_sol;

    t0 = clock();

    

    t1 = clock();
    time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

ILS& ILS::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;
 
    return *this;
}