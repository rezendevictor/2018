#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[20];
}Municipios;

//source: https://www.codewithc.com/dijkstras-algorithm-in-c/

void dijkstra(int **G,int elements,int startnode,int endnode,Municipios * vetor_nome)
{
  int MAX = elements;
  int cost[MAX][MAX],distance[MAX],pred[MAX],caminho[MAX];
  int visited[MAX],count,mindistance,nextnode,i,j;

  for(int t =0;t<MAX;t++)
  caminho[t]= 99999999;

  //pred[] stores the predecessor of each node
  //count gives the number of nodes seen so far
  //create the cost matrix

  for(i=0;i<elements;i++)
  for(j=0;j<elements;j++){
    cost[i][j]=G[i][j];
    if(cost[i][j]==0){
      cost[i][j]=9999999;
    }
  }

  //printf("Aqui 1\n" );
  //initialize pred[],distance[] and visited[]

  for(i=0;i<elements;i++)
  {
    distance[i]=cost[startnode][i];
    pred[i]=startnode;
    visited[i]=0;
  }

  distance[startnode]=0;
  visited[startnode]=1;
  count=1;


  while(count<elements)
  {
    mindistance=9999999;

    //nextnode gives the node at minimum distance
    for(i=0;i<elements;i++){
      if(distance[i]<mindistance&&!visited[i])
      {

        mindistance=distance[i];
        nextnode=i;
      }
    }

    //check if a better path exists through nextnode
    visited[nextnode]=1;
    for(i=0;i<elements;i++){
      if(!visited[i]){
        if(mindistance+cost[nextnode][i]<distance[i]){
          distance[i]=mindistance+cost[nextnode][i];
          //printf("%d\n",distance[i] );
          pred[i]=nextnode;
        }
        count++;
      }
    }
  }

  //print the path and distance of each node
  for(i=0;i<elements;i++){
    if(i!=startnode){
      if( i == endnode)
      {
        printf("Menor percurso:");
        caminho[0] = i;
        j=i;

        int t = 1;
        do
        {
          j=pred[j];
          caminho[t] = j;
          t++;
        }while(j!=startnode);
        t=t-1;
        do
        {
          printf(" %s",vetor_nome[caminho[t]].nome );
          t--;
        }while(t!=0);
        printf(" %s",vetor_nome[caminho[t]].nome);

        printf("\nDistancia total: %d Km\n",distance[i]);


      }
    }
  }

}



int ** Aloca_matriz(int **matriz, int lin, int col){

  matriz = (int **)malloc(lin * sizeof(int*));
  for(int i = 0; i < col; i++)
  matriz[i] = (int *)malloc(col * sizeof(int));
  int i,j;
  for(i = 0; i < lin; i++ ){
    for(j = 0; j < col; j++ ){
      if(i != j){
        matriz[i][j] = 0;
      }else{
        matriz[i][j] = 99999999;
      }
    }
  }
  return matriz;

}

void associacao(FILE *cidades,int **estradas,int num_elementos,Municipios * vetor_nome,int arestas){

  int i = 0,cont;
  char nome1[20], nome2[20];
  int dist,posicao1 = 0, posicao2= 0;
  char line[152]; // or however large you think these lines will be
  /* open the file for reading */
  /* "rt" means open the file for reading text */
  rewind(cidades);


  int cur_line = 0;

  while(fgets(line, 152, cidades) != NULL) {
    if (cur_line != 0) { // 3rd line
      /* get a line, up to 512 chars from in.  done if NULL */
      sscanf(line,"%s %s %d",nome1,nome2,&dist);
      //printf("%s %s \n",nome1,nome2);

      for(cont = 0;cont < num_elementos+1; cont++){
        if(strcmp(nome1, vetor_nome[cont].nome) == 0){
          posicao1 = cont;
          //printf("%d ",posicao1);
        }
        if(strcmp(nome2, vetor_nome[cont].nome) == 0){
          posicao2 = cont;
          //printf("%d \n",posicao2);
        }
      }//for end


      if(i != arestas){
        estradas[posicao2][posicao1] = dist;
        estradas[posicao1][posicao2] = dist;
        //printf("%d\n",dist );
      }
      i++;

    }
    cur_line++;
  }

  for(cont = 0;cont < num_elementos; cont++){
    if(strcmp(nome1, vetor_nome[cont].nome) == 0){
      posicao1 = cont;
    }
    if(strcmp(nome2, vetor_nome[cont].nome) == 0){
      posicao2 = cont;

    }
  }

  //printf("%d %d\n",posicao1, posicao2 );
  dijkstra(estradas,num_elementos,posicao1,posicao2,vetor_nome);

}

void solucao(FILE *cidades,int **estradas,int num_elementos){

  //variaveis auxiliares
  int cont ;
  char nome1[20], nome2[20];
  int dist,entrou1 = 1, apontador = 0;

  //variaveis utilizadas
  Municipios vetor_nome[num_elementos];
  // inicializando a matriz linha coluna

  char line[50]; // or however large you think these lines will be

  /* "rt" means open the file for reading text */
  int cur_line = 0;
  while(fgets(line, 50, cidades) != NULL) {
    if (cur_line >= 0) { // 3rd line
      /* get a line, up to 512 chars from in.  done if NULL */

      sscanf(line,"%s %s %d",nome1,nome2,&dist);
      //printf("%s %s %d\n",nome1,nome2,dist);
      //strcpy(nome1,mantem);
      //printf("%s\n",mantem);

      for(cont = 0;cont < num_elementos; cont++){
        if(strcmp(nome1, vetor_nome[cont].nome) == 0){
          entrou1 = 0;
          break;
        }
        entrou1 = 1;
      }

      if(entrou1 == 1){
        strcpy(vetor_nome[apontador].nome,nome1);
        //printf("apontador: %s\n",vetor_nome[apontador].nome );
        apontador++;
      }
    }
    cur_line++;
  }
  rewind(cidades);
   cur_line = 0;
  while(fgets(line, 50, cidades) != NULL) {
    if (cur_line >= 0) { // 3rd line
      /* get a line, up to 512 chars from in.  done if NULL */
      sscanf(line,"%s %s %d",nome1,nome2,&dist);
      for(cont = 0;cont < num_elementos; cont++){
        if(strcmp(nome2, vetor_nome[cont].nome) == 0){
          entrou1 = 0;
          break;
        }
        entrou1 = 1;
      }

      if(entrou1 == 1){
        strcpy(vetor_nome[apontador].nome,nome2);
        //printf("apontador: %s\n",vetor_nome[apontador].nome );
        apontador++;
      }
    }
    cur_line++;
  }
  estradas = Aloca_matriz(estradas,apontador,apontador);
  associacao(cidades,estradas,apontador,vetor_nome,num_elementos);

}//solucao end


int main() {
  //declarando variaveis
  char * nome_arquivo =  malloc(500 * sizeof(char));;
  int ** estradas = NULL;
  int num_elementos;

  printf("Digite o nome do arquivo de entrada: ");
  scanf("%s",nome_arquivo);
  //printf("%s\n",nome_arquivo );

  //abrindo o arquivo
  FILE *cidades;
  cidades = fopen(nome_arquivo, "r");
  if(cidades == NULL)
  printf("Erro, nao foi possivel abrir o arquivo\n");

  fscanf(cidades, "%d", &num_elementos);

  solucao(cidades,estradas,num_elementos);

  //Le o arquivo;
  free(estradas);
  fclose(cidades);
  return 0;
}
