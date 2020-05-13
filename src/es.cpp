#include "es.h"

void ES::realizarBusqueda(){
    Solucion s, s_aux, mejor_sol;

    // Tomo el valor inicial de T

    // Genero la solución inicial y la tomo como mejor solución
    generarSolucionInicial();
    funcionObjetivo();
    s = (*this);
    mejor_sol = s;

    do{
        for(){
            // s' <- nueva solución a partir de actual
            // Calculo la diferencia de costos
            double diferencia_costos = s1.obj - s.obj;
            if( diferencia_costos < 0) ||  /* U(0,1) */){
                s = s1;

                if( s < mejor_sol )
                    mejor_sol = s;
            }
        }
        // Calculo de la nueva temperatura
    }while(/* T <= Tfinal */);

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