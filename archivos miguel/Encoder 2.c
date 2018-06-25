#include <stdio.h>
#include <stdlib.h>

#define k 10

void *memset(void *str, int c, size_t n);

int main(int argc, char const *argv[])
{
	FILE *archivo;
	int b[k];
	double salidas[k];
	int bjmenos1=1;
	int bjmenos2=1;
	int bj;
	int i;
	char buffer[50];
	int var;
	double aux;

	i=0;
	archivo = fopen("rand.txt","r");
	while (!feof(archivo)) {
		fgets(buffer, 50 ,archivo);
		sscanf(buffer, "%d", &var);
		memset(buffer,0,50);
		b[i]=var;
		printf("var: \n%d\n", b[i]);
		i++;
	}
	fclose(archivo);
	printf("Estados:\n");
	for(i=0; i<k;i++){
		bj=b[i];
		aux=0.3*bj+bjmenos1+0.2*bjmenos2;
		bjmenos2=bjmenos1;
		bjmenos1=bj;
		salidas[i]=aux;
		aux=0;
		printf(" %f;", salidas[i]);
	}

	archivo = fopen("salidak.txt","w");
	for (i = 0; i < k; i++) {
		fprintf(archivo, "%f\n", salidas[i]);
	}
	fclose(archivo);

	return 0;
}
