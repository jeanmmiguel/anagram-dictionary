#ifndef __ILIST_H__
#define __ILIST_H__
// protótipos das funções


typedef struct palavra{
   char original[30];
   char ordenada[30];
}palavra;

palavra* Palavra_criar();
void ler_arquivo();
void troca(char*v,int maior,int i);
int partition(char *v,int p, int r);
void quickSort(char *v, int e , int d);
void ordenacao(palavra* palavra, char* buscar);
int partition_palavra(char *v,int p, int r);
void quickSort_palavra(char *v, int e , int d);
int busca_binaria(palavra *v, int e,int d, char* x);
void merge(palavra *v, int p, int q, int r);
int mergeSort(palavra *v,int e, int d);
int novo_dicionario(palavra *palavra);
void minusculo(char* s1);
#endif