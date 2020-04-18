#include "busqueda.h"

Busqueda::Busqueda(vector<vector<double>> _X, vector<vector<int>> _MR, int _k){
    this->X = _X;
    this->MR = _MR;
    this->LR = restriccionesALista(MR);
    this->k = _k;
    this->C = vector<vector<int>>(k, vector<int>(0));
    this->c_ic = vector<double>(k);
    inf_total = 0;
    time = 0;
    n_c = vector<int>(k,0);

    if(!X.empty())
        this->n = X.size();
    else{
        cout<<"Conjunto de datos vacío"<<endl;
        assert(false);
    }
    
    this->S = vector<int>(n);
    this->U = vector<vector<double>>(k, vector<double>(X[0].size()));

    calculoLambda();

    C_vacios = vector<bool>(k, false);
    num_vacios = k;
}

void Busqueda::mostrarResultado(){
    this->funcionObjetivo();

    cout<<"Resultado Busqueda: "<<endl;
    cout<<"Desviación general (Tasa_C): "<<desviacion<<endl;
    cout<<"Infeasability (Tasa_inf): "<<inf_total<<endl;
    cout<<"Agregado: "<<obj<<endl;
    cout<<"Tiempo: "<<time<<endl;
    cout<<"Clusters: "<<endl;

    for(int i=0; i<k; i++){
        cout<<"Cluster "<<i+1<<" num: "<<n_c[i]<<endl;
        for(int j=0; j<C[i].size(); j++){
            cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }
}


void Busqueda::calculoLambda(){

    // Distancia max del conjunto
    double D = 0;
    // Número de restricciones
    int R = LR.size();

    for(int i=0; i < (n-1); i++){
        for(int j=i+1; j<n; j++){
            double d = distanciaEuclidea(X[i], X[j]);
            if(d>D) D = d;
        }
    }

    lambda = D/R;
}


void Busqueda::calcularCentroide(int a){
    int n = U[a].size();
    int n2 = C[a].size();
    U[a] = vector<double>(n,0.0);
    
    // Recorro U
    for(int i=0; i<n; i++){
        for(int j=0; j<n2; j++)
            U[a][i] += X[C[a][j]][i];
        U[a][i] /= n2;
    }
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
        int size = C[i].size();
        c_ic[i] = 0;
        for(int j=0; j<size; j++)
            c_ic[i] += distanciaEuclidea(X[C[i][j]], U[i]);
        c_ic[i] /= size;
    }
}


void Busqueda::desviacionGeneral(){

    this->distanciaMediaIntraCluster();
    this->desviacion = 0;

    for(int i=0; i<k; i++)
        this->desviacion += c_ic[i];

    this->desviacion /= k;
}


void Busqueda::funcionObjetivo(){
    desviacionGeneral();
    infeasibilityTotal();

    obj = (desviacion + inf_total*lambda);
}
