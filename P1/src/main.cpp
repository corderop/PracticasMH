#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "greedy.h"

using namespace std;

int main(){

    int seed = 1830;
    // Inicialización de semillas aleatorias
    srand(seed);
    Set_random(seed);
    
    // Variables principales
    vector<vector<float>> data = leerDatos<float>("data/iris_set.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/iris_set_const_20.const");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);

    cout<<"--------------------------------"<<endl;
    Greedy grd(data, restricciones, 3);
    grd.mostrarResultado();
    cout<<"--------------------------------"<<endl;
}