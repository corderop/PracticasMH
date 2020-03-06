#include "greedy.h"

void generarVector(vector<int> &v, int n){
    v.clear();

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

vector<pair<float,int>> distancias(const vector<float> &X, const vector<vector<float>> &U){
    int n = U.size();
    vector<pair<float,int>> out(0);

    for(int i=0; i<n; i++){
        pair<float,int> p(distanciaEuclidea(X, U[i]), i); 
        out.push_back(p);
    }

    sort(out.begin(), out.end());

    return out;
}

int deboAniadir(int &out_pos, const vector<int> &asig, int n, const vector<vector<int>> &MR){
    int out = 0;
    int size = MR.size();
    bool uno_aniadido = false;
    
    for(int i=0; i<size && out != -1; i++){
        if(MR[n][i] == 1 && n!=i){
            if(out != 1){
                // Debe añadir
                out = 1;
                out_pos = asig[i];
            }
            else
                out = -1;
        }        
    }

    return out;
}

bool aniadir(int n, int cluster, vector<vector<int>> &C, const vector<vector<int>> &MR){
    bool out = true;
    // bool encontrado = false;
    int size = C[cluster].size();

    for(int i = 0; i<size && out; i++)
        out = ( MR[C[cluster][i]][n] != -1 );

    if(out)
        C[cluster].push_back(n);

    return out;
}

// void suma(vector<int> &v){
//     float suma = 0;
//     int n = v.size();

//     for(int i=0; i<n; i++){
//         suma += v[i];
//     }
// }

void calcularCentroide(vector<float> &U, vector<int> &C, const vector<vector<float>> &X){
    int n = C.size();
    int n2 = X[0].size();
    U = vector<float>(n2,0.0);
    
    for(int i=0; i<n; i++)
        for(int j=0; j<n2; j++)
            U[j] += X[C[i]][j];
}

vector<vector<int>> greedy(const vector<vector<float>> &X, const vector<vector<int>> &MR, const int k, vector<vector<float>> &U){
    // Declaración de variables
    int n = X.size();
    // RSI barajado de forma aleatoria
    vector<int> RSI;
    generarVector(RSI, n);

    // Obtiene el cluster asignado a cada instancia
    vector<int> asig(n, -1);
    // Partición de clusters
    vector<vector<int>> C(k, vector<int>(0));

    // Será true si se produce un cambio en C
    bool cambiado = false;

    do{
        cambiado = false;
        for(int i=0; i<n; i++)
            C[i].clear();

        for(int i=0; i<n; i++){
            int j = RSI[i];
            vector<pair<float,int>> d = distancias(X[j], U);
            bool aniadido = false;
            int pos_ML = -1;
            int debo = deboAniadir(pos_ML, asig, j, MR);

            if(debo==0){
                // No hay restricciones ML
                for(int h=0; h<d.size() && !aniadido; h++){
                    aniadido = aniadir(j, d[h].second, C, MR);
                    if(aniadido)
                        cambiado = true;
                }
            }
            else if(debo==1){
                // Se debe añadir en un cluster específico
                C[pos_ML].push_back(j);
                cambiado = true;
                aniadido = true;
            }
            else{
                // Finaliza el algoritmo ya que no se puede asignar
                // un cluster sin romper una restricción ML
                return vector<vector<int>>(0);
            }
        }

        if(cambiado)
            for(int i=0; i<k; i++)
                calcularCentroide(U[i], C[i], X);

    }while(cambiado);

    return C;
}