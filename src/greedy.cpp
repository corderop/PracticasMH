#include "greedy.h"

void Greedy::realizarBusqueda(){
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


void Greedy::calcularCentroidesIniciales(){
    int a = X[0].size();

    for(int i=0; i<k; i++){
        for(int j=0; j<a; j++){
            U[i][j] = Randfloat(0.0, 10.0);
        }
    }
}


priority_queue<ordena, vector<ordena>, compara_ordena> Greedy::distancias(int a){
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


priority_queue<ordena, vector<ordena>, compara_ordena> Greedy::distanciasVacios(int a){
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


void Greedy::aniadir(int inst, int cluster){

    C[cluster].push_back(inst);
    S[inst] = cluster;
    if(!C_vacios[cluster]){
        num_vacios--;
        C_vacios[cluster] = true;
    }
}


int Greedy::infeasibilityUna(int a, int b){
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