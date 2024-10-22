#include "local.h"

void Local::realizarBusqueda(){

	unsigned t0, t1;

	t0 = clock();

    if(nueva_sol){
        generarSolucionInicial();
        funcionObjetivo();
    }
    
	bool encontrado;
	int contador = max_ev;

    do{
		vector<pair<int,int>> V = generamosVecindario();
		int size = V.size();
		encontrado = false;
		double new_f = 0;

		for(int i=0; i<size && !encontrado && contador>0; i++){
			// Calcular nuevo objetivo
			contador--;
            double ant_obj = obj;
			new_f = recalcularF(V[i]);
            encontrado = new_f < ant_obj;
		}

    }while(encontrado);

	t1 = clock();

	time = ( double(t1-t0)/CLOCKS_PER_SEC );
}

double Local::recalcularF(const pair<int,int> &cambio){
	int cluster_nuevo = cambio.second;
	int cluster_anterior = S[cambio.first];
	int instancia = cambio.first;
    
    copia cp;

    cp.U = this->U;
    cp.C = this->C;
    cp.S = this->S;
    cp.c_ic = this->c_ic;
    cp.obj = this->obj;
    cp.desviacion = this->desviacion;
    cp.inf_total = this->inf_total;
    cp.n_c = this->n_c;

    // Recalcula C
    for(int i=0; i<C[cluster_anterior].size(); i++){
        if( C[cluster_anterior][i] == instancia)
            C[cluster_anterior].erase(C[cluster_anterior].begin()+i);
    }
    C[cluster_nuevo].push_back(instancia);
    S[instancia] = cluster_nuevo;
    
    n_c[cluster_anterior]--;
    n_c[cluster_nuevo]++;

    // Recalcula centroides
    calcularCentroide(cluster_anterior);
    calcularCentroide(cluster_nuevo);

    // Calcula la nueva funcion obj
    funcionObjetivo();

    double out = obj;

    if(obj>cp.obj){
        this->U = cp.U;
        this->C = cp.C;
        this->S = cp.S;
        this->c_ic = cp.c_ic;
        this->obj = cp.obj;
        this->desviacion = cp.desviacion;
        this->inf_total = cp.inf_total;
        this->n_c = cp.n_c;
    }

    return out;
}


vector<pair<int,int>> Local::generamosVecindario(){
	vector<pair<int,int>> out(0);
	
	for(int i=0; i<n; i++){
		if(n_c[S[i]]>1){
			for(int j=0; j<k; j++){
				if(S[i]!=j)
					out.push_back(pair<int,int>(i, j));
			}
		}
	}

	random_shuffle(out.begin(), out.end());

	return out;
}