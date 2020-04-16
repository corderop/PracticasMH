#include "poblaciones.h"

void Poblaciones::realizarBusqueda(){
    int evaluaciones = 0;
    t = 0;

    generarPoblacionInicial();
    evaluaciones += evaluarPoblacion();
    
    while(evaluaciones < 100000){
        t++;
        // Realizamos la selección
        torneoBinario();
        
        // Realizamos el cruce
        
    }

}

void Poblaciones::generarPoblacionInicial(){
    P = vector<Solucion>(0);

    for(int i=0; i<this->M; i++){
        this->generarSolucionInicial();

        Solucion sol;

        sol.U = this->U;
        sol.C = this->C;
        sol.S = this->S;
        sol.c_ic = this->c_ic;
        sol.obj = this->obj;
        sol.desviacion = this->desviacion;
        sol.inf_total = this->inf_total;
        sol.n_c = this->n_c;

        this->P.push_back(sol);
    }
}


void Poblaciones::generarSolucionInicial(){
    this->C = vector<vector<int>>(k, vector<int>(0));
    this->c_ic = vector<double>(k);
    this->inf_total = 0;
    this->S = vector<int>(n);
    this->U = vector<vector<double>>(k, vector<double>(X[0].size()));
    this->num_vacios = k;
    this->n_c = vector<int>(k,0);
    this->C_vacios = vector<bool>(k, false);

    for(int i=0; i<n; i++){
        if( (n-i) != num_vacios ){
            int num = Randint(0,k-1);
            n_c[num]++;
            S[i] = num;
			C[num].push_back(i);
            if(!C_vacios[num]){
                num_vacios--;
                C_vacios[num] =true;
            }
        }
        else{
            bool introducido = false;
            for(int j=0; j<C_vacios.size() && !introducido; j++){
                if(!C_vacios[j]){
                    introducido = true;
                    C_vacios[j] = true;
                    n_c[j]++;
                    num_vacios--;
                    S[i] = j;
					C[j].push_back(i);
                }
            }
        }
    }

	// Calcula los centroides
	for(int i=0; i<k; i++)
        calcularCentroide(i);

}

int Poblaciones::evaluarPoblacion(){
    int evaluaciones = 0;

    for(int i=0; i<M; i++){
        evaluarSolucion(this->P[i]);
        // Comprobar que esto funcione
        if(this->P[i] < this->P[this->sol_min])
            this->sol_min = i;
        else if(this->P[i] > this->P[this->sol_max])
            this->sol_max = i;
        evaluaciones++;
    }

    return evaluaciones;
}

void Poblaciones::evaluarSolucion(Solucion &s){
    // Almacena en la clase como solución actual
    this->U = s.U;
    this->C = s.C;
    this->S = s.S;
    this->c_ic = s.c_ic;
    this->obj = s.obj;
    this->desviacion = s.desviacion;
    this->inf_total = s.inf_total;
    this->n_c = s.n_c;

    // Calcula la función objetivo
    this->funcionObjetivo();

    // Vuelve a copiar en s los valores con la función ya calculada
    s.U = this->U;              // Probablemente se pueda quitar
    s.C = this->C;              // Probablemente se pueda quitar
    s.S = this->S;              // Probablemente se pueda quitar
    s.c_ic = this->c_ic;        // Probablemente se pueda quitar
    s.obj = this->obj;
    s.desviacion = this->desviacion;
    s.inf_total = this->inf_total;
    s.n_c = this->n_c;          // Probablemente se pueda quitar
}

void Poblaciones::torneoBinario(){
    for(int i=0 ; i<M; i++){
        int a = Randint(0, M-1),
            b = Randint(0, M-1);
        
        // Seleccionamos el mejor
        if(this->P[a] > P[b])
            P_t.push_back(P[a]);
        else
            P_t.push_back(P[b]);
    }
}


