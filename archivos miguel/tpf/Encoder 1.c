#include <stdio.h>
#include <stdlib.h>

#define k 10

void *memset(void *str, int c, size_t n);

int main(int argc, char const *argv[])
{
	FILE *archivo;
	int b[k];
	int salidas[2*k];
	int bjmenos1=1;
	int bjmenos2=1;
	int bj;
	int x2jmenos1;
	int x2j;
	int i;
	char buffer[50];
	int var;

	i=0;
	archivo = fopen("rand.txt","r");
	while (!feof(archivo)) {
		fgets(buffer, 50 ,archivo);
		sscanf(buffer, "%d", &var);
		memset(buffer,0,50);
		b[i]=var;
		printf("var: \n%d\n", var);
		i++;
	}
	fclose(archivo);
	printf("Estados:\n");
	for(i=0; i<k;i++){
		bj=b[i];
		x2jmenos1=bj*bjmenos2;
		x2j=bj*bjmenos1*bjmenos2;
		bjmenos2=bjmenos1;
		bjmenos1=bj;
		salidas[2*i]=x2jmenos1;
		salidas[2*i+1]=x2j;
		x2jmenos1=0;
		x2j=0;

	printf("[%d, %d]", bjmenos1, bjmenos2);
	}
	printf("\n");
	printf("Salidas:\n");
	for (i = 0; i < k; i++)
	{
		printf("(%d %d)", salidas[2*i], salidas[2*i+1]);
	}
	printf("\n");

	archivo = fopen("salida2k.txt","w");
	for (i = 0; i < 2*k; i++) {
		fprintf(archivo, "%d\n", salidas[i]);
	}
	fclose(archivo);

	return 0;
}
