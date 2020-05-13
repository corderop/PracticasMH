#include "es.h"

void ES::realizarBusqueda(){
    unsigned t0, t1;
    Solucion s, s_new, mejor_sol;
    int ev = 0;

    // Genero la solución inicial y la tomo como mejor solución
    generarSolucionInicial();
    funcionObjetivo();
    ev++;
    s = (*this);
    mejor_sol = s;

    t0 = clock();

    // Tomo el valor inicial de T
    double T = ( _mu*s.obj) / (-log(_phi));
    int max_vecinos = 10*n;
    int max_exitos = 0.1*max_vecinos;
    double M = (100000/max_vecinos)*(100000/max_vecinos);
    double beta = (T-T_f)/(M*T*T_f);

    while(T > T_f && ev < 100000){
        int exitos = 0;

        for(int i=0 ; i<max_vecinos && exitos<max_exitos ; i++){
            s_new = solucionVecina(s);  // Calcula la nueva solución
            ev++;
            double dif = s_new.obj - s.obj; // Calculo la diferencia de costos

            if( dif < 0 || Randdouble(0,1) <= exp(-dif/T)){
                s = s_new;
                exitos++;
                if( s < mejor_sol )
                    mejor_sol = s;
            }
        }
        // Calculo de la nueva temperatura
        T = T/(1+beta*T);
    }

    (*this) = mejor_sol;
    this->recalcularSolucion();
    this->funcionObjetivo();

    t1 = clock();
    time = ( double(t1-t0)/CLOCKS_PER_SEC );

}

Solucion ES::solucionVecina(const Solucion &s){
    Solucion salida, copia;
    int i_r = Randint(0, n-1),
        l_r = Randint(0, k-1);

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