#include <stdio.h>
#include <stdlib.h>

void verifica(int *heap,int tam){
    int pai;
    int esquerda;
    int direita;
    int i;

    for(i = 1; i < (tam/2)+1;i++){
        pai = heap[i];
        esquerda = heap[(i*2)];
        direita = heap[(i*2)+1];
        if(pai < esquerda || pai < direita){
            printf("Não é um heap.");
            return;
        }
    }

     printf("É Um heap.");
}


int main(){
	int tamanho;
    int *heap;
    int i;

    printf("Digite o tamanho do possivel heap:");
    scanf("%d", &tamanho);
    printf("\n");

    heap = (int*) malloc (tamanho+1 * sizeof(int));

    printf("Insira cada item do vetor a seguir:");

    for(i=1; i<=tamanho;i++ ){
        scanf("%d",&heap[i]);
    }

    verifica(heap,tamanho);

    return 0;

}
