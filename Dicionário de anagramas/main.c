#include <stdio.h>
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#define PRINT_DEBUG 0

int main(char* argc, char** argv){

   palavra* palavras;
   palavras = Palavra_criar();
   char v[40];

  printf("Informe a palavra que deseja encontrar o anagrama:");
  scanf("%s",v);
  fflush(stdin);
  ordenacao(palavras,v);

}

