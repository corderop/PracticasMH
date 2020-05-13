#include "es.h"

void ES::realizarBusqueda(){

    // Tomo el valor inicial de T
    // Genero la solución inicial y la tomo como mejor solución

    do{
        for(){
            // s' <- nueva solución a partir de actual
            // Calculo la diferencia de costos
            diferencia_costos = s1.obj - s.obj;
            if( diferencia_costos < 0) ||  /* U(0,1) */){
                s = s1;

                if( s.obj < mejor_solucion.obj )1
                    mejor_solucion = s;
            }
        }
        // Calculo de la nueva temperatura
    }while(/* T <= Tfinal */);

}