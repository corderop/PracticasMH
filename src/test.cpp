#include <iostream>
#include "aux.h"
#include "lectura.h"
#include "greedy.h"
#include "local.h"
#include "poblaciones.h"

using namespace std;

int main(int argc, char* argv[]){

    int seed = time(NULL);
    seed = atoi(argv[1]);
    // seed = 120;
//     string S,
//            conjunto,
//            rest;

//     // Entrada del programas
//     if(argc < 3 ){
//         cout<<"Error en la entrada. Formato correcto: "<<endl;
//         cout<<"./exe g|bl conjunto %restricciones [semilla] "<<endl;
//         assert(false);
//     }
//     else{
//         S = string(argv[1]);
//         conjunto = string(argv[2]);
//         rest = string(argv[3]);
//         if(argc > 4)
//             seed = atoi(argv[4]);
//     }

//     // Inicialización de semillas aleatorias
    srand(seed);
    Set_random(seed);
    string conjunto = "ecoli";
    string rest = "10";
//     // Variables principales
    vector<vector<double>> data = leerDatos<double>("data/" + conjunto + "_set.dat");
    vector<vector<int>> restricciones = leerDatos<int>("data/" + conjunto + "_set_const_" + rest + ".const");
    vector<vector<int>> lista_rest = restriccionesALista(restricciones);

    int clusters = (conjunto == "ecoli") ? 8 : 3 ;

//     cout<<"--------------------------------"<<endl;
//     if(S == "g"){
//         Greedy grd(data, restricciones, clusters);
//         grd.realizarBusqueda();
//         grd.mostrarResultado();
//     }
//     if(S == "bl"){
//         Local lcl(data, restricciones, clusters);
//         lcl.realizarBusqueda();
//         lcl.mostrarResultado();
//     }
//     cout<<"--------------------------------"<<endl;

    Poblaciones p(data,restricciones,clusters);
    p.realizarBusqueda();

    cout<<"--------------------------------"<<endl;
}