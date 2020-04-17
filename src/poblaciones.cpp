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
        P.resize(0);

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

        float no_mutaciones = P_m*M*n;
        for(int i=0; i<no_mutaciones; i++){
            int r1 = Randint(0,M-1),
                r2 = Randint(0,n-1);
            mutacion(r1,r2);
            evaluaciones++;
        }
    }

    // Tomo la mejor solución
    this->mejor_sol = 0;
    for(int i=1; i<P.size(); i++)
        if(P[i] < P[mejor_sol])
            mejor_sol = i;

    (*this) = P[mejor_sol];

}

void Poblaciones::generarPoblacionInicial(){
    P = vector<Solucion>(0);
    P.reserve(M);

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
        evaluaciones++;
    }

    return evaluaciones;
}

void Poblaciones::evaluarSolucion(Solucion &s){
    // Almacena en la clase como solución actual
    (*this) = s;

    // Calcula la función objetivo
    this->funcionObjetivo();

    // Vuelve a copiar en s los valores con la función ya calculada
    s = (*this);
}

void Poblaciones::torneoBinario(){
    mejor_pad = 0;

    for(int i=0 ; i<M; i++){
        int a = Randint(0, M-1),
            b = Randint(0, M-1);
        // Seleccionamos el mejor
        if(this->P[a] < P[b]){
            P_t.push_back(P[a]);
            if(P[a] < P_t[mejor_pad])
                mejor_pad = i;
        }
        else{
            P_t.push_back(P[b]);
            if(P[b] < P_t[mejor_pad])
                mejor_pad = i;
        }
    }
}

int Poblaciones::cruceUniforme(Solucion &p1, Solucion &p2){
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
    
    hijo1 = (*this);

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
    
    hijo2 = (*this);

    P.push_back(hijo2);
    calculoObjetivo = 2;

    return calculoObjetivo;
}

int Poblaciones::cruceSegmentoFijo(Solucion &p1, Solucion &p2){
    // Solucion hijo1, hijo2;
    int calculoObjetivo = 0;

    int r = Randint(0,n-1),
        v = Randint(n/2,n-1); // Favorecemos la explotación

    // Tomo el portador del segmento
    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    vector<int> out(n-v);
    iota(begin(out), end(out), (r+v)%n);
    random_shuffle(out.begin(), out.end());

    for(int i=0; i<out.size(); i++){
        if(i < (n-v)/2)
            this->S[out[i]] = p1.S[out[i]];
        else
            this->S[out[i]] = p2.S[out[i]];
    }

    recalcularSolucion();
    funcionObjetivo();

    Solucion hijo1;

    hijo1 = (*this);
    this->P.push_back(hijo1);

    r = Randint(0,n-1);
    v = Randint(n/2,n-1); // Favorecemos la explotación
    
    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    out = vector<int>(n-v);
    iota(begin(out), end(out), (r+v)%n);
    random_shuffle(out.begin(), out.end());

    for(int i=0; i<out.size(); i++){
        if(i < (n-v)/2)
            this->S[out[i]] = p1.S[out[i]];
        else
            this->S[out[i]] = p2.S[out[i]];
    }

    recalcularSolucion();
    funcionObjetivo();
    Solucion hijo2;

    hijo2 = (*this);
    this->P.push_back(hijo2);
    calculoObjetivo = 2;

    return calculoObjetivo;
}

void Poblaciones::recalcularSolucion(){
    this->C = vector<vector<int>>(k, vector<int>(0));
    this->c_ic = vector<double>(k);
    this->inf_total = 0;
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
    while(P[c].n_c[P[c].S[g]] <= 1){
        g = Randint(0,n-1);
    }
    
    this->S = P[c].S;
    this->S[g] = Randint(0,k-1);

    recalcularSolucion();
    funcionObjetivo();

    P.erase(P.begin()+c);
    Solucion mut;

    mut = (*this);

    P.push_back(mut);
}


Poblaciones& Poblaciones::operator=(const Solucion &s){
    this->U = s.U;
    this->C = s.C;
    this->S = s.S;
    this->c_ic = s.c_ic;
    this->obj = s.obj;
    this->desviacion = s.desviacion;
    this->inf_total = s.inf_total;
    this->n_c = s.n_c;
 
    return *this;
}