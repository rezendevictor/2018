/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Victor Franco Rezende
Matricula:
Descricao do programa: Programa visa resolver o problema da mochila com uma
aproximacao de estrategia gulosa
Data: 31/08/2018
************************************************/
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>


//definindo estrutura para trabalhar
typedef struct{
  int peso; //Recebe o peso de cada objeto
  int valor;  //Recebe o valor de cada objeto
  int posicao; //Recebe a posicao na qual cada objeto esta sendo enserido no programa

} Objeto;

//funcao gulosa
Objeto * guloso(Objeto *estoque,int Capacidade,int N_itens){
  int contador; // variavel auxiliar
  int peso = 0; // Variavel que controla o peso na mochila
  for (contador = 0; contador < N_itens; contador++) {

    if((peso + estoque[contador].peso) > Capacidade){
      estoque[contador].valor = 0;
      estoque[contador].peso = 0;

      /* Caso o peso do objeto sobrepasse a soma, seu peso sera
      definindo como 0, assim nao sera imprimido depois.
      */
    }else{
      peso += estoque[contador].peso;

      /*
      caso o peso do objeto caiba na capacidade da mochila, o peso do item
      e adicionado ao a varivel peso, para que diminua a capacidade.
      */
    }
    //if(peso >= Capacidade ) break;

    /* caso a mochila atinja sua capacidade maxima, o loop sera parado,
    para nao desperdicar iteracoes*/

  }

  return estoque;

}//END Guloso

//funcao de ordenacao
Objeto * ordenacao(Objeto *estoque,int N_itens){

  int i; //varivel auxiliar
  Objeto troca; // varivel para realizar as trocas de posicao

  //funcao de ordenacao, nao a  mais eficiente porem vai servir

  for(i =0; i<(N_itens-1);i++){

    if(estoque[i].peso > estoque[i+1].peso ){

      troca = estoque[i+1];
      estoque[i] = estoque[i+1];
      estoque[i+1] = troca;

    }

  }


  return estoque;
}//END ordenacao


//Corpo principal do programa

int main() {
  while (1) {
    //Definindo as variveis

    int Capacidade; // Capacidade da mochila
    int N_itens; //numero de itens a serem cadastrados
    int contador;
    struct rusage usage;
    struct timeval start, end;

    //Abrindo arquivo para escrever
    FILE *mochila;
    mochila = fopen("mochila.txt","w");
    if(mochila == NULL){
      printf("Arquivo inexistente!\n");
    }

    //Recebendo os valores das variveis
    scanf("%d",&Capacidade );
    if(Capacidade == 0) break;
    scanf("%d",&N_itens);
    printf("quantidade de itens: %d \n", N_itens );


    //Vetor para receber os itens
    Objeto *estoque = malloc (N_itens* 3 * sizeof (int)  );

    //Recebendo os objetos
    for (contador = 0; contador < N_itens; contador++) {
      estoque[contador].posicao = contador;
      scanf("%d %d",&estoque[contador].peso,&estoque[contador].valor);
    }

    //Tratando o problema
    estoque = ordenacao(estoque,N_itens);
    estoque = guloso(estoque,Capacidade,N_itens);

    int peso_total = 0,valor_total=0;
    for(contador = 0; contador < N_itens;contador++){
      if(estoque[contador].valor != 0 ){
        fprintf(mochila, "%d %d %d\n",estoque[contador].posicao,estoque[contador].peso,estoque[contador].valor );
        printf ("%d %d %d\n",estoque[contador].posicao,estoque[contador].peso,estoque[contador].valor );
        peso_total+= estoque[contador].peso;
        valor_total += estoque[contador].valor;

      }


    }
    fprintf(mochila, "Peso Total: %d Valor Total: %d\n",peso_total,valor_total );
    printf("Peso Total: %d Valor Total: %d\n",peso_total,valor_total);

    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_stime;

    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    //Encerrando a execucao do programa
    free(estoque);
    fclose(mochila);
    printf("---------------------------------\n" );
  }

  return 0;
}
