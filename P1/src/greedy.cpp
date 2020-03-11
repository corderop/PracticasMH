#include "greedy.h"

Greedy::Greedy(vector<vector<float>> _X, vector<vector<int>> _MR, int _k){
    this->X = _X;
    this->MR = _MR;
    this->k = _k;
    this->c_ic = vector<float>(k);
    inf_total = 0;
    time = 0;

    if(!X.empty())
        this->n = X.size();
    else{
        cout<<"Conjunto de datos vacío"<<endl;
         assert(true);
    }
    C_vacios = vector<bool>(k, false);
    num_vacios = k;

    this->calcularCentroidesIniciales();
    this->busqueda();
    this->desviacionGeneral();
}

void Greedy::calcularCentroidesIniciales(){
    U.clear();
    int a = X[0].size();

    for(int i=0; i<k; i++){
        vector<float> aux(0);
        for(int j=0; j<a; j++){
            aux.push_back(Randfloat(0.0, 10.0));
        }
        U.push_back(aux);
    }
}

void Greedy::busqueda(){
    // Declaración de variables

    // RSI barajado de forma aleatoria
    vector<int> RSI;
    generarVector(RSI, n);

    // Partición de clusters
    C = vector<vector<int>>(k, vector<int>(0));
    vector<vector<int>> ant_C(0);

    bool cambiado;

    unsigned t0, t1;
 
    t0=clock();

    do{
        ant_C = C;
        inf_total = 0;
        asig = vector<int>(n, -1);

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

int Greedy::deboAniadir(int &out_pos, int inst){
    int out = 0;
    int size = MR[inst].size();
    
    for(int i=0; i<size && out != -1; i++){
        if(MR[inst][i] == 1 && inst!=i && asig[i]!=-1){
            if(out != 1){
                // Debe añadir
                out = 1;
                out_pos = asig[i];
            }
            else if(out_pos != asig[i])
                out = -1;
        }    

    }

    return out;
}

void Greedy::aniadir(int inst, int cluster){

    C[cluster].push_back(inst);
    asig[inst] = cluster;
    if(!C_vacios[cluster]){
        num_vacios--;
        C_vacios[cluster] = true;
    }
}

void Greedy::calcularCentroide(int a){
    int n = U[a].size();
    int n2 = C[a].size();
    U[a] = vector<float>(n,0.0);
    
    // Recorro U
    for(int i=0; i<n; i++)
        for(int j=0; j<n2; j++)
            U[a][i] += ( X[C[a][j]][i]/n2 );
}

int Greedy::infeasibilityUna(int a, int b){
    int out = 0;
    int size = MR[a].size();

    for(int i=0; i<size; i++){
        if(i!=a){
            if(MR[a][i] == 1 && ( asig[i]!=b && asig[i]!=-1 )){
                out++;
            }
            else if(MR[a][i] == -1 && asig[i]==b){
                out++;
            }
        }
    }

    return out;
}

void Greedy::distanciaMediaIntraCluster(){

    for(int i=0; i<k; i++){
        int n = C[i].size();
        c_ic[i] = 0;
        for(int j=0; j<n; j++)
            c_ic[i] += distanciaEuclidea(X[j], U[i])/n;
        
    }

}

void Greedy::desviacionGeneral(){

    this->distanciaMediaIntraCluster();
    desviacion = 0;

    for(int i=0; i<k; i++)
        desviacion += c_ic[i];

    desviacion /= k;
}

void Greedy::mostrarResultado(){

    cout<<"Resultado Greedy: "<<endl;
    cout<<"Desviación general (Tasa_C): "<<desviacion<<endl;
    cout<<"Infeasability (Tasa_inf): "<<inf_total<<endl;
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