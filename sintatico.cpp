/*
-- PROGRAM
	-- PROGRAM NOME DE VARIAVEL ;
-- VAR | BEGIN
-/- VAR
	-- BLOCO DE VARIAVEIS
	-- NOME DE VARIAVEL : TIPO ; o END do VAR é o BEGIN
-/-BEGIN
	-- BLOCOS DE COMANDO
-- /*COMANDOS
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
	NAME
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
	else if (info == "name") return NAME;
}

void Sin1(Linhas* L, int numlin, Sintatico* sin)
{
	token toke = conversor(L->info->info);
	token ttoke;
	token ttokke;
	switch (toke)
	{
	case PROGRAM:

		sin->lex = lexemas_reservadas[L->info->tok];
		sin->val = tokens_reservadas[L->info->tok];
		ttoke = conversor(L->info->prox);
		
		switch (ttoke)
		{
		case NAME:
			sin->nome = L->info->prox->info;
			ttokke = conversor(L->info->prox->prox);
			switch (ttokke)
			{
			
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					//toke = conversor(L->info->info);
				}
				else
				{
					prinf("END esperado");
					system("PAUSE");
					exit(0);
				}
				break;
			
			default:
				prinf("Error, ';' esperado depois de NAME");
				system("PAUSE");
				exit(0);
				break;
			}
			break;

		default:
			prinf("Error, esperado NAME depois de PROGRAM");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	
	default:
		prinf("PROGRAM não encontrado");
		system("PAUSE");
		exit(0);
		break;
	}
	toke = conversor(L->info->info);
	switch (toke)
	{
	case BEGIN:
		if (L->prox != NULL)
		{
			L = L->prox;
			//toke = conversor(L->info->info);
			begins++;
			Sin3(L, numlin, sin);
		}
		else
		{
			prinf("END esperado");
			system("PAUSE");
			exit(0);
		}
		
		break;
	case VAR:
		if (L->prox != NULL)
		{
			L = L->prox;
			//toke = conversor(L->info->info);
			Sin2(L, numlin, sin);
		}
		else
		{
			prinf("END esperado");
			system("PAUSE");
			exit(0);
		}
		
		break;
	default:
		prinf("Begin\Var não encontrado");
		system("PAUSE");
		exit(0);
		break;
	}
}

void Sin3(Linhas* L, int numlin, Sintatico* sin)
{
	token toke = conversor(L->info->info);
	token ttoke;
	token ttokke;
	token ttoken;

	switch (toke)
	{
		//begin acho que ta errado//
	case BEGIN:
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			toke = conversor(L->info->info);
		}
		else
		{
			prinf("END esperado");
				system("PAUSE");
				exit(0);
		}
		break;
	case END:
		begins--;
		if (L->prox != NULL)
		{
			L = L->prox;
			toke = conversor(L->info->info);
		}
		else
		{
			if (begins>0)
			{
				prinf("END(s) esperado(s)");
				system("PAUSE");
				exit(0);
			}
			else
			{
				prinf("Programa compilado com sucesso");
				system("PAUSE");
				exit(0);
			}
		}
		break;
	case GO_TO:
		ttoke = conversor(L->info->info);
		switch (ttoke)
		{
		case NAME:
			L->info = L->info->prox;
			ttokke = conversor(L->info->info);
			switch (ttokke)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					toke = conversor(L->info->info);
				}
				else
				{
					prinf("END esperado");
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				prinf("';' esperado depois de NAME");
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			prinf("NAME esperado depois de GO_TO");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	case LOOP:
		//aqui é a merda//
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			toke = conversor(L->info->info);
		}
		else
		{
			prinf("END esperado");
			system("PAUSE");
			exit(0);
		}
		break;
	case READ:
		ttoke = conversor(L->info->info);
		switch (ttoke)
		{
		case NAME:
			L->info = L->info->prox;
			ttokke = conversor(L->info->info);
			switch (ttokke)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					toke = conversor(L->info->info);
				}
				else
				{
					prinf("END esperado");
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				prinf("';' esperado depois de Name");
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			prinf("NAME esperado depois de READ");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	case WRITE:
		ttoke = conversor(L->info->info);
		switch (ttoke)
		{
		case NAME:
			L->info = L->info->prox;
			ttokke = conversor(L->info->info);
			switch (ttokke)
			{
			case SEMICOLON:
				L = L->prox;
				toke = conversor(L->info->info);
				break;
			default:
				prinf("';' esperado depois de NAME");
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			prinf("NAME esperado depois de WRITE");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	case NAME:
		break;
	default:
		prinf("Fora da Regra sintática");
		system("PAUSE");
		exit(0);
		break;
	}
	/*COMANDOS
	-- NOME <- 0 ;
	-- NOME <- NOME + 1 ;
	-- NOME <- NOME ;
	-- GOTO NOME ;
	-- LOOP -/- BLOCO DE COMANDOS -/- END ;
	-- READ ( NOME ) ;
	-- WRITE ( NOME ) ;
	*/
}

void Sin2(Linhas* L, int numlin, Sintatico* sin)
{
	token toke = conversor(L->info->info);
	token ttoke;
	token ttokke;
	token ttoken;
	switch (toke)
	{
	case BEGIN:
		begins++;
		Sin3(L, numlin, sin);
		break;
	case NAME:
		sin->nome = L->info->info;
		ttoke = conversor(L->info->prox->info);
		switch (ttoke)
		{
		case COLON:
			L->info = L->info->prox;
			ttokke = conversor(L->info->prox->info);
			switch (ttokke)
			{
			case INTEGER:
				sin->lex = lexemas_reservadas[L->info->tok];
				sin->val = tokens_reservadas[L->info->tok];
				L->info = L->info->prox;
				ttoken = conversor(L->info->prox->info);
				switch (ttoken)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						toke = conversor(L->info->info);
					}
					else
					{
						prinf("END esperado");
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					prinf("Error, ';' esperado depois do TIPO", );
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			case REAL:
				sin->lex = lexemas_reservadas[L->info->tok];
				sin->val = tokens_reservadas[L->info->tok];
				L->info = L->info->prox;
				ttoken = conversor(L->info->prox->info);
				switch (ttoken)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						toke = conversor(L->info->info);
					}
					else
					{
						prinf("END esperado");
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					prinf("Error, ';' esperado depois do TIPO", );
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				prinf("TIPO esperado depois de ':'");
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			prinf("Error, ':' esperado depois de NAME");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	default:
		prinf("Begin\Name não encontrado");
		system("PAUSE");
		exit(0);
		break;
	}
}

/*
enum class Type: int
{
	{"program", "integer", "real", "begin", "end", "goto", "loop", "read", "write", "var", "<-", ";", "+", "0", "1", ":", "NULL"}
};
*/