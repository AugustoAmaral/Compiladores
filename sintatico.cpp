/*
-- PROGRAM
	-- PROGRAM NOME DE VARIAVEL ;
-- VAR | BEGIN
-/- VAR
	-- BLOCO DE VARIAVEIS
	-- NOME DE VARIAVEL : TIPO ; o END do VAR é o BEGIN
-/-BEGIN
	-- BLOCOS DE COMANDO
-- COMANDOS
	-- NOME <- 0 ;
	-- NOME <- NOME + 1 ;
	-- NOME <- NOME ;
	-- GOTO NOME ;
	-- LOOP -/- BLOCO DE COMANDOS -/- END ;
	-- READ ( NOME ) ;
	-- WRITE ( NOME ) ;
*/

#include "funcarquivos.cpp"

int begins = 0;

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
	NUL,
	VARIAVEL
};

token conversor(char* info)
{
	if (info == "program") return PROGRAM;
	else if (info == "integer") return INTEGER;
	else if (info == "real") return REAL;
	else if (info == "begin") return BEGIN;
	else if (info == "goto") return GO_TO;
	else if (info == "loop") return LOOP;
	else if (info == "read") return READ;
	else if (info == "write") return WRITE;
	else if (info == "var") return VAR;
	else if (info == "<-") return ARROW;
	else if (info == ";") return SEMICOLON;
	else if (info == "+") return PLUS;
	else if (info == "0") return ZERO;
	else if (info == "1") return ONE;
	else if (info == ":") return COLON;
	else if (info == "NULL") return NUL;
}

void verificadorSintatico(Linhas* L, int numlin, Sintatico* sin)
{
	token toke = conversor(token->info);
	token ttoke;

	switch (toke)
	{
		case PROGRAM:
			
			sin->lex = lexemas_reservadas[token->tok];
			sin->val = tokens_reservadas[token->tok];
			ttoke = conversor(token->prox->info);
			if (ttoke == 16)
			{
				sin->nome = token->prox->info;
				if (/*checar ponto e virgula*/)
				{

				}
				else
				{
					prinf("Error, ';' esperado depois de Nome",);
				}
			}
			else
			{
				prinf("Error, esperado nome depois de program foi encontrado %d", tokke);
			}
			//verificadorSintatico(token->prox, numlin, sin);
			//add tabela sintatico
			break;
		case INTEGER:
			break;
		case REAL:
			break;
		case BEGIN:
			begins++;
			break;
		case END:
			begins--;
			break;
		case GO_TO:
			break;
		case LOOP:
			break;
		case READ:
			break;
		case WRITE:
			break;
		case VAR:
			break;
		case ARROW:
			break;
		case SEMICOLON:
			break;
		case PLUS:
			break;
		case ZERO:
			break;
		case ONE:
			break;
		case COLON:
			break;
		case NUL:
			break;

			break;
		default:
			printf("Error");
	}

}




/*
enum class Type: int
{
	{"program", "integer", "real", "begin", "end", "goto", "loop", "read", "write", "var", "<-", ";", "+", "0", "1", ":", "NULL"}
};
*/