
#include <stdio.h>
#include <stdlib.h>
#define TAM 10
#define PREC 100

//void brute_force_beta (double [],int*);
//void print(int[]);

void *memset(void *str, int c, size_t n);

void brute_force_beta(double q[], int *detectado){
  int aux,aux2;
    int sim[2] = {1, -1};
    for ( int j = 0; j < TAM; j++) {
      aux = abs(q[j]- sim[0]);
      aux2= abs (q[j] - sim[1]);
      if (aux<aux2) {
        detectado[j] = sim[0];
        }
        else{
        detectado[j] = sim[1];
      }
    }
  return ;
}

void print (int a[]){
  for (int i = 0; i < TAM; i++) {
    printf("%d\n", a[i] );
  }
}


int main(int argc, char const *argv[]) {

  FILE *ent;
  FILE *ruido;

  //int N = 5;
  //double b[TAM] = {-0.958377, 0.087669, 0.275473, -0.329830, -0.307965} ;
  double simbols[TAM];
  int b;
  double r;
  char b1[PREC];
  char b2[PREC];
  int i;
  int D[TAM];

  ent=fopen("rand.txt","r");
  ruido=fopen("ruido.txt","r");

  while (!feof(ent)) {
    fgets(b1, PREC, ent);
    fgets(b2, PREC, ruido);
    sscanf(b1, "%d", &b);
    sscanf(b2, "%lf", &r);
    memset(b1,0,TAM);
    memset(b2,0,TAM);
    simbols[i]=b+r;
    printf("simbolo: %d ruido: %lf total: %lf\n", b, r, simbols[i]);
    i++;
  }

  brute_force_beta(simbols,&D[0]);
  print(D);


    return 0;
}
