#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "global.h"

using namespace std;

int main(){
    
    // Variables principales
    vector<vector<float>> data = leerDatos<float>("data/iris_set.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/aa.dat");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);
}