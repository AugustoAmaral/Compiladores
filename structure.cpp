#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define tam_palavras_reservadas 17
const char* const lexemas_reservadas[] = {"program","integer","real","begin","end","goto","loop","read","write","var","<-",";","+","0","1",":","name"}; //16 palavras reservadas
const char* const tokens_reservadas[] = {"start","type","type","delimiter","delimiter","goto","loop","read","write","var","attr","point","operator","zero","one","point","name"};
const char* const atributo_reservadas[] = {"SUM","0","1","-","name"};

enum token
{
	PROGRAM,
	INTEGER,
	REAL,
	BEGIN,
	END,
	GO_TO,
	LOOP,
	READ,
	WRITE,
	VAR,
	ARROW,
	SEMICOLON,
	PLUS,
	ZERO,
	ONE,
	COLON,
	NAME
};

token conversor(int num)
{
	switch (num)
	{
		case 0:
    	return PROGRAM;
    	break;
    	
		case 1:
    	return INTEGER;
    	break;
    	
		case 2:
    	return REAL;
    	break;
    	
		case 3:
    	return BEGIN;
    	break;
    	
		case 4:
    	return END;
    	break;
    	
		case 5:
    	return GO_TO;
    	break;
    	
		case 6:
    	return LOOP;
    	break;
    	
		case 7:
    	return READ;
    	break;
    
    	case 8:
    	return WRITE;
    	break;
    	
		case 9:
    	return VAR;
    	break;
    	
		case 10:
    	return ARROW;
    	break;
    	
		case 11:
    	return SEMICOLON;
    	break;
    	
		case 12:
    	return PLUS;
    	break;
    	
		case 13:
    	return ZERO;
    	break;
    	
		case 14:
    	return ONE;
    	break;
    	
		case 15:
    	return COLON;
    	break;
    	
		case 16:
    	return NAME;
    	break;
	}	
}


typedef struct palavras{
	struct palavras* ant;
	int tok;
	int line;
	int attr;
	int id;
	char* info;
	struct palavras* prox;
} Palavras;

/*
typedef struct sintatico {
	char* nome;
	char* lex;
	char* val;
} Sintatico;
*/
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

Linhas* go_to_l (Linhas* L, int num_lin){ //Vai pra linha num_lin
	if (L == NULL)
		printf("Linha inalcancavel");
	else if (L->id < num_lin)
		go_to_l(L->prox,num_lin);
	else if (L->id > num_lin)
		go_to_l(L->ant,num_lin);
	else if (L->id == num_lin)
		return (L);
}

//Palavras prox_palavra




















