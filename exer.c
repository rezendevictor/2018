#include <stdio.h>
#include <stdlib.h>

void decom(int a){
  int *number = malloc ((a+1) * sizeof (int) );
  int count = 0;
  int d=0;
  number[0] = a;
  while(number[a-1]!=1){
    while(number[d]>=number[d+1]){
      number[d]--;
      number[d+1]++;
      if(number[d+1]>=2) aux(number,a,d);
      if((number[d]-1)<(number[d+1]+1)){
        break;
      }

    }
    d += 2;

  }
  printf("%d %d %d %d %d \n",number[0],number[1],number[2],number[3],number[4] );




  /*
  if(number[aux+1]<number[aux]){
  number[aux] = number[aux] -1;
  number[aux+1]++;

}else{
aux++;
}
for( d = 0; d < a ;d++) {
if(number[d]!=0)
count++;
}
for(d = 0; d < (count-1); d++){
printf("%d + ",number[d] );
}
printf("%d\n", number[d]);
count = 0;

*/





}
int aux(int *vetor,int tamanho,int entrada){
  int *vec = malloc ((tamanho+1) * sizeof (int) );
  int a = 0;
  for(a = 0; a < tamanho;a++) vec[a] = &vetor[a];
  int imprime = 0;
  while(vetor[entrada] != 1){
    vec[entrada]--;
    for(a = (entrada+1);a < tamanho; a++ ) vec[a]++;
    for(imprime = 0; imprime<(tamanho-1);imprime++) printf("%d + ", vetor[imprime]);
    printf("%d \n ", vec[imprime]);
  }
}







int main() {
  int a;
  printf("Digite um numero inteiro: ");
  scanf("%d",&a );
  decom(a);

  return 0;
}
