#include <stdio.h>
#include <ctype.h>
#define tam_palavras_reservadas 16
const char* const lexemas_reservadas[] = {"program","integer","real","begin","end","goto","loop","read","write","var","<-",";","+","0","1",":","name"}; //16 palavras reservadas
const char* const tokens_reservadas[] = {"start","type","type","delimiter","delimiter","goto","loop","read","write","var","attr","point","operator","zero","one","point","name"};
const char* const atributo_reservadas[] = {"SUM","0","1","-","name"};



typedef struct palavras{
	struct palavras* ant;
	int tok;
	int line;
	int attr;
	int id;
	char* info;
	struct palavras* prox;
} Palavras;

typedef struct sintatico {
	char* nome;
	char* lex;
	char* val;
} Sintatico;

typedef struct linhas{
	struct linhas* ant;
	int id;
	struct palavras* info;
	struct linhas* prox;
} Linhas;

void printarLinha(Palavras* linha){ //DEBUG ONLY
	Palavras* p = linha;
	while (p->prox != NULL){
		printf("|Lin: %d  \t|Col: %d  \t|Lex: %s  \t|Tok: %s\t|Attr: %s\t|\n",p->line,p->id,lexemas_reservadas[p->tok],tokens_reservadas[p->tok],atributo_reservadas[p->attr]);
		p = p->prox;
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
