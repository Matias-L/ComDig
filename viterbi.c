/*
Comunicaciones digitales
Trabajo práctico número 2. 
UNC-FCEFyN

Profesora: Graciela Corral briones
Alumnos:
		Armando, Gaspar
		Cazajous, Miguel
		Ceballos, Matías
		D’Andrea, David
		Mantay, Rodrigo
		Tapia, Rodrigo

Consigna n°2: Simulador BPSK con codificador convolucional, ruido AWGN y decodificador de Viterbi
Junio 2018
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define ka 1000		//Numero de simbolos de entrada

int productopunto(int[],int[]);
void salida_encoder(int, int, int, int[]);
int compara(int , int );
void estado (int , int[]);
int proximoEstado (int , int);
void traceback(int*, int[]);


/*
El programa se divide en 3 grandes bloques: Codificador, canal y decodificador.
Para simplicidad de lectura, en cada bloque se declaran las variables que usarán
En el encoder convolucional ingresamos los simbolos a ser codificados mediante el vector "b", y mostramos su secuencia de salida.
En el bloque canal levantamos un archivo de ruidos gaussianos generados en Octave, y lo cargamos en un vector. Dicho vector se suma
al vector de salida del convoluciona, y el resultado es un vector que ingresará al decodificador.
En el decodificador recibimos el vector con ruido gaussiano aditivo y se decodifica mediante el algoritmo de Viterbi.
*/
int main(int argc, char const *argv[])
{


	// Bloque encoder convolucional

	//int ka=7;						//Numero de simbolos
	int b[ka]={1,-1,-1,1,1,-1,1,1,1,-1,1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,1,-1,-1,1,1,1,1,-1,1,1,1,1,-1,1,-1,1,-1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,1,1,1,-1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,1,1,-1,1,1,1,1,1,-1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,1,-1,-1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,-1,-1,1,1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,-1,1,1,1,1,1,1,1,-1,-1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,1,1,1,-1,-1,1,1,1,1,1,1,-1,-1,1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,-1,1,-1,1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1,-1,1,-1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,-1,1,1,1,1,-1,1,-1,-1,1,-1,1,-1,-1,1,-1,-1,1,1,1,-1,-1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,1,1,1,1,1,-1,1,-1,1,1,1,-1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,1,1,1,-1,1,1,1,1,-1,-1,-1,1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,1,1,1,-1,-1,-1,-1,1,-1,-1,-1,1,-1,-1,1,-1,1,1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,1,1,-1,-1,1,1,1,1,1,1,-1,1,-1,-1,-1,-1,-1,1,1,1,1,-1,1,-1,1,1,-1,1,-1,1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,1,1,-1,1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,-1,1,1,1,1,-1,-1,1,1,1,-1,1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,1,-1,-1,1,1,-1,1,-1,1,-1,1,1,-1,1,-1,1,1,1,1,-1,-1,-1,-1,-1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,-1,-1,-1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,-1,1,1,-1,-1,1,1,-1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,-1,1,1,-1,-1,-1,-1,1,-1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,-1,1,1,-1,-1,-1,1,-1,-1,-1,-1,1,-1,-1,-1,1,1,-1,-1,-1,-1,1,1,1,1,1,-1,1,-1,-1,-1,1,1,-1,1,1,-1,1,-1,1,-1,1,-1,-1,-1,-1,1,1,-1,-1,-1,-1,-1,1,-1,1,1,1,-1,1,-1,1,1,1,1,-1,1,-1,1,1,-1,-1,1,1,1,1,-1,1,1,1,-1,1,1,1,1,1,-1,-1,1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,-1,1,1,-1,-1,1,-1,1,-1,1,1,-1,1,-1,-1,-1,-1,-1,-1,1,-1,1,1,-1
};	//vector de símbolos de entrada
	int salidas[2*ka];				//Vector de salida
	int bjmenos1=1;				
	int bjmenos2=1;
	int bj;
	int x2jmenos1;
	int x2j;
	int m=0;	//indice del vector de salidas
	float canal[2*ka];

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


	//Bloque del canal

	FILE *archivo;
	char buffer[50];
	int q=0;
	float var=0;
	float y[2*ka];		//Vector a decodificar

	printf("\n");
	printf("Ruido:\n");
	archivo = fopen("ruido.txt","r");		//Levanto el archivo de ruidos
	while (!feof(archivo)) {
		fgets(buffer, 50 ,archivo);
		var=atof(buffer);
		canal[q]=var;
		printf("%f \n",canal[q] );
		q++;
		memset(buffer,0,50);
	}
	fclose(archivo);

	printf("\n");
	printf("Vector a decodificar ya con ruido: \n");

	//Sumo el ruido al vector de salida del codificador
	for(int ye=0; ye<2*ka; ye++){
		y[ye]=canal[ye]+salidas[ye];
		printf("%f \n", y[ye]);
	}
	printf("\n");

	//Fin canal
	//******************

	//Bloque decodificador


	int k=5;
	int estados=4;
	int MC[estados][k+3];
	int MEstadoAnterior[estados][k+3];
	int E[2];
	int S[2];
	

	for(int i=0;i<estados;i++){
		for(int j =0; j<k+3;j++){
		    MC[i][j]=-9999;
		    MEstadoAnterior[i][j]= -9999;
		}
			
	}
	MC[0][0] = 0;

	
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

	//COMENTO TODO ESTO POR QUE SE VA A VER HORRIBLE
	/*
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
	*/
	//Fin bloque decodificador
	//***************

	//Guardo el resultado del decodificador en un archivo
	archivo = fopen("decodificados.txt","w");
	for (int i = 0; i < ka; i++) {
		fprintf(archivo, "%d\n", B[i]);
	}
	fclose(archivo);

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

