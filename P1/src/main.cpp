#include <iostream>
#include "aux.h"
#include "lectura.h"

using namespace std;

int main(){
    
    vector<vector<float>> v1 = leerDatos<float>("data/iris_set.dat");
    vector<vector<int>> v = leerDatos<int>("data/iris_set_const_10.const");

    cout<<"Tamaño: "<<v.size()<<endl;
    for(int i=0; i<v.size(); i++){
        for(int j=0; j<v[i].size(); j++){
            cout<<v[i][j]<<"  ";
        }
        cout<<endl;
    }
    
}