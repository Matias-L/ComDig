#include <stdio.h>

int productopunto(int[],int[]);
void salida_encoder(int, int, int, int[]);
int compara(int , int );
void estado (int , int[]);
int proximoEstado (int , int);
void traceback(int*, int[]);



int main(int argc, char const *argv[])
{


	//Encoder convolucional

	int ka=7;					//Numero de simbolos
	int b[7]={1,1,1,1,-1,1,1};	//vector de símbolos de entrada
	int salidas[2*ka];			//Vector de salida
	int bjmenos1=1;				
	int bjmenos2=1;
	int bj;
	int x2jmenos1;
	int x2j;
	int m=0;	//indice del vector de salidas

	printf("Simbolos de entrada:\n");
	
	for(int i=0; i<ka;i++){
		bj=b[i];
		x2jmenos1=bj*bjmenos2;
		x2j=bj*bjmenos1*bjmenos2;
		bjmenos2=bjmenos1;
		bjmenos1=bj;
		salidas[m]=x2jmenos1;
		salidas[m+1]=x2j;
		x2jmenos1=0;
		x2j=0;
		printf("%d ",b[i] );
		m+=2;
		}

	printf("\n");
	printf("Salida del codificador:\n");
	for (m = 0; m < 2*ka; m++)
	{
		printf("%d ", salidas[m]);
	}
	printf("\n");




	//Fin codificador convolucional
	//***********************

	//Aca hay que afectar por ruido AWGN el vector salidas[]

	//Fin AWGN
	//******************




	int k=5;
	int estados=4;
	int MC[estados][k+3];
	int MEstadoAnterior[estados][k+3];
	for(int i=0;i<estados;i++){
		for(int j =0; j<k+3;j++){
		    MC[i][j]=-9999;
		    MEstadoAnterior[i][j]= -9999;
		}
			
	}
	MC[0][0] = 0;

	int y[14];

	printf("Vamos a decodificar: \n");
	for (int t=0; t<14; t++){
		y[t]=salidas[t];
		printf("%d ",y[t]);
	}
	//int y[14] = {1,3,-2,1,4,-1,5,5,-3,-3,1,-6,2,-4};
	int E[2];
	int S[2];
	


	int MEjes[estados][estados];
	for(int i=0;i<estados;i++){
		for(int j =0; j<estados;j++)
			MEjes[i][j]=-999;
	}
	
	for(int j=0;j<k+3;j++){
		for(int e = 0; e<estados; e++){
			if(j!=0){
				//CALCULAR COSTO
				int costo_maximo = -9999;
				
				for(int n = 0; n<estados; n++){
				    if(MEjes[n][e]>-999){
				        int aux = MEjes[n][e] + MC[n][j-1];
				        if(aux>costo_maximo){
				            costo_maximo=aux;
				            MEstadoAnterior[e][j]=n;
				        }
				    }
				    
				}
				MC[e][j]=costo_maximo;
			}
			
			

		}
		for(int i=0;i<estados;i++){
		for(int j =0; j<estados;j++)
		MEjes[i][j]=-999;
		//int Y[2];
		//Y[0]=y[(2*j)-1]
		for(int e=0; e<estados;e++){
			//Calcular metricas
			estado(e,E);
			int nextE;
			int Y[2];

			Y[0]=y[2*j];
			Y[1]=y[(2*j)+1];
			if(MC[e][j] >-9000){
				//Si llega un 1
				nextE = proximoEstado(e,1);
				salida_encoder(1,E[0],E[1], S);
				MEjes[e][nextE]= productopunto(S,Y);
				//Si llega un -1
				if(j<k){	//Las ultimas iteraciones llegan 1 y 1
					nextE = proximoEstado(e,-1);
					
					salida_encoder(-1,E[0],E[1], S);
					MEjes[e][nextE]= productopunto(S,Y);
				}
			}


			}
		}

	}

	int B[7];
	//traceback(MEstadoAnterior, B);

	int ultimo_estado;
	int proximo_estado;
	for(int i=0;i<estados;i++){
		if(MEstadoAnterior[i][7]>-999){
			ultimo_estado=i;
			proximo_estado=MEstadoAnterior[i][7];
		}
	}
	
	estado(ultimo_estado,E);

	B[6]=E[0];

	for(int j=6;j>0;j--){
		estado(proximo_estado,E);
		B[j-1]=E[0];
		proximo_estado=MEstadoAnterior[proximo_estado][j];
	}

	
	
	/*
	for(int i = 0; i<4;i++){
	    for(int j=0;j<4;j++){
	        printf("|       %d\t",MEjes[i][j]);
	    }
	    printf("\n");
	}*/
	
	printf("\nCOSTOS\n\n");
	
	for(int i = 3; i>=0;i--){
	    for(int j=0;j<k+3;j++){
	        printf("|\t%d\t",MC[i][j]);
	    }
	    printf("\n");
	}

	printf("\nEstado Anterior\n\n");
	
	for(int i = 3; i>=0;i--){
	    for(int j=0;j<k+3;j++){
	        printf("|\t%d\t",MEstadoAnterior[i][j]);
	    }
	    printf("\n");
	}

		printf("\nSimbolos de Entrada\n\n");


	for(int i=0; i<7;i++){
		printf("%d  ",B[i]);
	}
		    printf("\n");



	//estado(estado_actual, E);
	//salida_encoder(1,E[0],E[1], S);
	//int camino1= productopunto(S,y);
	//printf("%d\n",camino1 );

	//salida_encoder(-1,E[0],E[1], S);
	//int camino2= productopunto(S,y);
	//printf("%d\n",camino2 );

	//MC[0][j]=camino1;
	//MC[1][j]=camino2;

	//int maximo = compara(camino1,camino2);
	//printf("%d\n",maximo );
	return 0;

}

void salida_encoder(int bj, int bj1, int bj2, int S[]){
	int* ptr = S;
	int x1 = bj*bj2;
	int x2 = bj*bj1*bj2;

	
	ptr[0]=x1;
	ptr[1]=x2;
}

void estado (int e, int E[]){
	int* ptr = E;
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
}

int proximoEstado (int actual, int simbolo){
	if(simbolo == 1){
		switch(actual){
			case 0: return 0;
			case 1: return 2;
			case 2: return 0;
			case 3: return 2;
		}
	}
	if(simbolo == -1){
		switch(actual){
			case 0: return 1;
			case 1: return 3;
			case 2: return 1;
			case 3: return 3;
		}
	}
}

int productopunto(int x[], int y[])
{
	int total=0;
	for(int i=0;i<2;i++)
	{
		total+=x[i]*y[i];
	}

	return total;
}

/*
void traceback(int m[][], int v[]){
	int* ptr=v;
	int* MEstadoAnterior= m;

	int ultimo_estado;
	int proximo_estado;
	for(int i=0;i<estados;i++){
		if(MEstadoAnterior[i][7]>-999){
			ultimo_estado=i;
			proximo_estado=MEstadoAnterior[i][7];
		}
	}
	int E[2];
	estado(ultimo_estado,E);

	ptr[6]=E[0];

	for(int j=6;j>0;j--){
		estado(proximo_estado,E);
		ptr[j-1]=E[0];
		proximo_estado=MEstadoAnterior[proximo_estado,j];
	}
*/
