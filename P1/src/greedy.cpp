#include "greedy.h"

void generarVector(vector<int> &v, int n){
    v.clear();

    for(int i=0; i<n ; i++)
        v[i] = i;
    
    random_shuffle(v.begin(), v.end());
}

float distanciaEuclidea(const vector<int> &a, const vector<int> &b){
    float sum=0;
    int n = a.size();

    for(int i=0; i<n; i++)
        sum += (b[i]-a[i])*(b[i]-a[i]);

    return sqrt(sum);
}

vector<pair<float,int>> distancias(const vector<int> &X, const vector<vector<int>> &U){
    int n = U.size();
    vector<pair<float,int>> out(0);

    for(int i=0; i<n; i++){
        pair<float,int> p(distanciaEuclidea(X, U[i]), i); 
        out.push_back(p);
    }

    sort(out.begin(), out.end());

    return out;
}

vector<vector<int>> greedy(const vector<vector<int>> &X, const vector<vector<int>> &MR, const int k, const vector<vector<int>> &U){
    // Declaración de variables
    int n = X.size();
    // RSI barajado de forma aleatoria
    vector<int> RSI;
    generarVector(RSI, n);

    do{
        for(int i=0; i<n; i++){
            int j = RSI[i];
            vector<pair<float,int>> d = distancias(X[j], U);

            for(int h=0; h<d.size(); h++){
                
            }

            return vector<vector<int>>(0);
        }

        for(int i=0; i<k; i++){

        }

    }while(n);
}