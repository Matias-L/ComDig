#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4
#define M 7
#define NULO -999
#define INF 9999

double pot(double n){
	return n*n;
}

double salida_canal(int bj, int bj1, int bj2){

	double S = (0.3*bj) + bj1 +(0.4*bj2);
	return S;
}

int* estado (int e){
	int* ptr;
	ptr = malloc(2);
	switch(e){
		case 0:
			ptr[0]=1;
			ptr[1]=1;
			break;

		case 1:
			ptr[0]=-1;
			ptr[1]=1;
			break;

		case 2:
			ptr[0]=1;
			ptr[1]=-1;
			break;

		case 3:
			ptr[0]=-1;
			ptr[1]=-1;
			break;
		}
		return ptr;
}

int proximoEstado (int Eactual, int simbolo){
	if(simbolo == 1){
		switch(Eactual){
			case 0: return 0;
			case 1: return 2;
			case 2: return 0;
			case 3: return 2;
		}
	}
	if(simbolo == -1){
		switch(Eactual){
			case 0: return 1;
			case 1: return 3;
			case 2: return 1;
			case 3: return 3;
		}
	}
	return -1;
}


int main(){


	int X[M-1]= {1, -1, -1, -1, 1, 1};
	double Y[M-1];

	int b1=1;
	int b2=1;
	for(int i=0;i<M-1;i++){
		Y[i]=salida_canal(X[i],b1,b2);
		b2=b1;
		b1=X[i];
		printf("%4.1f\t", Y[i]);
	}









	//DETECCION
	int state_matrix[N][M];
	double cost_matrix[N][M];
	double path_metric[N][N];


	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			state_matrix[i][j]= NULO;
			cost_matrix[i][j]= INF;
		}
		for(int j=0;j<N;j++)
			path_metric[i][j]= INF;
	}

	cost_matrix[0][0]=0;	//Estado inicial del Trellis

	for(int j=0;j<M;j++){

		//Calculo de Costo en cada Estado
		if(j>0){	//En la primer iteracion no hay costo
			for(int e=0;e<N;e++){

				double menorCosto = INF;
				for(int prevE=0;prevE<N;prevE++){
					double costoRama;
					if(path_metric[prevE][e]!=INF){
						costoRama=path_metric[prevE][e];
						double camino = cost_matrix[prevE][j-1] + costoRama;
						if(camino < menorCosto){
							menorCosto=camino;
							cost_matrix[e][j]=menorCosto;
							state_matrix[e][j]=prevE;
						}

					}
				}
			}
		}

		//Calculo de ramas de cada estado
		for(int e =0;e<N;e++){
			if(cost_matrix[e][j]!=INF){

				int *E = estado(e);
				int nextE;
				double costoDeRama;

				//Llega un 1
				nextE = proximoEstado(e,1);
				costoDeRama = pot(Y[j] - salida_canal(1,E[0],E[1] ));
				path_metric[e][nextE] = costoDeRama;

				//Llega un -1
				nextE = proximoEstado(e,-1);
				costoDeRama = pot(Y[j] - salida_canal(-1,E[0],E[1] ));
				path_metric[e][nextE] = costoDeRama;
			}
		}
	}

printf("\nCOSTOS\n\n");

	for(int i = 3; i>=0;i--){
	    for(int j=0;j<M;j++){
	        printf("|\t%4.1f\t",cost_matrix[i][j]);
	    }
	    printf("\n");
	}

	printf("\nEstado Anterior\n\n");

	for(int i = 3; i>=0;i--){
	    for(int j=0;j<M;j++){
	        printf("|\t%d\t",state_matrix[i][j]);
	    }
	    printf("\n");
	}

}
