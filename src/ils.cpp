#include "ils.h"

void ILS::realizarBusquedaILS(){
    unsigned t0, t1;
    int ev = 0;
    Solucion mejor_sol;
    this->nueva_sol = false;
    this->max_ev = 10000;

    t0 = clock();

    // Genera solución inicial
    this->generarSolucionInicial();
    this->funcionObjetivo();
    // Realiza la busqueda local
    this->realizarBusqueda();
    mejor_sol = (*this);

    for(int i=0; i<9; i++){
        this->mutacion();
        this->recalcularSolucion();
        this->funcionObjetivo();
        // Realiza la búsqueda local
        this->realizarBusqueda();
        // Criterio de aceptación
        if(mejor_sol.obj > this->obj)
            mejor_sol =(*this);
    }

    t1 = clock();
    time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

void ILS::mutacion(){
    Solucion s;
    int r = Randint(0,n-1),
        v = (int)0.1*n;

    for(int i=0 ; i<v; i++){
        int j = (r+i)%n,
            a = Randint(0,k-1);

        this->S[j] = a;
    }
}

ILS& ILS::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;
 
    return *this;
}