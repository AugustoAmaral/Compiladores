/*ESTRUTURA

BEGIN

DECLARACAO DE VARIAVEIS

FUNCOES

END*/
#include <stdio.h>
#include <ctype.h>

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

int verificarId (char* palavra){ // RETORNA 1 SE TODAS AS LETRAS FOREM MAIUSCULAS E 0 CASO N
	int i=0;
	int check;
	for (i=0;i<strlen(palavra);i++)
		if (palavra[i] != toupper(palavra[i]))
			return 0;
	return 1;
	
}
