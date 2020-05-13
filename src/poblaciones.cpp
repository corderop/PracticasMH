#include "poblaciones.h"

void Poblaciones::realizarBusqueda(){
    cout<<"-AGG-U-------------------------------"<<endl;
    realizarGeneracional('U');
    mostrarResultado();
    cout<<"-AGG-S-------------------------------"<<endl;
    realizarGeneracional('S');
    mostrarResultado();
    cout<<"-AGE-U-------------------------------"<<endl;
    realizarEstacionario('U');
    mostrarResultado();
    cout<<"-AGE-S-------------------------------"<<endl;
    realizarEstacionario('S');
    mostrarResultado();
    cout<<"-M-10-------------------------------"<<endl;
    realizarMemetico(1);
    mostrarResultado();
    cout<<"-M-0.1-------------------------------"<<endl;
    realizarMemetico(2);
    mostrarResultado();
    cout<<"-M-0.1e-------------------------------"<<endl;
    realizarMemetico(3);
    mostrarResultado();
    cout<<"--------------------------------"<<endl;
}

void Poblaciones::realizarGeneracional(char tipo){
    unsigned t0, t1;
    int evaluaciones = 0;
    t = 0;

    t0 = clock();

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
            if(tipo == 'U')
                evaluaciones += cruceUniforme(P_t[j], P_t[j+1]);
            else if(tipo == 'S')
                evaluaciones += cruceSegmentoFijo(P_t[j], P_t[j+1]);
        }
        for(int i=no_cruces*2; i<M; i++){
            P.push_back(P_t[i]);
        }

        float no_mutaciones = P_m*M*n;
        for(int i=0; i<no_mutaciones; i++){
            int r1 = Randint(0,M-1),
                r2 = Randint(0,n-1);
            mutacion(r1,r2);
            evaluaciones++;
        }

        // Mantenemos mejor padre
        int peor = max_element(P.begin(),P.end()) - P.begin(); 
        P[peor] = P_t[mejor_pad];
    }

    // Tomo la mejor solución
    this->mejor_sol = min_element(P.begin(),P.end()) - P.begin();

    (*this) = P[mejor_sol];

    t1 = clock();

	time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

void Poblaciones::realizarEstacionario(char tipo){
    unsigned t0, t1;
    int evaluaciones = 0;
    t = 0;

    t0 = clock();

    generarPoblacionInicial();
    evaluaciones += evaluarPoblacion();
    
    while(evaluaciones < 100000){
        t++;
        // Realizamos la selección
        torneoBinarioEstacionario();

        // Realizamos el cruce
        if(tipo == 'U'){
            evaluaciones += cruceUniformeEstacionario(P_t[0], P_t[1]);
        }
        else if(tipo == 'S'){
            evaluaciones += cruceSegmentoFijoEstacionario(P_t[0], P_t[1]);
        }


        float no_mutaciones = P_m*2*n;

        for(int i=0; i<2; i++){
            double prob = Randdouble(0,100);
            if(prob < (P_m*n)*100){
                int r2 = Randint(0,n-1);
                mutacionEstacionario(i,r2);
                evaluaciones++;
            }
        }

        // Obtenemos el índice del peor elemento
        int peor = max_element(P.begin(),P.end()) - P.begin(); 
        // Tomo el peor de los hijos    
        if(P_t[0] < P_t[1]){
            // Lo comparo con el peor de la población
            if(P_t[1] < P[peor]){
                // Intercambio el peor con el peor de los hijos
                P[peor] = P_t[1];
                // Cojo el segundo peor de la población
                peor = max_element(P.begin(),P.end()) - P.begin();
                if(P_t[0] < P[peor]){
                    P[peor] = P_t[0];
                }
            }
            else if(P_t[0] < P[peor]){
                P[peor] = P_t[0];
            }
        }
        else{
            if(P_t[0] < P[peor]){
                // Intercambio el peor con el peor de los hijos
                P[peor] = P_t[0];
                // Cojo el segundo peor de la población
                peor = max_element(P.begin(),P.end()) - P.begin();
                if(P_t[1] < P[peor]){
                    P[peor] = P_t[1];
                }
            }
            else if(P_t[1] < P[peor]){
                P[peor] = P_t[1];
            }
        }
    }

    // Tomo la mejor solución
    this->mejor_sol = min_element(P.begin(),P.end()) - P.begin();


    (*this) = P[mejor_sol];

    t1 = clock();

	time = ( double(t1-t0)/CLOCKS_PER_SEC );

}

void Poblaciones::realizarMemetico(int tipo){
    unsigned t0, t1;
    int evaluaciones = 0;
    t = 0;

    t0 = clock();

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
        for(int i=no_cruces*2; i<M; i++){
            P.push_back(P_t[i]);
        }

        float no_mutaciones = P_m*M*n;
        for(int i=0; i<no_mutaciones; i++){
            int r1 = Randint(0,M-1),
                r2 = Randint(0,n-1);
            mutacion(r1,r2);
            evaluaciones++;
        }

        // Mantenemos mejor padre
        int peor = max_element(P.begin(),P.end()) - P.begin(); 
        P[peor] = P_t[mejor_pad];

        if(t%10 == 0){
            if(tipo == 1){
                for(int i=0; i<M; i++){
                    this->S = P[i].S;
                    this->obj = P[i].obj;
                    evaluaciones += busquedaLocalSuave(0.1*n);
                    P[i].S = this->S;
                    P[i].obj = this->obj;
                }
            }
            else if(tipo == 2){
                int no_bl = 0.1*M;
                for(int i=0; i<no_bl; i++){
                    int r1 = Randint(0,M-1);
                    this->S = P[r1].S;
                    this->obj = P[r1].obj;
                    evaluaciones += busquedaLocalSuave(0.1*n);
                    P[r1].S = this->S;
                    P[r1].obj = this->obj;
                }
            }
            else{
                int no_bl = 0.1*M;
                vector<int> mejores(no_bl);
                vector<int> aux(no_bl);
                for(int i=0; i<no_bl ;i++){
                    mejores[i] = min_element(P.begin(),P.end()) - P.begin();
                    aux[i] = P[mejores[i]].obj;
                    P[mejores[i]].obj = 0;
                }
                for(int i=0; i<no_bl; i++){
                    P[mejores[i]].obj = aux[i];
                    this->S = P[mejores[i]].S;
                    this->obj = P[mejores[i]].obj;
                    evaluaciones += busquedaLocalSuave(0.1*n);
                    P[mejores[i]].S = this->S;
                    P[mejores[i]].obj = this->obj;
                }
            }
        }

    }

    this->mejor_sol = min_element(P.begin(),P.end()) - P.begin();

    (*this) = P[mejor_sol];

    t1 = clock();

	time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

int Poblaciones::busquedaLocalSuave(int e){
    int fallos = 0;
    bool mejora = true;
    int i=0;
    int evaluaciones = 0;

    vector<int> RSI;
    generarVector(RSI, n);

    while((mejora || fallos < e) && i<n){
        mejora = false;
        int cluster_actual = S[RSI[i]];
        int nuevo_cluster = -1;
        double obj_actual = obj;
        if(n_c[cluster_actual] > 1){
            for(int j=0; j<k; j++){
                if(j != cluster_actual){
                    S[RSI[i]] = j;
                    recalcularSolucion();
                    funcionObjetivo();
                    evaluaciones++;
                    if(obj < obj_actual){
                        nuevo_cluster = j;
                    }
                }
            }
        }
        // else
        //     fallos++;

        if(nuevo_cluster == -1){
            fallos++;
            S[RSI[i]] = cluster_actual;
            obj = obj_actual;
        }
        else{
            mejora=true;
            S[RSI[i]] = nuevo_cluster;
            recalcularSolucion();
            funcionObjetivo();
            evaluaciones++;
        }

        i++;
    }

    return evaluaciones;
}


void Poblaciones::generarPoblacionInicial(){
    P = vector<Solucion>(0);
    P.reserve(M);

    for(int i=0; i<this->M; i++){
        this->generarSolucionInicial();

        Solucion sol;

        sol.S = this->S;
        sol.obj = this->obj;

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

}

int Poblaciones::evaluarPoblacion(){
    int evaluaciones = 0;

    for(int i=0; i<M; i++){
        evaluarSolucion(this->P[i]);
        evaluaciones++;
    }

    return evaluaciones;
}

void Poblaciones::evaluarSolucion(Solucion &s){
    // Almacena en la clase como solución actual
    (*this) = s;

    // Calcula la función objetivo
    recalcularSolucion();
    this->funcionObjetivo();

    // Vuelve a copiar en s los valores con la función ya calculada
    s = (*this);
}

void Poblaciones::torneoBinario(){
    mejor_pad = 0;
    P_t = vector<Solucion>(0);

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

void Poblaciones::torneoBinarioEstacionario(){
    P_t = vector<Solucion>(0);

    int a = Randint(0, M-1),
        b = Randint(0, M-1);

    // Seleccionamos el mejor
    if(this->P[a] < P[b]){
        P_t.push_back(P[a]);
    }
    else{
        P_t.push_back(P[b]);
    }

    a = Randint(0, M-1);
    b = Randint(0, M-1);
        
    // Seleccionamos el mejor
    if(this->P[a] < P[b]){
        P_t.push_back(P[a]);
    }
    else{
        P_t.push_back(P[b]);
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

int Poblaciones::cruceUniformeEstacionario(Solucion &p1, Solucion &p2){
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

    p1 = hijo1;

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

    p2 = hijo2;
    calculoObjetivo = 2;

    return calculoObjetivo;
}

int Poblaciones::cruceSegmentoFijo(Solucion &p1, Solucion &p2){
    Solucion hijo1, hijo2;
    int calculoObjetivo = 0;

    int r = Randint(0,n-1),
        v = Randint(n/2,n-1); // Favorecemos la explotación


    // Toma la aleatoreidad de genes en un vector
    vector<int> out(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    // Tomo el portador del segmento
    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    for(int i=0; i<out.size(); i++){
        if( out[i]>=((r+v)%n) && out[i]<(((r+v)%n)+r) ){
            if(i < n/2)
                S[out[i]] = p1.S[out[i]];
            else
                S[out[i]] = p2.S[out[i]];
        }
    }

    recalcularSolucion();
    funcionObjetivo();
    
    hijo1 = (*this);

    P.push_back(hijo1);

    r = Randint(0,n-1);
    v = Randint(n/2,n-1); // Favorecemos la explotación

    out = vector<int>(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    for(int i=0; i<out.size(); i++){
        if( out[i]>=((r+v)%n) && out[i]<(((r+v)%n)+r) ){
            if(i < n/2)
                S[out[i]] = p1.S[out[i]];
            else
                S[out[i]] = p2.S[out[i]];
        }
    }

    recalcularSolucion();
    funcionObjetivo();
    
    hijo2 = (*this);

    P.push_back(hijo2);
    calculoObjetivo = 2;

    return calculoObjetivo;
}

int Poblaciones::cruceSegmentoFijoEstacionario(Solucion &p1, Solucion &p2){
    Solucion hijo1, hijo2;
    int calculoObjetivo = 0;

    int r = Randint(0,n-1),
        v = Randint(n/2,n-1); // Favorecemos la explotación


    // Toma la aleatoreidad de genes en un vector
    vector<int> out(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    // Tomo el portador del segmento
    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    for(int i=0; i<out.size(); i++){
        if( out[i]>=((r+v)%n) && out[i]<(((r+v)%n)+r) ){
            if(i < n/2)
                S[out[i]] = p1.S[out[i]];
            else
                S[out[i]] = p2.S[out[i]];
        }
    }

    this->recalcularSolucion();
    funcionObjetivo();
    
    hijo1 = (*this);

    p1 = hijo1;

    out = vector<int>(n);
    iota(begin(out), end(out), 0);
    random_shuffle(out.begin(), out.end());

    if(p1 < p2)
        S = p1.S;
    else
        S = p2.S;

    for(int i=0; i<out.size(); i++){
        if( out[i]>=((r+v)%8) && out[i]<(((r+v)%8)+r) ){
            if(i < n/2)
                S[out[i]] = p1.S[out[i]];
            else
                S[out[i]] = p2.S[out[i]];
        }
    }

    this->recalcularSolucion();
    funcionObjetivo();
    
    hijo2 = (*this);

    p2 = hijo2;
    calculoObjetivo = 2;

    return calculoObjetivo;
}


void Poblaciones::mutacion(int c, int g){
    // Comprueba que no deje un cluster vacio
    this->S = P[c].S;
    this->recalcularSolucion();
    while(n_c[S[g]] <= 1){
        g = Randint(0,n-1);
    }
    
    this->S[g] = Randint(0,k-1);

    this->recalcularSolucion();
    funcionObjetivo();

    Solucion mut;

    mut = (*this);

    P[c] = mut;
}

void Poblaciones::mutacionEstacionario(int c, int g){
    // Comprueba que no deje un cluster vacio
    this->S = P_t[c].S;
    recalcularSolucion();
    while(n_c[S[g]] <= 1){
        g = Randint(0,n-1);
        // recalcularSolucion();
    }
    
    // this->S = P_t[c].S;
    this->S[g] = Randint(0,k-1);

    recalcularSolucion();
    funcionObjetivo();

    Solucion mut;

    mut = (*this);

    P_t[c] = mut;
}



Poblaciones& Poblaciones::operator=(const Solucion &s){
    this->S = s.S;
    this->obj = s.obj;
 
    return *this;
}