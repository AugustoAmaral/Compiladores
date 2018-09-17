/*ESTRUTURA

BEGIN

DECLARACAO DE VARIAVEIS

FUNCOES

END*/
#include <stdio.h>

typedef struct linhas{
	struct linhas* ant;
	int id;
	char* info;
	struct linhas* prox;
} Linhas;

void printarLinha(Linhas* line){ //DEBUG ONLY
	Linhas* l = line;
	while (l != NULL){
		printf("%s",l->info);
		l = l->prox;
	}
}
