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

void Sin1(Linhas*);
void Sin2(Linhas*);
void Sin3(Linhas*);

int begins = 0;

void Sin1(Linhas* Line) // Verifica a linha program
{
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
					printf("programa de uma linha só.\n");
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("Error, ';' esperado depois de NAME na linha: %d\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;

		default:
			printf("Error, esperado NAME depois de PROGRAM na linha: %d.\n",L->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	
	default:
		printf("PROGRAM não encontrado na linha: %d.\n",L->id);
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
			begins = 1; //BEGINS = 1 nesse caso, não sei o que significa
			Sin3(L->prox); //MANDA A LINHA ATUAL PARA SIN3 (A PARTIR DO BEGIN)
		}
		else
		{
			printf("Begin nada, nao tem nada depois da linha: %d\n",L->id);
			system("PAUSE");
			exit(0);
		}		
		break;
		
	case VAR:
		if (L->prox != NULL)
		{
			Sin2(L->prox);
		}
		else
		{
			printf("VAR o que, não tem nada depois da linha: %d\n",L->id);
			system("PAUSE");
			exit(0);
		}
		
		break;
	default: //Aqui eu tenho que verificar se é end, pq se for, ele tem que passar né..
		printf("Begin or Var não encontrado || End encontrado na linha: %d\n",L->id);
		system("PAUSE");
		exit(0);
		break;
	}
}

void Sin3(Linhas* L){
	Palavras* P = L->info; //Recebe a palavra da primeira linha
	token token1 = conversor(P->tok);
	token token2, token3, token4, token5, token6;
	switch (token1)
	{
	case END:
		begins--;
		if (L->prox != NULL)
			Sin3(L->prox);
		else
		{
			if (begins>0)
			{
				printf("END(s) esperado(s) na linha: %d (Ficou um Loop ou o begin aberto)\n",L->id);
				system("PAUSE");
				exit(0);
			}
			else
			{
				printf("Programa compilado com sucesso.\n");
				system("PAUSE");
				exit(0);
			}
		}
		break;
	case GO_TO:		
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
					Sin3(L->prox);
				else
				{
					printf("END esperado depois da linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de GO_TO na linha: %d.\n",L->id);
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
					Sin3(L->prox);
				}
				else
				{
					printf("END esperado depois da linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Esperado NAME depois de LOOP na linha: %d.\n",L->id);
			system("PAUSE");
			exit(0);
			break;
		}
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
					Sin3(L->prox);
				else
				{
					printf("END esperado depois da linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de Name na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de READ na linha: %d.\n",L->id);
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
					Sin3(L->prox);
				else
				{
					printf("END esperado depois da linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
				}
				break;
			default:
				printf("';' esperado depois de NAME na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("NAME esperado depois de WRITE na linha: %d.\n",L->id);
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
						Sin3(L->prox);
					else
					{
						printf("END esperado depois da linha: %d.\n",L->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Esperado ';' depois de '0' na linha: %d.\n",L->id);
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
						Sin3(L->prox);
					else
					{
						printf("END esperado depois da linha: %d.\n",L->id);
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
								Sin3(L->prox);
							else
							{
								printf("END esperado depois da linha: %d.\n",L->id);
								system("PAUSE");
								exit(0);
							}
							break;
						default:
							printf("Esperado ';' depois de '1' na linha: %d.\n",L->id);
							system("PAUSE");
							exit(0);
							break;
						}
						break;
					default:
						printf("Esperado '1' depois de '+' na linha: %d.\n",L->id);
						system("PAUSE");
						exit(0);
						break;
					}

					break;
				default:
					printf("Esperado ';' depois de '0' na linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				printf("Esperado '0' ou NAME na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Esperado Atribuidor '<-' na linha: %d.\n",L->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	default:
		printf("Fora da Regra sintatica na linha: %d.\n",L->id);
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
		Sin3(L->prox); //Já que no sin3 ele não reconhece begin, tem que mandar por aqui
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
						Sin2(L->prox);
					else
					{
						printf("END esperado depois da linha: %d.\n",L->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Error, ';' esperado depois do TIPO na linha: %d.\n",L->id);
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
						Sin2(L->prox);
					else
					{
						printf("END esperado depois da linha: %d.\n",L->id);
						system("PAUSE");
						exit(0);
					}
					break;
				default:
					printf("Error, ';' esperado depois do TIPO na linha: %d.\n",L->id);
					system("PAUSE");
					exit(0);
					break;
				}
				break;
			default:
				printf("TIPO esperado depois de ':' na linha: %d.\n",L->id);
				system("PAUSE");
				exit(0);
				break;
			}
			break;
		default:
			printf("Error, ':' esperado depois de NAME na linha: %d.\n",L->id);
			system("PAUSE");
			exit(0);
			break;
		}
		break;
	default:
		printf("Begin or Name não encontrado na linha: %d.\n",L->id);
		system("PAUSE");
		exit(0);
		break;
	}
}
