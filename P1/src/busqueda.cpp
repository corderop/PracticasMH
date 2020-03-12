#include "busqueda.h"

Busqueda::Busqueda(vector<vector<float>> _X, vector<vector<int>> _MR, int _k){
    this->X = _X;
    this->MR = _MR;
    this->LR = restriccionesALista(MR);
    this->k = _k;
    this->C = vector<vector<int>>(k, vector<int>(0));
    this->c_ic = vector<float>(k);
    inf_total = 0;
    time = 0;
    n_c = vector<int>(k,0);

    if(!X.empty())
        this->n = X.size();
    else{
        cout<<"Conjunto de datos vacío"<<endl;
         assert(true);
    }
    
    this->S = vector<int>(n);
    this->U = vector<vector<float>>(k, vector<float>(X[0].size()));

    calculoLambda();

    C_vacios = vector<bool>(k, false);
    num_vacios = k;
}

// GLOBAL -------------------------------------------

void Busqueda::mostrarResultado(){
    this->desviacionGeneral();
    this->funcionObjetivo();

    cout<<"Resultado Busqueda: "<<endl;
    cout<<"Desviación general (Tasa_C): "<<desviacion<<endl;
    cout<<"Infeasability (Tasa_inf): "<<inf_total<<endl;
    cout<<"Agregado: "<<obj<<endl;
    cout<<"Tiempo: "<<time<<endl;
    cout<<"Clusters: "<<endl;

    for(int i=0; i<k; i++){
        cout<<"Cluster "<<i+1<<endl;
        for(int j=0; j<C[i].size(); j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
}


void Busqueda::calculoLambda(){

    // Distancia max del conjunto
    float D = 0;
    // Número de restricciones
    int R = LR.size();

    for(int i=0; i < (n-1); i++){
        for(int j=i+1; j<n; j++){
            float d = distanciaEuclidea(X[i], X[j]);
            if(d>D) D = d;
        }
    }

    lambda = D/R;
}


void Busqueda::calcularCentroide(int a){
    int n = U[a].size();
    int n2 = C[a].size();
    U[a] = vector<float>(n,0.0);
    
    // Recorro U
    for(int i=0; i<n; i++)
        for(int j=0; j<n2; j++)
            U[a][i] += ( X[C[a][j]][i]/n2 );
}


void Busqueda::infeasibilityTotal(){
    int size = LR.size();
    inf_total = 0;

    for(int i=0; i<size; i++ ){
        if( LR[i][2] == 1 && S[LR[i][0]]!=S[LR[i][1]] )
            inf_total++;
        else if( LR[i][2] == -1 && S[LR[i][0]]==S[LR[i][1]] )
            inf_total++;
    }
}


void Busqueda::distanciaMediaIntraCluster(){

    for(int i=0; i<k; i++){
        int n = C[i].size();
        c_ic[i] = 0;
        for(int j=0; j<n; j++)
            c_ic[i] += distanciaEuclidea(X[j], U[i])/n;
    }
}


void Busqueda::desviacionGeneral(){

    this->distanciaMediaIntraCluster();
    desviacion = 0;

    for(int i=0; i<k; i++)
        desviacion += c_ic[i];

    desviacion /= k;
}


void Busqueda::funcionObjetivo(){
    desviacionGeneral();
    infeasibilityTotal();

    obj = (desviacion + inf_total*lambda);
}



// GREEDY -------------------------------------------

void Busqueda::busquedaGreedy(){
    // Declaración de variables

    // RSI barajado de forma aleatoria
    vector<int> RSI;
    generarVector(RSI, n);

    // Partición de clusters
    vector<vector<int>> ant_C(0);

    // Calcula centroides aleatorios
    this->calcularCentroidesIniciales();

    bool cambiado;

    unsigned t0, t1;
 
    t0=clock();

    do{
        ant_C = C;
        inf_total = 0;
        S = vector<int>(n, -1);

        for(int i=0; i<k; i++)
            C[i].clear();

        for(int i=0; i<n; i++){
            int j = RSI[i];

            if((n-i) != num_vacios){
                priority_queue<ordena, vector<ordena>, compara_ordena> d = distancias(j);
                aniadir(j, d.top().cluster);
                inf_total += d.top().inf;
            }
            else{
                bool aniadido = false;
                priority_queue<ordena, vector<ordena>, compara_ordena> d = distanciasVacios(j);
                aniadir(j, d.top().cluster);
                inf_total += d.top().inf;
            }
        }

        vector<vector<int>> copy = C;
        sort(copy.begin(), copy.end());
        sort(ant_C.begin(), ant_C.end());
        cambiado = (ant_C != copy);

        if(cambiado)
            for(int i=0; i<k; i++)
                calcularCentroide(i);

    }while(cambiado);
    
    t1 = clock();

    time = ( float(t1-t0)/CLOCKS_PER_SEC );
}


void Busqueda::calcularCentroidesIniciales(){
    int a = X[0].size();

    for(int i=0; i<k; i++){
        for(int j=0; j<a; j++){
            U[i][j] = Randfloat(0.0, 10.0);
        }
    }
}


priority_queue<ordena, vector<ordena>, compara_ordena> Busqueda::distancias(int a){
    int n = U.size();
    priority_queue<ordena, vector<ordena>, compara_ordena> out;

    for(int i=0; i<n; i++){
        ordena aux;
        aux.cluster = i;
        aux.distancia = distanciaEuclidea(X[a], U[i]);
        aux.inf = infeasibilityUna(a, i); 
        out.push(aux);
    }

    return out;
}


priority_queue<ordena, vector<ordena>, compara_ordena> Busqueda::distanciasVacios(int a){
    int n = U.size();
    priority_queue<ordena, vector<ordena>, compara_ordena> out;

    for(int i=0; i<n; i++){
        if(!C_vacios[i]){
            ordena aux;
            aux.cluster = i;
            aux.distancia = distanciaEuclidea(X[a], U[i]);
            aux.inf = infeasibilityUna(a, i); 
            out.push(aux);
        }
    }

    return out;
}


void Busqueda::aniadir(int inst, int cluster){

    C[cluster].push_back(inst);
    S[inst] = cluster;
    if(!C_vacios[cluster]){
        num_vacios--;
        C_vacios[cluster] = true;
    }
}


int Busqueda::infeasibilityUna(int a, int b){
    int out = 0;
    int size = MR[a].size();

    for(int i=0; i<size; i++){
        if(i!=a){
            if(MR[a][i] == 1 && ( S[i]!=b && S[i]!=-1 )){
                out++;
            }
            else if(MR[a][i] == -1 && S[i]==b){
                out++;
            }
        }
    }

    return out;
}



// LOCAL --------------------------------------------

void Busqueda::busquedaLocal(){

	unsigned t0, t1;

	t0 = clock();

    generarSolucionInicial();
	funcionObjetivo();

	bool encontrado;
	int contador = 100000;

    do{
		vector<pair<int,int>> V = generamosVecindario();
		int size = V.size();
		encontrado = false;
		float new_f = 0;
		int cambio;

		for(int i=0; i<size && !encontrado && contador>0; i++){
			// Calcular nuevo objetivo
			contador--;
			new_f = recalcularF(V[i]);
			if(new_f > obj){
				encontrado = true;
				cambio = i;
			}
		}

		if(encontrado){
			S[V[cambio].first] = V[cambio].second;
			obj = new_f;
		}

    }while(encontrado);

	t1 = clock();

	time = ( float(t1-t0)/CLOCKS_PER_SEC );
}


void Busqueda::generarSolucionInicial(){
    
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


float Busqueda::recalcularF(const pair<int,int> &cambio){
	int cluster_nuevo = cambio.second;
	int cluster_anterior = S[cambio.first];
	int instancia = cambio.first;
    
    copia cp;

    cp.U = this->U;
    cp.C = this->C;
    cp.c_ic = this->c_ic;
    cp.obj = this->obj;
    cp.desviacion = this->desviacion;
    cp.inf_total = this->inf_total;

    // Recalcula C
    for(int i=0; i<k; i++){
        if( C[cluster_anterior][i] == instancia)
            C[cluster_anterior].erase(C[cluster_anterior].begin()+i);
    }
    C[cluster_nuevo].push_back(instancia);

    // Recalcula centroides
    calcularCentroide(cluster_anterior);
    calcularCentroide(cluster_nuevo);

    // Calcula la nueva funcion obj
    funcionObjetivo();

    float out = obj;

    if(obj<cp.obj){
        this->U = cp.U;
        this->C = cp.C;
        this->c_ic = cp.c_ic;
        this->obj = cp.obj;
        this->desviacion = cp.desviacion;
        this->inf_total = cp.inf_total;
    }

    return out;
}


vector<pair<int,int>> Busqueda::generamosVecindario(){
	vector<pair<int,int>> out(0);
	
	for(int i=0; i<n; i++){
		if(n_c[S[i]]>1){
			for(int j=0; j<k; j++){
				if(S[i]!=j)
					out.push_back(pair<int,int>(i, j));
			}
		}
	}

	random_shuffle(out.begin(), out.end());

	return out;
}