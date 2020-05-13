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
    // cout<<desviacion<<","<<inf_total<<","<<obj<<","<<time<<endl;
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
    int n1 = U[a].size();
    int n2 = C[a].size();

    // Recorro U
    for(int i=0; i<n1; i++){
        U[a][i] = 0.0;
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


void Busqueda::recalcularSolucion(){
    this->inf_total = 0;
    this->num_vacios = k;

    for(int i=0; i<k; i++){
        this->C[i].clear();
        this->n_c[i] = 0;
        this->C_vacios[i] = false;
    }

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
                }while(n_c[random]<=1);

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