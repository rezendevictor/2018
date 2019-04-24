#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INF 0xffffffff


/*int fatorial(int[] fator){
  int prox[INF] = 0;


}*/


int main() {
  //variaveis
  int a;
  int aux;
  int tamanho_vetor=0;
  //pegando o numero
  printf("Digite um numero inteiro: ");
  scanf("%d", &a );
  aux = a - 1;

  //PArte da teoria tirada do site https://jandersongomes.com/index.php/2017/08/16/calcular-fatorial-de-numeros-maiores-do-que-50-000-em-c/
  int tmp = 0;
  tmp = round((log(2*3.141592653)+log(a)+2*a*(log(a) - 1))/(2 * log(10))) + 1;
  int *numero = (int *)malloc( tmp * sizeof(int));
  tmp++;
  //numero[tmp-1] = -1;
  //printf(" TMP =%d\n", tmp);
  //printf("%lu\n",tmp* sizeof(int  ));

  //funcao para dividir no vetor
  int resto = a%10;

  int fica = a/10;

  do{
    numero[tamanho_vetor] = resto;
    resto = fica%10;
    fica = fica/10;
    tamanho_vetor++;
  }while(fica !=0);
    numero[tamanho_vetor] = resto;




//funcao fatorial
    while(aux > 0){
      int aux_interno;
      int j = 0;
      int sobra = 0;
      for(aux_interno = 0; aux_interno<tmp ; aux_interno++){
          int digit = (numero[j] * aux)+ sobra;
          numero[j] = digit%10 ;
          sobra  = digit/10;
          j++;

          //printf(" numero :%d \n sobra %d\n digit :%d \n", numero[j],sobra, digit );
      }
      aux--;
    }


  printf("Resultado: " );
  int flag = 0;
  while(tmp >= 0){
  if(numero[tmp] > 0){
    flag = 1;
  }
  if(flag == 1){
  printf("%d", numero[tmp]);
  }
  tmp-- ;
  }
  printf("\n");

  //printf(" Teste =%d\n", teste);

  return 0;

}
