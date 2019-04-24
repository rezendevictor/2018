/************************************************
LAED1 - Trabalho Pratico 1
Aluno: Victor Franco Rezende
Matricula:
Descricao do programa: Programa visa resolver o problema da mochila com uma
aproximacao de estrategia de tentativa e erro
Data: 31/08/2018
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

//definindo estrutura para trabalhar
typedef struct{
  int peso;
  int valor ;
  int posicao;
} Objeto;

Objeto * recursiva(Objeto *estoque, Objeto *combinacao,int N_itens,int quantidade,int contador_interno,int peso_atual,int Capacidade){

  while(contador_interno<N_itens){
    if(peso_atual < Capacidade){
      combinacao[quantidade] = estoque[contador_interno];
      peso_atual += estoque[contador_interno].peso;
      quantidade++;
      contador_interno++;
    }else{
      int i;
      for(i =0; i < quantidade;i++){
        if((combinacao[i].peso/combinacao[i].valor) > (estoque[contador_interno].peso/estoque[contador_interno].valor)){
          peso_atual -= combinacao[i].peso;
          combinacao[i] = estoque[contador_interno];
          peso_atual += combinacao[i].peso;
          break;
        }
      }
      contador_interno++;
      return recursiva(estoque,combinacao, N_itens, quantidade,contador_interno, peso_atual,Capacidade);
    }
  }
  if(contador_interno == N_itens)  return combinacao;

}//Recursiva END


//funcao tentativa e erro
Objeto * tentativa(Objeto *estoque,int Capacidade,int N_itens){
  int contador_interno;
  int quantidade = 0;
  int peso_atual =0;

  Objeto *combinacao =  malloc (N_itens* 3 * sizeof (int)  );
  for(contador_interno = 0; contador_interno < N_itens; contador_interno++ ) combinacao[contador_interno].valor = 0;
  contador_interno =0;
  //funcao recursiva
  recursiva(estoque,combinacao, N_itens, quantidade,contador_interno, peso_atual,Capacidade);


  return combinacao;
}


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
    estoque = tentativa(estoque,Capacidade,N_itens);

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
