#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 13
#define N 50
#define TAMALFABETO 26


/* typedef unsigned int  TipoPesos[n]; */
typedef char TipoChave[N];
typedef unsigned TipoPesos[N][TAMALFABETO];
typedef struct TipoItem {
    /* outros componentes */
    TipoChave Chave;
} TipoItem;
typedef unsigned int TipoIndice;
typedef struct TipoCelula* TipoApontador;
typedef struct TipoCelula {
    TipoItem Item;
    TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
    TipoCelula *Primeiro, *Ultimo;
} TipoLista;
typedef TipoLista TipoDicionario[M];
TipoDicionario Tabela;
TipoItem Elemento;
TipoPesos p;
TipoApontador i;

void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro; Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo); }

void Ins(TipoItem x, TipoLista *Lista)
{ Lista->Ultimo->Prox = (TipoCelula *)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox; Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Ret(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{  /* -- Obs.: o item a ser retirado o seguinte ao apontado por p -- */
    TipoApontador q;
    if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
    { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
}
q = p->Prox; *Item = q->Item; p->Prox = q->Prox;
if (p->Prox == NULL)
Lista->Ultimo = p;
free(q);
}

/*
void GeraPesos(TipoPesos p)
{ int i;
struct timeval semente;
gettimeofday(&semente, NULL);
srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
for (i = 0; i < n; i++)
p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i;
unsigned int Soma = 0;
int comp = strlen(Chave);
for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
return (Soma % M);
}
*/

void GeraPesos(TipoPesos p)
{ /* Gera valores randomicos entre 1 e 10.000 */
    int i, j;
    struct timeval semente;
    /* Utilizar o tempo como semente para a funcao srand() */
    gettimeofday(&semente, NULL);
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
    for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
    p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

TipoIndice h(TipoChave Chave, TipoPesos p)
{ int i; unsigned int Soma = 0;
    int comp = strlen(Chave);
    for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)Chave[i]];
    return (Soma % M);
}

void Inicializa(TipoDicionario T)
{ int i;
    for (i = 0; i < M; i++) FLVazia(&T[i]);
}

TipoApontador Pesquisa(TipoChave Ch, TipoPesos p, TipoDicionario T)
{ /* Obs.: TipoApontador de retorno aponta para o item anterior da lista */
    TipoIndice i;
    TipoApontador Ap;
    i = h(Ch, p);
    if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
    else
    { Ap = T[i].Primeiro;
        while (Ap->Prox->Prox != NULL &&
            strncmp(Ch, Ap->Prox->Item.Chave, sizeof(TipoChave)))
            Ap = Ap->Prox;
            if (!strncmp(Ch, Ap->Prox->Item.Chave, sizeof(TipoChave)))
            return Ap;
            else return NULL;  /* Pesquisa sem sucesso */
        }
    }

    void Insere(TipoItem x, TipoPesos p, TipoDicionario T)
    { if (Pesquisa(x.Chave, p, T) == NULL)
        Ins(x, &T[h(x.Chave, p)]);
        else printf(" Registro ja  esta  presente\n");
    }

    void Retira(TipoItem x, TipoPesos p, TipoDicionario T)
    { TipoApontador Ap; Ap = Pesquisa(x.Chave, p, T);
        if (Ap == NULL)
        printf(" Registro nao esta  presente\n");
        else Ret(Ap, &T[h(x.Chave, p)], &x);
    }

    void Imp(TipoLista Lista)
    { TipoApontador Aux;
        Aux = Lista.Primeiro->Prox;
        while (Aux != NULL)
        { printf("%.*s ", N, Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}

void Imprime(TipoDicionario Tabela)
{ int i;
    for (i = 0; i < M; i++)
    { printf("%d: ", i);
    if (!Vazia(Tabela[i]))
    Imp(Tabela[i]);
    putchar('\n');
}
}

void LerPalavra(char *p, int Tam)
{ char c; int i, j;
    fflush(stdin); j=0;
    while (((c=getchar())!='\n') && j<Tam-1) p[j++]= c;
    p[j]='\0';
    while(c != '\n') c=getchar();
    /* Desconsiderar espacos ao final
    da cadeia como ocorre em Pascal.*/
    for(i=j-1;(i>=0 && p[i]==' ');i--) p[i]='\0';
}
void leitura(FILE *base, TipoDicionario Tabela){

    char line[20], letra;
    int indice,cur_line = 0;
    TipoItem inserido;
    char salvo = 1;


    while(fgets(line, 2, base) != NULL) {
        if (cur_line >= 0) {
            /* get a line, up to 512 chars from in.  done if NULL */
            sscanf(line,"%s",&letra);
            indice = (letra - 64)%13;
            if(salvo != letra){
                inserido.Chave[0] = letra;
                Ins(inserido,&Tabela[indice]);
                salvo = letra;
            }
        }
        cur_line++;
    }
}

void ordem(TipoLista lista,int item){
    TipoApontador aux;
    if(Vazia(lista)){
        return;
    }
    aux = lista.Primeiro -> Prox;
    while(aux != NULL){
        if(aux->Item.Chave[0] == item){
            printf("%s\n",aux->Item.Chave);
        }
        aux = aux->Prox;
    }


}

int main(){
    TipoDicionario Tabela;
    int i = 0;
    int j = 0;
    char *nome_arquivo =  (char*) malloc(50 * sizeof(char));;
    Inicializa(Tabela);
    printf("Digite o nome do arquivo: ");
    scanf("%s",nome_arquivo );
    printf ("\n");

    FILE *tabe;
    tabe = fopen(nome_arquivo, "r");
    if(tabe == NULL)
    printf("Erro, nao foi possivel abrir o arquivo\n");

    leitura(tabe, Tabela);
    printf("Tabela apos insercoes:\n");
    Imprime(Tabela);
    printf("\n" );
    printf("Chaves em ordem alfabetica:\n");

    for(i  = 65; i <= 90; i++){
        for(j = 0; j < M; j++){
            ordem(Tabela[j],i);
        }
    }

    for(i  = 97; i <= 122; i++){
        for(j = 0; j < M; j++){
            ordem(Tabela[j],i);
        }
    }
    return 0;
}
