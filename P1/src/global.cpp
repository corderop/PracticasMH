#include "global.h"

vector<vector<int>> restriccionesALista(const vector<vector<int>> &m){
    vector<vector<int>> out(0);
    int n = m.size();

    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            if(m[i][j] != 0){
                int aux[] = {i, j, m[i][j]};
                vector<int> aux2(aux, aux+sizeof(aux) / sizeof(int));
                out.push_back(aux2);
            }

    return out;
}