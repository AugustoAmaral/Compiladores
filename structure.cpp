/*ESTRUTURA

BEGIN

DECLARACAO DE VARIAVEIS

FUNCOES

END*/
#include <stdio.h>

typedef struct palavras{
	struct palavras* ant;
	int id;
	char* info;
	struct palavras* prox;
} Palavras;

typedef struct linhas{
	struct linhas* ant;
	int id;
	struct palavras* info;
	struct linhas* prox;
} Linhas;

void printarLinha(Linhas* line){ //DEBUG ONLY
	Linhas* l = line;
	while (l != NULL){
		printf("%s",l->info);
		l = l->prox;
	}
}
