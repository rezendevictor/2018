/************************************************
LAED1 - Trabalho Pratico 2
Aluno: Victor Franco Rezende
Matricula: --
Descricao do programa: O programa faz a analise e registo de cada metodo de ordenacao
e imprime todos os resultados em um arquivo .csv. Todos os algoritmos foram retirados dos Slides
de aula  
Data:
************************************************/

#include <stdio.h>
#include <time.h>

#define MAXTAM 100000

clock_t start, end;
double cpu_time_used[10];



typedef long TipoChave;

typedef struct TipoItem {
    TipoChave Chave;

} TipoItem ;

typedef int TipoIndice ;
typedef TipoItem TipoVetor [ MAXTAM + 1];

TipoVetor A;



void Selecao(TipoItem *A, TipoIndice n){
    TipoIndice i ,j , Min;
    TipoItem x;
    for(i = 1; i<= n -1; i++){
        Min = i;
        for(j = i + 1; j <= n;j++){
            if(A[j].Chave < A[i].Chave) Min = j;

            x = A[Min];
            A[Min] = A[i];
            A[i] = x;
        }
    }
}


void Insercao(TipoItem *A, TipoIndice n){
    TipoIndice i,j;
    TipoItem x;
    for(i = 2; i <= n ; i++){
        x = A[i];
        j = i - 1;
        A[0] = 0; //Sentinela
        while (x.Chave < A[j].Chave) {
            A[j+1]= A[j;
            j--;
        }
        A[j+1] = x;
    }

}


void Shellsort(TipoItem *A, TipoIndice n){
    int i, j;
    int h = 1;
    TipoItem x;
    do h = h*3 +1; while(h<n);
    do{
        h/=3;
        for(i = h+1; i <= n ; i++){
            while(A[j - h].Chave> x.Chave){
                A[j] = A[j - h];
                j-= h;
                if(j<= h) goto L999;
            }
            L999 : A[j] = x;
        }
    }while(h != 1);

}

void Bubblesort(int *A, int n)
{
    int i, j;
    int aux;
    for (j=0; j<n­1; j++){
        for (i=0; i<n­1; i++){
            if (A[i] > A[i+1]){
                aux = A[i];
                A[i] = A[i+1];
                A[i+1] = aux;
            }
        }
    }
}


//MERGESORT ======================================================
void Merge(Vetor A, int i, int m, int j){
    Vetor B;
    int x;
    int k = i;
    int l = m+1;

    for (x=i;x<=j;x++) B[x] = A[x];
    x = i;
    while (k<=m && l<=j) {
        if (B[k] <= B[l])
        A[x++] = B[k++];
        else
        A[x++] = B[l++];
    }
    while (k<=m) A[x++] = B[k++];
    while (l<=j) A[x++] = B[l++];
}

void Mergesort(Vetor A, int i, int j){
    int m;
    if (i < j){
        m = (i + j ­ 1) / 2;
        Mergesort(A, i, m);
        Mergesort(A, m + 1, j);
        Merge(A,  i,  m, j); /*Intercala A[i..m] e A[m+1..j] em A[i..j] */
    }
}


//END MERGESORT ========================================================

// QUICKSORT ===========================================================

void Particao(TipoIndice Esq, TipoIndice Dir,
    TipoIndice *i, TipoIndice *j, TipoItem *A)
    { TipoItem x, w;
        *i = Esq; *j = Dir;
        x = A[(*i + *j) / 2]; /* obtem o pivo x */
        do
        { while (x.Chave > A[*i].Chave) (*i)++;
            while (x.Chave < A[*j].Chave) (*j)--;
            if (*i <= *j)
            { w = A[*i];
                A[*i] = A[*j];
                A[*j] = w;
                (*i)++; (*j)--;
            }
        } while (*i <= *j);
    }

    void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
    { TipoIndice i, j;
        Particao(Esq, Dir, &i, &j, A);
        if (Esq < j) Ordena(Esq, j, A);
        if (i < Dir) Ordena(i, Dir, A);
    }
    void QuickSort(TipoItem *A, TipoIndice n)
    { Ordena(1, n, A);
    }




    //END QUICKSORT ========================================================

    //HEAPSORT =============================================================
    void Ordena(TipoIndice Esq, TipoIndice Dir , TipoItem ∗A)
    { TipoIndice i , j ;
        Particao(Esq, Dir, & i , & j , A);
        if (Esq < j ) Ordena(Esq, j , A);
        if ( i < Dir ) Ordena( i , Dir , A);
    }

    void QuickSort(TipoItem ∗A, TipoIndice n)
    { Ordena(1 , n, A) ; }

    TipoItem Max(TipoItem ∗A)
    { return (A[1]); }

    void Refaz(TipoIndice Esq, TipoIndice Dir , TipoItem ∗A)
    { TipoIndice i = Esq;
        int j ; TipoItem x;
        j = i ∗ 2;
        x = A[ i ] ;
        while ( j <= Dir)
        { if ( j < Dir)
            { if (A[ j ] .Chave < A[ j +1].Chave)
                j ++;
            }
            if (x.Chave >= A[ j ] .Chave) goto L999;
            A[ i ] = A[ j ] ; i = j ; j = i ∗ 2;
        }
        L999: A[ i ] = x;
    }

    void Constroi(TipoItem ∗A, TipoIndice n)
    { TipoIndice Esq;
        Esq = n / 2 + 1;
        while (Esq > 1)
        { Esq−−;
            Refaz(Esq, n, A);
        }
    }

    TipoItem RetiraMax(TipoItem ∗A, TipoIndice ∗n)
    { TipoItem Maximo;
        if (∗n < 1)
        printf ( "Erro : heap vazio\n" );
        else { Maximo = A[1]; A[1] = A[∗n] ; (∗n)−−;
            Refaz(1 , ∗n, A);
        }
        return Maximo;
    }

    void AumentaChave(TipoIndice i , TipoChave ChaveNova, TipoItem ∗A)
    { TipoItem x;
        if (ChaveNova < A[ i ] .Chave)
        { printf ( "Erro : ChaveNova menor que a chave atual \n" );
        return;
    }
    A[ i ] .Chave = ChaveNova;
    while ( i > 1 && A[ i / 2 ] .Chave < A[ i ] .Chave)
    { x = A[ i / 2 ] ; A[ i / 2] = A[ i ] ; A[ i ] = x;
        i /= 2;
    }
}
void Insere(TipoItem ∗x, TipoItem ∗A, TipoIndice ∗n){
    (∗n)++; A[∗n] = ∗x; A[∗n] .Chave = INT_MIN;
    AumentaChave(∗n, x−>Chave, A);
}

void Heapsort(TipoItem ∗A, TipoIndice n)
{ TipoIndice Esq, Dir ;
    TipoItem x;
    Constroi(A, n) ; /∗ constroi o heap ∗/
    Esq = 1; Dir = n;
    while ( Dir > 1)
    { /∗ ordena o vetor ∗/
        x = A[1]; A[1] = A[ Dir ] ; A[ Dir ] = x; Dir−−;
        Refaz(Esq, Dir , A);
    }
}

void SelecaoParcial(TipoVetor A,
    TipoIndice n, TipoIndice k)
    { TipoIndice i , j , Min; TipoItem x;
        for ( i = 1; i <= k; i++)
        { Min = i ;
            for ( j = i + 1; j <= n; j++)
            if (A[ j ] .Chave < A[Min] .Chave) Min = j ;
            x = A[Min] ; A[Min] = A[ i ] ; A[ i ] = x;
        }
    }
    void InsercaoParcial(TipoVetor A, TipoIndice n,
        TipoIndice k)
        { /∗−−Nao preserva o restante do vetor−−∗/
            TipoIndice i , j ; TipoItem x;
            for ( i = 2; i <= n; i++)
            { x = A[ i ] ;
                if ( i > k) j = k; else j = i − 1;
                A[0] = x; /∗ sentinela ∗/
                while (x.Chave < A[ j ] .Chave)
                { A[ j +1] = A[ j ] ;
                    j−−;
                }
                A[ j +1] = x;
            }
        }

        void InsercaoParcial2(TipoVetor A, TipoIndice n, TipoIndice k)
        { /∗−−Preserva o restante do vetor−−∗/
            TipoIndice i , j ; TipoItem x;
            for ( i = 2; i <= n; i++)
            { x = A[ i ] ;
                if ( i > k)
                { j = k; if (x.Chave < A[k] .Chave) A[ i ] = A[k ] ; }
                else j = i − 1;
                A[0] = x; /∗ sentinela ∗/
                while (x.Chave < A[ j ] .Chave)
                { if ( j < k) {A[ j +1] = A[ j ] ; }
                j−−;
            }
            if ( j < k) A[ j +1] = x;
        }
    }
    void HeapsortParcial(TipoItem ∗A, TipoIndice n, TipoIndice k)
    { TipoIndice Esq = 1; TipoIndice Dir ;
        TipoItem x; long Aux = 0;
        Constroi(A, n) ; /∗ constroi o heap ∗/
        Dir = n;
        while (Aux < k)
        { /∗ ordena o vetor ∗/
            x = A[1];
            A[1] = A[n − Aux] ;
            A[n − Aux] = x;
            Dir−−; Aux++;
            Refaz(Esq, Dir , A);
        }
    }


    // END HEAPSORT ========================================================

    int main(int argc, char const *argv[]) {
        //o arquivo deve seguir o modelo: numero de itens, depois os itens
        // quando for executar, devemos
        int *vetor;
        int numero_itens;

        int controle = 0;
        scanf("%d", &numero_itens );

        vetor = malloc (numero_itens * sizeof (int));

        for(;controle <= numero_itens; controle++){
            scanf("%d",&vetor[controle].Chave );
        }

        start = clock();
        //insere a funcao
        end = clock();
        cpu_time_used[0] = ((double) (end - start))/CLOCKS_PER_SEC;
        //repete isso para cada funcao de ordenacao


        return 0;
    }

