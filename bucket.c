#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define MAX 10

typedef char TipoChave[100];
typedef struct {
  TipoChave Nome;
  int Nota;
  /* outros componentes */
} TipoItem;
typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct {
  TipoApontador Fundo, Topo;
  int Tamanho;
} TipoPilha;

void FPVazia(TipoPilha *Pilha)
{ Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Fundo = Pilha->Topo;
  Pilha->Topo->Prox = NULL;
  Pilha->Tamanho = 0;
}

int Vazia(TipoPilha Pilha)
{ return (Pilha.Topo == Pilha.Fundo); }

void Empilha(TipoItem x, TipoPilha *Pilha)
{ TipoApontador Aux;
  Aux = (TipoApontador) malloc(sizeof(TipoCelula));
  Pilha->Topo->Item = x;
  Aux->Prox = Pilha->Topo;
  Pilha->Topo = Aux;
  Pilha->Tamanho++;
}

void Desempilha(TipoPilha *Pilha, TipoItem *Item)
{ TipoApontador q;
  if (Vazia(*Pilha)) { printf("Erro: lista vazia\n"); return; }
  q = Pilha->Topo;
  Pilha->Topo = q->Prox;
  *Item = q->Prox->Item;
  free(q);  Pilha->Tamanho--;
}

int Tamanho(TipoPilha Pilha)
{ return (Pilha.Tamanho); }

// --------------- funcoes adicionadas




TipoPilha Organiza(TipoPilha *Pilha){
  int i;
  int tamanho = Tamanho(Pilha);
  TipoItem balde[tamanho];

  for(i = 0; i < tamanho;i++){
    balde[i] = Desempilha(Pilha,Pilha -> Topo);
  }

  for(i = 0; i < tamanho;i++){
    int j = 0;
    for(j = 0; j < tamanho; j++){
      if(i==j){
        continue;
      }else if(tamanho )

    }
  }


}




// ------ fim -------
int main(int argc, char *argv[]){

  return(0);
}
