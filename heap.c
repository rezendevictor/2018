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
            printf("N�o � um heap.");
            return;
        }
    }

     printf("� Um heap.");
}



int main() {
    int tamanho;
    int *heap;
    int i;

    printf("Digite o tamanho do possivel heap:");
    scanf("%d", &tamanho);
    putchar('\n');

    heap = (int*) malloc (tamanho+2 * sizeof(int));

    printf("Insira cada item do vetor a seguir:");

    for(i=1; i<=tamanho;i++ ){
        scanf("%d",&heap[i]);
    }

    verifica(heap,tamanho);

    free(heap);
    return 0;


}
