#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "global.h"
#include "greedy.h"

using namespace std;

int main(){
    srand(time(NULL));
    
    // Variables principales
    vector<vector<float>> data = leerDatos<float>("data/prueba.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/prueba.const");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);

    vector<vector<float>> U(0);

    vector<float> aux1(0);
    aux1.push_back(3.0);
    aux1.push_back(2.0);
    U.push_back(aux1);
    vector<float> aux2(0);
    aux2.push_back(6.0);
    aux2.push_back(2.0);
    U.push_back(aux2);

    vector<vector<int>> C = greedy(data, restricciones, 2, U);

    if(C.size() != 0)
        for(int i=0; i<C.size(); i++){
            cout<<endl<<"Cluster "<<i+1<<endl;
            for(int j=0; j<C[i].size(); j++){
                cout<<C[i][j]<<" ";
            }
            cout<<endl;
        }
    else{
        cout<<"No hay solución"<<endl;
    }
}