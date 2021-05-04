#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <limits.h>
//implementações das funções

int novo_dicionario(palavra *palavra) { // função auxiliar para imprimir o vetor ordenado em arquivo
    
    FILE *arq = fopen("dicionario_ordenado.txt", "w+");
    
    if (arq == NULL) return -1;
        for(int i = 0; i <  261798; i++) {
            fprintf(arq, "[%s,", palavra[i].original);
            fprintf(arq, "%s]\n", palavra[i].ordenada);
        }
    fclose(arq);
    return 0;
}
int busca_binaria(palavra *v,int e,int d, char* x){

  int aux, meio;
    
     if( e <= d){
        meio = (e + d) / 2;
        aux = strcmp(v[meio].ordenada,x);
        if(aux == 0) return meio;
         else{
              aux = strcmp(v[meio].ordenada,x);
            if(aux < 0){
                return busca_binaria(v, meio +1, d , x);
            }else{
                return busca_binaria(v,e,meio - 1, x);
            }
        }
    }
    return -1;

}
void troca(char *v,int maior,int i){
 char aux;
 aux = v[maior];
 v[maior] = v[i];
 v[i] = aux;

}

int partition(char *v,int p, int r){

char x;
int i, j ;
x = v[r];
i = p - 1;

for( j = p; j < r;j++){
    if(v[j] <= x){
        i++;
        troca(v,i,j);
    }
}
troca(v,i + 1,r);
return i + 1;
}

void quickSort(char *v, int e , int d){
    int q ;

    if(e < d ){
        q = partition(v,e,d);
        quickSort(v,e,q-1);
        quickSort(v,q+1,d);

   }
}
void merge(palavra *v, int p, int q, int r){

    int i,j,k;
    int n1 =  q - p +1;
    int n2 = r - q;
    int count = 0;
    int aux;
    char sentinela[] = "zzzzzzzzzz";
 

    palavra* e = (palavra*) malloc(sizeof(palavra) * (n1 + 1));
    palavra* d =(palavra*) malloc(sizeof(palavra)*(n2 + 1));

    for(i = 0; i < n1;i++){
        strcpy(e[i].ordenada, v[p + i].ordenada);
        strcpy(e[i].original, v[p + i].original);
    }
    strcpy(e[n1].ordenada, sentinela);

    for(j = 0; j < n2;j++){    
        strcpy(d[j].ordenada, v[q+1+j].ordenada);
        strcpy(d[j].original, v[q+1+j].original);
        }
    strcpy(d[n2].ordenada, sentinela);
     
         i = 0;
         j = 0;
    for( k = p; k <= r ; k++){
        aux = strcmp(e[i].ordenada, d[j].ordenada);
        if(aux < 0){       
        strcpy(v[k].ordenada , e[i].ordenada);
        strcpy(v[k].original , e[i].original);
        i++;
        }else{
        strcpy(v[k].ordenada,d[j].ordenada);
        strcpy(v[k].original , d[j].original);
        count++;
        j++;
        }
    }
     
free(e);
free(d);
}

int mergeSort(palavra *v,int e, int d){

    int meio;
    int total;

    if(e < d){
        meio =  (e + d) / 2;
        mergeSort(v,e,meio);
        mergeSort(v,meio+1,d);
        merge(v,e,meio,d);
    }
}
void ordenacao(palavra* palavra, char* buscar){

minusculo(buscar);
printf("%s",buscar);
char vet[30];
strcpy(vet,buscar);
printf("palavra digitada: %s\n",buscar);
mergeSort(palavra,0,261798);
quickSort(buscar,0, strlen(buscar)-1);
char aux[30];
strcpy(aux,buscar);
printf("palavra ordenada: %s\n",aux);

printf("Anagramas para a palavra %s:\n",vet);
int pos = busca_binaria(palavra,0,261798,aux);
if(pos == -1){
    printf("não foram encontrados anagramas para essa palavra..\n");
}
int i = pos;
int pos_aux;
while(!(strcmp(aux,palavra[i].ordenada))){
   i--;

}
pos_aux = i;
int j,x ;
printf("%s\n",vet);
for(j = pos_aux ; j < 261798; j++ ){
    x = strcmp(aux,palavra[j].ordenada);
    if(x == 0){
     printf("%s \n",palavra[j].original);

    }
}
novo_dicionario(palavra);


}

palavra* Palavra_criar(){ // alocar a estrutura 
 
palavra* palavras;

palavras = malloc(sizeof(palavra) *  261798);
ler_arquivo(palavras);
return palavras;

}

void minusculo(char* s1){ // converter as palavras em minúsculo
    
int i = 0;

    for(i = 0;i < strlen(s1); i++){ 
        if(s1[i] >= 65 && s1[i] <= 90){ 
            s1[i] += 32;
        }
    }
       
}

void ler_arquivo(palavra* palavras){ // leitura do arquivo, copia as palavras em cada campo da estrutura

 int i = 0, numPalavras = 0;
    char linhas[30];
    
    FILE *arquivo;
    arquivo = fopen("dicionario.txt", "r");

    if (arquivo == NULL)
    printf("erro no arquivo");
    while(fgets(linhas, 30 , arquivo) != NULL)
    {       

        linhas[strlen(linhas)-1] = '\0'; // insere o barra zero no final do arquivo, para tirar as quebras de linha
        minusculo(linhas);

        strcpy(palavras[i].original, (linhas));
        strcpy(palavras[i].ordenada,palavras[i].original);
        quickSort(palavras[i].ordenada,0,strlen(palavras[i].ordenada)- 1);
        i++;
        numPalavras++;

    }
    fclose(arquivo);
}
