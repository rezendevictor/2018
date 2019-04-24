#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#define MAX 10

typedef struct TipoCelula *TipoApontador;

typedef int TipoChave;

typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct TipoFila {
  TipoApontador Frente, Tras;
} TipoFila;

void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Frente;
  Fila->Frente->Prox = NULL;
}

int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); }

void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Fila->Tras = Fila->Tras->Prox;
  Fila->Tras->Item = x;
  Fila->Tras->Prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
  q = Fila->Frente;
  Fila->Frente = Fila->Frente->Prox;
  *Item = Fila->Frente->Item;
  free(q);
}

void Imprime(TipoFila Fila)
{ TipoApontador Aux;
  Aux = Fila.Frente->Prox;
  while (Aux != NULL)
  { printf("%d\n", Aux->Item.Chave);
  Aux = Aux->Prox;
}
}

void menu(FILE *opcao){

  char nome1;
  char line[152];
  int dist;
  TipoFila fila;
  TipoItem usado;
  TipoApontador aux;
  FFVazia(&fila);

  int cur_line = 0;
  while(fgets(line, 152, opcao) != NULL) {
    if (cur_line != -1) { // 3rd line
      /* get a line, up to 512 chars from in.  done if NULL */
      sscanf(line,"%s %d",&nome1,&dist);

      switch (nome1) {

        case 'a':
        usado.Chave = dist;
        Enfileira(usado,&fila);
        break;

        case 'b':

        aux = fila.Frente -> Prox;
        usado.Chave = aux-> Item.Chave;
        Desenfileira(&fila,&usado);

        break;

        case 'c':

        printf("Processos na fila: \n");
        Imprime(fila);
        printf("\n");

        break;
      }


    }
    cur_line++;
  }

}


int main(int argc, char *argv[])
{

  char * nome_arquivo =  malloc(500 * sizeof(char));;

  printf("Digite o nome do arquivo: ");
  scanf("%s",nome_arquivo);

  //abrindo o arquivo
  FILE *opcao;
  opcao = fopen(nome_arquivo, "r");
  if(opcao == NULL)
  printf("Erro, nao foi possivel abrir o arquivo\n");

  menu(opcao);


  return 0;
}
