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
        P = vector<Solucion>(0);

        // Realizamos el cruce
        int no_cruces = P_c*(M/2);
        for(int i=0; i<no_cruces; i++){
            int j = i*2;
            evaluaciones += cruceUniforme(P_t[j], P_t[j+1]);
        }
        for(int i=no_cruces*2; i<M-1; i++){
            P.push_back(P_t[i]);
        }
        if(mejor_pad < no_cruces*2)
            P.push_back(P_t[mejor_pad]);
        else
            P.push_back(P_t[M-1]);

        int no_mutaciones = P_m*M*n;
        for(int i=0; i<no_mutaciones; i++){
            int r1 = Randint(0,M-1),
                r2 = Randint(0,n-1);
            mutacion(r1,r2);
            evaluaciones++;
        }
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
        // if(this->P[i] < this->P[this->mejor_sol])
        //     this->mejor_sol = i;
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
        mejor_pad = 0;
        // Seleccionamos el mejor
        if(this->P[a] > P[b]){
            P_t.push_back(P[a]);
            if(P[a] < P[mejor_pad])
                mejor_pad = i;
        }
        else{
            P_t.push_back(P[b]);
            if(P[b] < P[mejor_pad])
                mejor_pad = i;
        }
    }
}

int Poblaciones::cruceUniforme(const Solucion &p1, const Solucion &p2){
    Solucion hijo1, hijo2;
    int calculoObjetivo = 0;

    // Toma la aleatoreidad de genes en un vector
    vector<int> out(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    for(int i=0; i<out.size(); i++){
        if(i < n/2)
            S[out[i]] = p1.S[out[i]];
        else
            S[out[i]] = p2.S[out[i]];
    }

    recalcularSolucion();
    funcionObjetivo();
    
    hijo1.U = this->U;              
    hijo1.C = this->C;              
    hijo1.S = this->S;              
    hijo1.c_ic = this->c_ic;        
    hijo1.obj = this->obj;
    hijo1.desviacion = this->desviacion;
    hijo1.inf_total = this->inf_total;
    hijo1.n_c = this->n_c;

    P.push_back(hijo1);

    out = vector<int>(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    for(int i=0; i<out.size(); i++){
        if(i < n/2)
            S[out[i]] = p1.S[out[i]];
        else
            S[out[i]] = p2.S[out[i]];
    }

    recalcularSolucion();
    funcionObjetivo();
    
    hijo2.U = this->U;              
    hijo2.C = this->C;              
    hijo2.S = this->S;              
    hijo2.c_ic = this->c_ic;        
    hijo2.obj = this->obj;
    hijo2.desviacion = this->desviacion;
    hijo2.inf_total = this->inf_total;
    hijo2.n_c = this->n_c;

    P.push_back(hijo2);
    calculoObjetivo = 2;

    return calculoObjetivo;
}

// int cruceSegmentoFijo

void Poblaciones::recalcularSolucion(){
    this->C = vector<vector<int>>(k, vector<int>(0));
    this->U = vector<vector<double>>(k, vector<double>(X[0].size()));
    this->num_vacios = k;
    this->n_c = vector<int>(k,0);
    this->C_vacios = vector<bool>(k, false);

    for(int i=0; i<this->S.size(); i++){
        C[S[i]].push_back(i);
        if(C[S[i]].size() == 1){
            num_vacios--;
            C_vacios[S[i]] = true;
        }
        n_c[S[i]]++;
    }

    // Si no hay ninguno vacio no entra
    if(num_vacios != 0){
        for(int i=0; i<C_vacios.size(); i++){
            if(!C_vacios[i]){
                int random;

                do{
                   random = Randint(0, C.size()-1); 
                }while(n_c[random]>1);

                int anterior = C[random][C[random].size()-1];
                C[random].pop_back();
                S[anterior] = i;
                C[i].push_back(anterior);
                num_vacios--;
                C_vacios[i] = true;
            }
        }
    }

    for(int i=0; i<this->C.size(); i++)
        calcularCentroide(i);
}

void Poblaciones::mutacion(int c, int g){
    // Comprueba que no deje un cluster vacio
    while(P[c].n_c[P[c].S[g]] > 1){
        g = Randint(0,n-1);
    }
    
    this->S = P[c].S;
    this->S[g] = Randint(0,k-1);

    recalcularSolucion();
    funcionObjetivo();

    P.erase(P.begin()+c);
    Solucion mut;

    mut.U = this->U;              
    mut.C = this->C;              
    mut.S = this->S;              
    mut.c_ic = this->c_ic;        
    mut.obj = this->obj;
    mut.desviacion = this->desviacion;
    mut.inf_total = this->inf_total;
    mut.n_c = this->n_c;

    P.push_back(mut);
}

