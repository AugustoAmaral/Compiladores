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
	token token1 = conversor(L->info->info);
	token token2;
	token token3;
	switch (token1)
	{
	case PROGRAM:

		sin->lex = lexemas_reservadas[L->info->tok];
		sin->val = tokens_reservadas[L->info->tok];
		token2 = conversor(L->info->prox);
		
		switch (token2)
		{
		case NAME:
			sin->nome = L->info->prox->info;
			token3 = conversor(L->info->prox->prox);
			switch (token3)
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
	token1 = conversor(L->info->info);
	switch (token1)
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
	token token1 = conversor(L->info->info);
	token token2, token3, token4, token5, token6;

	switch (token1)
	{
		//begin acho que ta errado//
	case BEGIN:
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			token1 = conversor(L->info->info);
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
			token1 = conversor(L->info->info);
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
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case NAME:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					token1 = conversor(L->info->info);
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
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case NAME:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					token1 = conversor(L->info->info);
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
			prinf("Esperado NAME depois de LOOP");
			system("PAUSE");
			exit(0);
			break;
		}
		//aqui é a merda//
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			token1 = conversor(L->info->info);
		}
		else
		{
			prinf("END esperado");
			system("PAUSE");
			exit(0);
		}
		break;
	case READ:
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case NAME:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					token1 = conversor(L->info->info);
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
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case NAME:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					token1 = conversor(L->info->info);
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
			prinf("NAME esperado depois de WRITE");
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	case NAME:
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case ARROW:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case ZERO:
				L->info = L->info->prox;
				token4 = conversor(L->info->info);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						token1 = conversor(L->info->info);
					}
					else
					{
						prinf("END esperado");
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					prinf("Esperado ';' depois de '0'");
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			case NAME:
				L->info = L->info->prox;
				token4 = conversor(L->info->info);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						token1 = conversor(L->info->info);
					}
					else
					{
						prinf("END esperado");
						system("PAUSE");
						exit(0);
					}
					break;
				case PLUS:
					L->info = L->info->prox;
					token5 = conversor(L->info->info);
					switch (token5)
					{
					case ONE:
						L->info = L->info->prox;
						token6 = conversor(L->info->info);
						switch (token6)
						{
						case SEMICOLON:
							if (L->prox != NULL)
							{
								L = L->prox;
								token1 = conversor(L->info->info);
							}
							else
							{
								prinf("END esperado");
								system("PAUSE");
								exit(0);
							}
							break;
						default:
							prinf("Esperado ';' depois de '1'");
							system("PAUSE");
							exit(0);
							break;
						}
						break;
					default:
						prinf("Esperado '1' depois de '+'");
						system("PAUSE");
						exit(0);
						break;
					}

					break;
				default:
					prinf("Esperado ';' depois de '0'");
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				prinf("Esperado '0' ou NAME");
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			prinf("Esperado Atribuidor '<-'");
			system("PAUSE");
			exit(0);
			break;
		}
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
	token token1 = conversor(L->info->info);
	token token2;
	token token3;
	token token4;
	switch (token1)
	{
	case BEGIN:
		begins++;
		Sin3(L, numlin, sin);
		break;
	case NAME:
		sin->nome = L->info->info;
		L->info = L->info->prox;
		token2 = conversor(L->info->info);
		switch (token2)
		{
		case COLON:
			L->info = L->info->prox;
			token3 = conversor(L->info->info);
			switch (token3)
			{
			case INTEGER:
				sin->lex = lexemas_reservadas[L->info->tok];
				sin->val = tokens_reservadas[L->info->tok];
				L->info = L->info->prox;
				token4 = conversor(L->info->info);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						token1 = conversor(L->info->info);
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
				token4 = conversor(L->info->info);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						token1 = conversor(L->info->info);
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