/* ========================================================================== */
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#define INICIOARRANJO   1
#define MAXTAM          1000

typedef int TipoChave;

typedef int TipoApontador;

typedef struct {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef struct {
  TipoItem Item[MAXTAM];
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================== */

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = INICIOARRANJO;
  Lista -> Ultimo = Lista -> Primeiro;
}  /* FLVazia */

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void Insere(TipoItem x, TipoLista *Lista)
{ if (Lista -> Ultimo > MAXTAM) printf("Lista esta cheia\n");
else { Lista -> Item[Lista -> Ultimo - 1] = x;
  Lista -> Ultimo++;
}
}  /* Insere */

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ int Aux;

  if (Vazia(*Lista) || p >= Lista -> Ultimo)
  { printf(" Erro   Posicao nao existe\n");
  return;
}
*Item = Lista -> Item[p - 1];
Lista -> Ultimo--;
for (Aux = p; Aux < Lista -> Ultimo; Aux++)
Lista -> Item[Aux - 1] = Lista -> Item[Aux];
}  /* Retira */

void Imprime(TipoLista Lista)
{ int Aux;

  for (Aux = Lista.Primeiro - 1; Aux <= (Lista.Ultimo - 2); Aux++)
  printf("%d\n", Lista.Item[Aux].Chave);
}  /* Imprime */

TipoApontador localiza(TipoLista Lista, TipoItem Proc){
  TipoItem localizado;
  TipoApontador contador;
  int i = INICIOARRANJO;


  for(contador= Lista.Primeiro;contador != Lista.Ultimo;contador++){

    if(Lista.Item[i].Chave == Proc.Chave){
      printf("O item esta na Posicao %d\n", i );
      return contador;
    }
    else i++;
  }
  printf("Item nao encontrado\n" );
  return 1;


}


TipoLista Particiona(TipoLista Lista1,TipoItem Local){
  int i = 1;
  TipoApontador contador;
  TipoLista Lista2;
  FLVazia(&Lista2);
  TipoApontador auxiliar;

  for(contador= Lista1.Primeiro;contador != Lista1.Ultimo;contador++){
    if(Lista1.Item[i].Chave == Local.Chave) break;
    else i++;
  }
  while(i != Lista1.Ultimo){
    auxiliar = i;
    Insere(Lista1.Item[i],&Lista2);
    Retira(auxiliar,&Lista1,&Lista1.Item[i]);
  }


}






void menu(){

  int opcao = 0;
  TipoLista Lista;
  TipoItem Inserir;
  TipoLista Lista2;


  printf("1. Criar lista vazia\n 2. Inserir elemento\n 3. Retirar elemento\n 4. Localizar um item na lista dada a sua chave.\n 5. Particionar a lista em duas a partir de determinado item.\n 6. Imprimir lista\n 7. Sair\n" );
  scanf("%d",&opcao );

  while(opcao != 7){
    switch (opcao) {
      case 1:// Criar lista vazia\n
      FLVazia(&Lista);
      break;
      case 2: //Inserir elemento\n
      printf("Insira a chave do Item:\n");
      scanf("%d\n",&Inserir.Chave);
      Insere(Inserir,&Lista);
      break;
      case 3:// Retirar elemento\n
      printf("Insira a chave do Item:\n");
      scanf("%d\n",&Inserir.Chave);
      Retira((Lista.Ultimo -1),&Lista,&Inserir);
      break;
      case 4: //Localizar um item na lista dada a sua chave.\n
      printf("Insira a chave do Item:\n");
      scanf("%d\n",&Inserir.Chave);
      localiza(Lista,Inserir);
      break;
      case 5:// Particionar a lista em duas a partir de determinado item.\n
      printf("Insira a chave do Item:\n");
      scanf("%d\n",&Inserir.Chave);
      Lista2 = Particiona(Lista,Inserir);
      break;
      case 6:// Imprimir lista\n
      Imprime (Lista);
      break;
    }
  }

}



/* ========================================================================== */

int main(int argc, char *argv[])
{ struct timeval t;

  TipoLista lista;
  TipoItem item;
  int vetor[MAXTAM];
  int i, j, k, n, max;
  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  max = 10;
  FLVazia(&lista);

  /*Gera uma permutacao aleatoria de chaves entre 1 e max*/
  for(i = 0; i < max; i++) vetor[i] = i + 1;
  for(i = 0; i < max; i++)
  { k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
    j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
    n = vetor[k];
    vetor[k] = vetor[j];
    vetor[j] = n;
  }
  /*Insere cada chave na lista */
  for (i = 0; i < max; i++)
  { item.Chave = vetor[i];
    Insere(item, &lista);
    printf("Inseriu: %d \n", item.Chave);
  }
  Imprime(lista);

  /*Retira cada chave da lista */
  for(i = 0; i < max; i++)
  { /*escolhe uma chave aleatoriamente */
    j = (int) ((lista.Ultimo - 1) * rand() / (RAND_MAX + 1.0));
    /*retira chave apontada */
    Retira(j, &lista, &item);
    printf("Retirou: %d\n", item.Chave);
  }
  Imprime (lista);


  return(0);
}
