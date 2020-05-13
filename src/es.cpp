#include "es.h"

void ES::realizarBusqueda(){
    Solucion s, s_new, mejor_sol;
    int ev = 0;

    // Genero la solución inicial y la tomo como mejor solución
    generarSolucionInicial();
    funcionObjetivo();
    ev++;
    s = (*this);
    mejor_sol = s;

    // Tomo el valor inicial de T
    double T = ( 0.3*s.obj) / 0.3,
           T_f = 0.001;

    while(T <= T_f){
        for(){
            s_new = solucionVecina(s);  // Calcula la nueva solución
            ev++;
            double dif = s_new.obj - s.obj; // Calculo la diferencia de costos

            if( dif < 0) ||  /* U(0,1) */){
                s = s1;

                if( s < mejor_sol )
                    mejor_sol = s;
            }
        }
        // Calculo de la nueva temperatura
    }

}

Solucion ES::solucionVecina(const Solucion &s){
    Solucion salida, copia;
    int i_r = Randint(0, n),
        l_r = Randint(0, k);

    // No deje ningún cluster vacio
    while(n_c[S[i_r]]<=1){
        i_r = Randint(0,n);
    }

    (*this) = s;
    S[i_r] = l_r;
    this->recalcularSolucion();
    this->funcionObjetivo();

    salida = (*this);
    return salida;
}

ES& ES::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;
 
    return *this;
}