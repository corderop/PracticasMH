#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "greedy.h"
#include "local.h"

using namespace std;

int main(){

    int seed = 100;
    // Inicialización de semillas aleatorias
    srand(seed);
    Set_random(seed);
    
    // Variables principales
    vector<vector<float>> data = leerDatos<float>("data/rand_set.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/rand_set_const_10.const");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);

    cout<<"--------------------------------"<<endl;
    Local grd(data, restricciones, 3);
    grd.realizarBusqueda();
    grd.mostrarResultado();
    cout<<"--------------------------------"<<endl;
}