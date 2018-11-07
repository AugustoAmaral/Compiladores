/*
-- PROGRAM
	-- PROGRAM NOME DE VARIAVEL ;
-- VAR | BEGIN
-/- VAR
	-- BLOCO DE VARIAVEIS
	-- NOME DE VARIAVEL : TIPO ; o END do VAR � o BEGIN
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

void Sin1(Linhas*);
void Sin2(Linhas*);
void Sin3(Linhas*);

int begins = 0;

void Sin1(Linhas* Line) // Verifica a linha program
{
	printf("\n\n DEBUG S1 \n\n");
	Linhas* L = Line;
	token token1;
	token token2;
	token token3;
	Palavras* P = L->info; //Recebe a palavra da primeira linha
	

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
					P = L->info;
				}
				else
				{
					printf("programa de uma linha s�? na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("Error, ';' esperado depois de NAME na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;

		default:
			printf("Error, esperado NAME depois de PROGRAM na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	
	default:
		printf("PROGRAM n�o encontrado na linha: %d Coluna: %d\n",P->line,P->id);
		system("PAUSE");
		exit(0);
		break;
	}
	
	token1 = conversor(P->tok);
	switch (token1)
	{
	case BEGIN:
		if (L->prox != NULL)
		{
			L = L->prox;
			begins = 1; //BEGINS = 1 nesse caso, n�o sei o que significa
			Sin3(L); //MANDA A LINHA ATUAL PARA SIN3 (A PARTIR DO BEGIN)
		}
		else
		{
			printf("Begin o que? nao tem nada depois na linha: %d Coluna: %d\n",P->line,P->id);
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
			printf("VAR o que? na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
		}
		
		break;
	default: //Aqui eu tenho que verificar se � end, pq se for, ele tem que passar n�..
		printf("Begin or Var n�o encontrado || End encontrado, fim do programa na linha: %d Coluna: %d\n",P->line,P->id);
		system("PAUSE");
		exit(0);
		break;
	}
}

void Sin3(Linhas* L)
{
	Palavras* P = L->info; //Recebe a palavra da primeira linha
	token token1 = conversor(P->tok);
	token token2, token3, token4, token5, token6;
	
	printf("\n\n DEBUG S3 \n\n");
	
	switch (token1)
	{
	/*case BEGIN:
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			P = L->info;
			token1 = conversor(P->tok);
		}
		else
		{
			printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
		}
		break;*/
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
				printf("END(s) esperado(s) na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
			}
			else
			{
				printf("Programa compilado com sucesso na linha: %d Coluna: %d\n",P->line,P->id);
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
					printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de GO_TO na linha: %d Coluna: %d\n",P->line,P->id);
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
					token1 = conversor(P->tok);
				}
				else
				{
					printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Esperado NAME depois de LOOP na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
			break;
		}

		/*//aqui � a merda
		begins++;
		if (L->prox != NULL)
		{
			L = L->prox;
			token1 = conversor(L->info->info);
		}
		else
		{
			printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
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
					printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de Name na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de READ na linha: %d Coluna: %d\n",P->line,P->id);
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
					printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de WRITE na linha: %d Coluna: %d\n",P->line,P->id);
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
						printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Esperado ';' depois de '0' na linha: %d Coluna: %d\n",P->line,P->id);
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
						printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
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
						P = P->prox; //L->info = L->info->prox;
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
								printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
								system("PAUSE");
								exit(0);
							}
							break;
						default:
							printf("Esperado ';' depois de '1' na linha: %d Coluna: %d\n",P->line,P->id);
							system("PAUSE");
							exit(0);
							break;
						}
						break;
					default:
						printf("Esperado '1' depois de '+' na linha: %d Coluna: %d\n",P->line,P->id);
						system("PAUSE");
						exit(0);
						break;
					}

					break;
				default:
					printf("Esperado ';' depois de '0' na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				printf("Esperado '0' ou NAME na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Esperado Atribuidor '<-' na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	default:
		printf("Fora da Regra sint�tica na linha: %d Coluna: %d\n",P->line,P->id);
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
	printf("\n\n DEBUG S2 \n\n");
	
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
						printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Error, ';' esperado depois do TIPO na linha: %d Coluna: %d\n",P->line,P->id);
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
						token1 = conversor(P->tok);
					}
					else
					{
						printf("END esperado na linha: %d Coluna: %d\n",P->line,P->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Error, ';' esperado depois do TIPO na linha: %d Coluna: %d\n",P->line,P->id);
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				printf("TIPO esperado depois de ':' na linha: %d Coluna: %d\n",P->line,P->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Error, ':' esperado depois de NAME na linha: %d Coluna: %d\n",P->line,P->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	default:
		printf("Begin or Name n�o encontrado na linha: %d Coluna: %d\n",P->line,P->id);
		system("PAUSE");
		exit(0);
		break;
	}
}
