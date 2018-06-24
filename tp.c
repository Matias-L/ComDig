#include <stdio.h>
#include <string.h>

#define M 5	//Ventana de truncamiento
#define N 4	//Numero de estados
#define K 10	//Numero de simbolos de entrada

struct Estado
{	int id;
	int ePos;		//Estado al que pasa ante entrada positiva
	float salPos;	//Salida ante entrada positiva
	int eNeg;		//Estado ante entrada -1
	float salNeg;	//Salida ante entrada -a
	
};

struct  Estado e0;
struct  Estado e1;
struct  Estado e2;
struct  Estado e3;
struct  Estado e[N];	//vector que almacena los estados posibles

float simbolosEntrada[K]={1,1,1,1,-1,-1,-1,1,-1,1};
int x[K];	//Vector de salida
int state_matrix[M][N];
float cost_matrix [M][N];


void inicializaEstados (){

	e0.id=0;
	e0.ePos=0;
	e0.salPos=1.5;
	e0.eNeg=1;
	e0.salNeg=0.9;
	e[0]=e0;

	e1.id=1;
	e1.ePos=2;
	e1.salPos=-0.5;
	e1.eNeg=3;
	e1.salNeg=-1.1;
	e[1]=e1;

	e2.id=2;
	e2.ePos=0;
	e2.salPos=1.1;
	e2.eNeg=1;
	e2.salNeg=0.5;
	e[2]=e2;

	e3.id=3;
	e3.ePos=2;
	e3.salPos=-0.9;
	e3.eNeg=3;
	e3.salNeg=-1.5;
	e[3]=e3;

}

void imprimeMatricez(){
printf("\n");
printf("state matrix :\n");
printf("\n");

	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			printf("%d ", state_matrix[j][i] );
		}
		printf("\n");
	}
printf("____________________\n");

printf("cost matrix :\n");
printf("\n");

	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			printf("%f ", cost_matrix[j][i] );
		}
		printf("\n");
	}
printf("____________________\n");
}

float metricaRama(float salidaDelDestino, float simbolo){
	return simbolo-salidaDelDestino;
}

int traceback(){

	//Primero debe buscar la mayor métrica de la ultima columna. 
	int max=0;
	for (int i=0; i<=N; i++){
		if (cost_matrix[M][i]>cost_matrix[M][max]){
			max=i;
		}
	}

	//Luego, empiezo a retroceder buscando los estados.
	int estado=max;
	for(int j=M; j<0; j--){
		estado=state_matrix[j][estado];
	}

	//Finalmente, desplazo toda la matriz un lugar a la izquierda

	for(int l=0; l<M; l++){
		for(int h=0; h<N; h++){
			state_matrix[l][h]=state_matrix[l+1][h];
			cost_matrix[l][h]=cost_matrix[l+1][h];
		}
	}

	//limpio la ultima columna

	for (int r=0; r<N; r++){
						state_matrix[M][r]=-1;
				cost_matrix[M][r]=-99999;
	}




	return estado;

}



int main(int argc, char const *argv[])
{




	//Limpio vector de secuencia detectada
	for (int l=0; l<K; l++){
		x[l]=0;
	}
	inicializaEstados();
	//Lleno la matriz de estados con -1 
	for(int g=0; g<M; g++){
		for(int h=0; h<N; h++){
			state_matrix[g][h]=-1;
			cost_matrix[g][h]=-1;
		}
	}



	//Regimen transitorio
	int epoch=0;		//Indice de profundidad
	int estado=0;
	float branchMetric=0;

	state_matrix[epoch][estado]=0;
	cost_matrix[epoch][estado]=0;
	state_matrix[epoch][estado]=0;

	//state_matrix[epoch+1][e[estado].ePos]=e[estado].ePos;
	//state_matrix[epoch+1][e[estado].eNeg]=e[estado].eNeg;
	state_matrix[epoch+1][e[estado].ePos]=estado;
	state_matrix[epoch+1][e[estado].eNeg]=estado;
	cost_matrix[epoch+1][e[estado].ePos]=metricaRama(e[estado].salPos, simbolosEntrada[epoch])+cost_matrix[epoch][estado];
	cost_matrix[epoch+1][e[estado].eNeg]=metricaRama(e[estado].salNeg, simbolosEntrada[epoch])+cost_matrix[epoch][estado];

	epoch=1;
	estado=0;
	//state_matrix[epoch+1][e[estado].ePos]=e[estado].ePos;
	//state_matrix[epoch+1][e[estado].eNeg]=e[estado].eNeg;
	state_matrix[epoch+1][e[estado].ePos]=estado;
	state_matrix[epoch+1][e[estado].eNeg]=estado;
	cost_matrix[epoch+1][e[estado].ePos]=metricaRama(e[estado].salPos, simbolosEntrada[epoch])+cost_matrix[epoch][estado];
	cost_matrix[epoch+1][e[estado].eNeg]=metricaRama(e[estado].salNeg, simbolosEntrada[epoch])+cost_matrix[epoch][estado];

	estado=1;
	//state_matrix[epoch+1][e[estado].ePos]=e[estado].ePos;
	//state_matrix[epoch+1][e[estado].eNeg]=e[estado].eNeg;
	state_matrix[epoch+1][e[estado].ePos]=estado;
	state_matrix[epoch+1][e[estado].eNeg]=estado;
	cost_matrix[epoch+1][e[estado].ePos]=metricaRama(e[estado].salPos, simbolosEntrada[epoch])+cost_matrix[epoch][estado];
	cost_matrix[epoch+1][e[estado].eNeg]=metricaRama(e[estado].salNeg, simbolosEntrada[epoch])+cost_matrix[epoch][estado];

	epoch=2;






	//Regimen estacionario previo llenado de la ventana
	for(int o=epoch;o<M;o++){
		for(int estado=0; estado<N; estado++){
			//Viendo la salida ante entrada positiva
			if(state_matrix[o+1][e[estado].ePos]==-1){
				state_matrix[o+1][e[estado].ePos]=e[estado].ePos;
				cost_matrix[o+1][e[estado].ePos]=metricaRama(e[estado].salPos, simbolosEntrada[o])+cost_matrix[o][estado];
			}
			else{ //Otro estado escribio en la celda, y hay que quedarse con el maximo
				//Si el nuevo valor es mayor que el anterior, sobreescribe.
				//Tambien actualiza la matriz de estados
				if( (cost_matrix[o][estado]+metricaRama(e[estado].salPos, simbolosEntrada[o])) > (cost_matrix[o+1][e[estado].ePos]) )
				cost_matrix[o+1][e[estado].ePos]=cost_matrix[o][estado]+metricaRama(e[estado].ePos, simbolosEntrada[o]);
				state_matrix[o+1][e[estado].ePos]=estado;
			}
			//Viendo la salida ante entrada negativa
			if(state_matrix[o+1][e[estado].eNeg]==-1){
			state_matrix[o+1][e[estado].eNeg]=e[estado].eNeg;
			cost_matrix[o+1][e[estado].eNeg]=metricaRama(e[estado].salNeg, simbolosEntrada[o])+cost_matrix[o][estado];
			}
				else{ //Otro estado escribio en la celda, y hay que quedarse con el maximo
				//Si el nuevo valor es mayor que el anterior, sobreescribe.
				//Tambien actualiza la matriz de estados
				if( (cost_matrix[o][estado]+metricaRama(e[estado].salNeg, simbolosEntrada[o])) > (cost_matrix[o+1][e[estado].eNeg]) )
				cost_matrix[o+1][e[estado].eNeg]=cost_matrix[o][estado]+metricaRama(e[estado].eNeg, simbolosEntrada[o]);
				state_matrix[o+1][e[estado].eNeg]=estado;
			}



		}
	}
	//En este punto la ventana se llena completamente. Ejecuto hasta que no hayan mas simbolos de entrada

printf("X[]: ");
	while (epoch<=K){
		x[epoch]=traceback();
		printf("%d ", x[epoch]);


		//Ver si no se puede evitar esta duplicacion de codigo

			//Viendo la salida ante entrada positiva
			if(state_matrix[M][e[estado].ePos]==-1){
				state_matrix[M][e[estado].ePos]=e[estado].ePos;
				cost_matrix[M][e[estado].ePos]=metricaRama(e[estado].salPos, simbolosEntrada[M-1])+cost_matrix[M-1][estado];
			}
			else{ //Otro estado escribio en la celda, y hay que quedarse con el maximo
				//Si el nuevo valor es mayor que el anterior, sobreescribe.
				//Tambien actualiza la matriz de estados
				if( (cost_matrix[M-1][estado]+metricaRama(e[estado].salPos, simbolosEntrada[M-1])) > (cost_matrix[M][e[estado].ePos]) )
				cost_matrix[M][e[estado].ePos]=cost_matrix[M-1][estado]+metricaRama(e[estado].ePos, simbolosEntrada[M-1]);
				state_matrix[M][e[estado].ePos]=estado;
			}
			//Viendo la salida ante entrada negativa
			if(state_matrix[M][e[estado].eNeg]==-1){
			state_matrix[M][e[estado].eNeg]=e[estado].eNeg;
			cost_matrix[M][e[estado].eNeg]=metricaRama(e[estado].salNeg, simbolosEntrada[M-1])+cost_matrix[M-1][estado];
			}
				else{ //Otro estado escribio en la celda, y hay que quedarse con el maximo
				//Si el nuevo valor es mayor que el anterior, sobreescribe.
				//Tambien actualiza la matriz de estados
				if( (cost_matrix[M-1][estado]+metricaRama(e[estado].salNeg, simbolosEntrada[M-1])) > (cost_matrix[M][e[estado].eNeg]) )
				cost_matrix[M][e[estado].eNeg]=cost_matrix[M-1][estado]+metricaRama(e[estado].eNeg, simbolosEntrada[M-1]);
				state_matrix[M][e[estado].eNeg]=estado;
			}




		//--------fin duplicacion







		epoch++;
	}


imprimeMatricez();

	return 0;
}