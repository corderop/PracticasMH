// Referencias
// https://stackoverflow.com/questions/37957080/can-i-use-2-or-more-delimiters-in-c-function-getline
// 
#include "aux.h"
#include <fstream>
#include <sstream>

template <class T>
vector<vector<T>> leerDatos(string s){
    vector<vector<T>> out(0);
    string line;

    ifstream f(s);

    if(f.is_open())
        while(getline(f,line)){
            vector<T> v_line(0);
            stringstream st(line);

            while(getline(st, line, ',')){
                if (is_same<T, float>::value){ v_line.push_back(stof(line)); }
                else if(is_same<T, int>::value){ v_line.push_back(stoi(line)); }
            }
            
            out.push_back(v_line);
        }
    
    f.close();

    cout<<s<<" leído correctamente"<<endl;

    return out;
}