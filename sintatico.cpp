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

void Sin1(Linhas* Line) // Verifica a linha program
{
	Linhas* L = Line;
	token token1;
	token token2;
	token token3;
	Palavra* P = L->info; //Recebe a palavra da primeira linha
	
	token1 = conversor(P->tok); //primeira palavra
	P = P->prox;
	token2 = conversor(P->tok); //Segunda palavra
	P = P->prox;
	token3 = conversor(P->tok); //Terceira palavra
	
	switch (token1)
	{
	case PROGRAM:		
		switch (token2)
		{
		case NAME:
			switch (token3)
			{			
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
				}
				else
				{
					prinf("programa de uma linha só?");
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
			begins = 1; //BEGINS = 1 nesse caso, não sei o que significa
			Sin3(L); //MANDA A LINHA ATUAL PARA SIN3 (A PARTIR DO BEGIN)
		}
		else
		{
			prinf("Begin o que? nao tem nada depois");
			system("PAUSE");
			exit(0);
		}		
		break;
		
	case VAR:
		if (L->prox != NULL)
		{
			L = L->prox;
			Sin2(L);
		}
		else
		{
			prinf("VAR o que?");
			system("PAUSE");
			exit(0);
		}
		
		break;
	default: //Aqui eu tenho que verificar se é end, pq se for, ele tem que passar né..
		prinf("Begin\Var não encontrado || End encontrado, fim do programa");
		system("PAUSE");
		exit(0);
		break;
	}
}

void Sin3(Linhas* L)
{
	Palavra* P = L->info; //Recebe a palavra da primeira linha
	token token1 = conversor(P->tok);
	token token2, token3, token4, token5, token6;

	switch (token1)
	{
	case BEGIN:
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			P = L->info;
			token1 = conversor(P->tok);
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
			P = L->info;
			token1 = conversor(P->tok);
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
		/*L = L->prox;
		P = L->info;
		token1 = conversor(P->tok);*/
		
		P = P->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case NAME:
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					P = L->info;
					token1 = conversor(P->tok);
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
		P = P->prox; //L->info = L->info->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case NAME:
			P = P->prox; //L->info = L->info->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					begins++; //Como o loop precisa de um end, eu vou contar aqui.
					L = L->prox;
					P = L->info;
					token1 = conversor(P->info);
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

		/*//aqui é a merda
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
		}*/
		break;
	case READ:
		P = P->prox; //L->info = L->info->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case NAME:
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					P = L->info;
					token1 = conversor(P->tok);
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
		P = P->prox; //L->info = L->info->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case NAME:
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					L = L->prox;
					P = L->info;
					token1 = conversor(P->tok);
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
		P = P->prox; //L->info = L->info->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case ARROW:
			P = P->prox; //L->info = L->info->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case ZERO:
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						P = L->info;
						token1 = conversor(P->tok);
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
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						P = L->info;
						token1 = conversor(P->tok);
					}
					else
					{
						prinf("END esperado");
						system("PAUSE");
						exit(0);
					}
					break;
				case PLUS:
					P = P->prox; //L->info = L->info->prox;
					token5 = conversor(P->tok);
					switch (token5)
					{
					case ONE:
						P = P->prox //L->info = L->info->prox;
						token6 = conversor(P->tok);
						switch (token6)
						{
						case SEMICOLON:
							if (L->prox != NULL)
							{
								L = L->prox;
								P = L->info;
								token1 = conversor(P->tok);
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

void Sin2(Linhas* L)
{
	Palavras* P = L->info;
	token token1 = conversor(P->tok);
	token token2;
	token token3;
	token token4;
	switch (token1)
	{
	case BEGIN:
		begins = 1; //Primeiro Begin
		Sin3(L);
		break;
	case NAME:
		P = P->prox; //L->info = L->info->prox;
		token2 = conversor(P->tok);
		switch (token2)
		{
		case COLON:
			P = P->prox; //L->info = L->info->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case INTEGER:
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						P = L->info;
						token1 = conversor(P->tok);
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
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					if (L->prox != NULL)
					{
						L = L->prox;
						P = L->info;
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
