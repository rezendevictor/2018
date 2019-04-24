#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 10

/* ========================================================================= */

typedef int TipoChave;

typedef struct {
  /* qual e a palavra;
  Definido desse jeito para ser usado como ponteiro;
  Maior palavra do portugues tem 46 letras e a maior palavra do mundo tem 85;
  */
  char palavra[50];
  int ocorrencia; // quantas vezes a palavra aparece;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL)
  { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
  return;
}
q = p -> Prox;
*Item = q -> Item;
p -> Prox = q -> Prox;
if (p -> Prox == NULL) Lista -> Ultimo = p;
free(q);
}

void Imprime(TipoLista Lista)
{
  TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL){
    printf("%s  [%d] \n ", Aux -> Item.palavra, Aux -> Item.ocorrencia);
    Aux = Aux -> Prox;
  }
}

/*Funcoes Adicionadas para resolucao da questao 1 ========================= */
//compara as palavras
static int contador = 0;

void checagem(TipoLista *Lista, char temporario[50], int contador){
  //Variaveis auxiliares
  TipoApontador Aux;
  TipoItem ItemNovo;
  char palavra[contador];
  int i;

  strcpy(palavra,temporario);
  //Pegando o primeiro item

  if(Vazia(*Lista)){
    strcpy(ItemNovo.palavra, palavra);
    ItemNovo.ocorrencia = 1;
    Insere(ItemNovo, Lista);
    return;
  }

  Aux = Lista -> Primeiro -> Prox;

  while (Aux != NULL){

    if(strcmp(Aux -> Item.palavra, palavra)==0){
      Aux -> Item.ocorrencia++;
      return;
    }

    Aux = Aux -> Prox;
  }

  strcpy(ItemNovo.palavra, palavra);
  ItemNovo.ocorrencia = 1;
  Insere(ItemNovo,Lista);

  return;
}



//le o texto
void leitura(TipoLista *Lista, FILE *arquivo){
  char c;
  char temporario[50];
  int contador=0;
  c = fgetc(arquivo);
  while(c!= EOF){
    if(c == ' ' || c == '\n' || c == '.' || c == ',' || c == ':' || c == ';' || c == '!' || c == '?'|| c == '('|| c == ')'|| c == '-' ){
      //chama funcao de comparacao
      if(contador>0){
        checagem(Lista, temporario, contador);
        while(contador!= -1){
          temporario[contador] = '\0';
          contador--;
        }
      }
      contador = 0; //chegou no fim da palavra
    }
    else{
      temporario[contador] = c; //armazena as palavras letra por letra na string
      contador++; //anda a posicao
    }
    c = fgetc(arquivo);
  }
}




/* ========================================================================= */

int main(int argc, char *argv[])
{ struct timeval t;

  TipoLista lista;
  TipoItem item;
  int vetor[MAX];
  TipoApontador p;
  FLVazia(&lista);
  FILE *arquivo;


  char * nome_arquivo =  malloc(100 * sizeof(char));;

  while(1){
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s",nome_arquivo);

    //abrindo o arquivo
    arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
      printf("Erro, nao foi possivel abrir o arquivo\n");
    }
    else break;
  }

  leitura(&lista,arquivo);
  Imprime(lista);

  return 0;
}
