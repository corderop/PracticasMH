#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "global.h"
#include "greedy.h"

using namespace std;

int main(){
    // Inicialización de semillas aleatorias
    srand(time(NULL));
    Set_random(time(NULL));
    
    // Variables principales
    vector<vector<float>> data = leerDatos<float>("data/prueba.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/prueba.const");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);

    Greedy grd(data, restricciones, 2);

    if(grd.C.size() != 0)
        for(int i=0; i<grd.k; i++){
            cout<<endl<<"Cluster "<<i+1<<endl;
            for(int j=0; j<grd.C[i].size(); j++){
                cout<<grd.C[i][j]<<" ";
            }
            cout<<endl;
        }
    else
        cout<<"No hay solución"<<endl;
}