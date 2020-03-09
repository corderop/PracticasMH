#include "greedy.h"

Greedy::Greedy(vector<vector<float>> _X, vector<vector<int>> _MR, int _k){
    this->X = _X;
    this->MR = _MR;
    this->k = _k;

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
}

void Greedy::calcularCentroidesIniciales(){
    U.clear();
    int a = X[0].size();

    // for(int i=0; i<k; i++){
    //     vector<float> aux(0);
    //     for(int j=0; j<a; j++){
    //         aux.push_back(Randfloat(0.0, 100.0));
    //     }
    //     U.push_back(aux);
    // }

    vector<float> aux1(0);
    aux1.push_back(3);
    aux1.push_back(2);
    U.push_back(aux1);
    aux1 = vector<float>(0);
    aux1.push_back(6);
    aux1.push_back(2);
    U.push_back(aux1);

}

void Greedy::busqueda(){
    // Declaración de variables

    // RSI barajado de forma aleatoria
    vector<int> RSI;
    generarVector(RSI, n);

    // Obtiene el cluster asignado a cada instancia
    asig = vector<int>(n, -1);
    // Partición de clusters
    C = vector<vector<int>>(k, vector<int>(0));
    vector<vector<int>> ant_C(0);

    // Sale si no hay solución
    bool salir = false;
    bool cambiado;

    do{
        ant_C = C;

        for(int i=0; i<k && !salir; i++)
            C[i].clear();

        for(int i=0; i<n && !salir; i++){
            int j = RSI[i];
            vector<pair<float,int>> d = distancias(j);
            bool aniadido = false;
            int pos_ML = -1;
            int debo = deboAniadir(pos_ML, j);

            if(debo==0){
                // No hay restricciones ML
                if((n-i) != num_vacios){
                    for(int h=0; h<d.size() && !aniadido; h++)
                        aniadido = aniadir(j, d[h].second);
                }
                else{
                    for(int h=0; h<C_vacios.size() && !aniadido; h++){
                        if(!C_vacios[h])
                            aniadido = aniadir(j, h);
                    }
                }

                salir = !aniadido;
            }
            else if(debo==1){
                // Se debe añadir en un cluster específico
                aniadido = aniadir(j, pos_ML);
                salir = !aniadido;
            }
            else{
                // Finaliza el algoritmo ya que no se puede asignar
                // un cluster sin romper una restricción ML
                salir = true;
            }
        }

        cambiado = (ant_C != C);

        if(cambiado && !salir)
            for(int i=0; i<k; i++)
                calcularCentroide(i);

    }while(cambiado && !salir);

    if(!salir)
        C = ant_C;
    else
        C = vector<vector<int>>(0);
    
}

vector<pair<float,int>> Greedy::distancias(int a){
    int n = U.size();
    vector<pair<float,int>> out(0);

    for(int i=0; i<n; i++){
        pair<float,int> p(distanciaEuclidea(X[a], U[i]), i); 
        out.push_back(p);
    }

    sort(out.begin(), out.end());

    return out;
}

int Greedy::deboAniadir(int &out_pos, int inst){
    int out = 0;
    int size = MR.size();
    bool uno_aniadido = false;
    
    for(int i=0; i<size && out != -1; i++){
        if(MR[inst][i] == 1 && inst!=i){
            if(out != 1 && asig[i]!=-1){
                // Debe añadir
                out = 1;
                out_pos = asig[i];
            }
            else if(out == 1)
                out = -1;
        }        
    }

    return out;
}

bool Greedy::aniadir(int inst, int cluster){
    bool out = true;
    // bool encontrado = false;
    int size = C[cluster].size();

    for(int i = 0; i<size && out; i++)
        out = ( MR[inst][C[cluster][i]] != -1 );

    if(out){
        C[cluster].push_back(inst);
        asig[inst] = cluster;
        if(!C_vacios[cluster]){
            num_vacios--;
            C_vacios[cluster] = true;
        }
    }

    return out;
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

/////////////////////////////////////////
// FUNCIONES AUXILIARES
/////////////////////////////////////////

void generarVector(vector<int> &v, int n){
    v.resize(n);

    for(int i=0; i<n ; i++)
        v[i] = i;
    
    random_shuffle(v.begin(), v.end());
}

float distanciaEuclidea(const vector<float> &a, const vector<float> &b){
    float sum=0;
    int n = a.size();

    for(int i=0; i<n; i++)
        sum += (b[i]-a[i])*(b[i]-a[i]);

    return sqrt(sum);
}