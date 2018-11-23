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
#include <windows.h>
#include "funcarquivos.cpp"

void Sin1(Linhas*,Semantico*);
void Sin2(Linhas*,Semantico*);
void Sin3(Linhas*,Semantico*);

int begins = 0;

void printVar(Semantico* S){
	printf("\n%p, %s, %d, %d, %p\n",(void*)S,S->nome,S->type,S->val,(void*)S->prox);
	if (S->prox != NULL)
		printVar(S->prox);
}

void addVar (char* name, token tipo,Semantico* S,int l){
	//printf("recebi: %s \t/ tok: %d \t/ S->nome: %s \t/ S->tokem: %d.\n",name,tipo,S->nome,S->type);
	if (strcmp(name,S->nome) == 0){
		printf("Nome de variavel ja encontrado na linha %d.\n",l);
		exit(0);
	}
	else
	if (S->prox != NULL)		
			addVar (name,tipo,S->prox,l); //VAI ATÉ A ULTIMA VARIAVEL EXISTENTE
	else{
		S->prox = (Semantico*) malloc (sizeof(Semantico)); //ALOCA UM ESPAÇO PRA UMA NOVA VARIAVEL
		S = S->prox; //VAI PRO ESPAÇO DA PROXIMA
		strcpy(S->nome,name);
		S->prox = NULL;
		S->type = tipo;
		S->val = 0; //ESTOU SUPONDO QUE O COMPILADOR JA INICIA A VARIAVEL LIMPA
	}
}

int checkVar (char* name, token tipo, int valor, Semantico* S,int cont,int linha){
	cont=1;
	if (S != NULL){
		//printf("%s <-> %s  //  %d <-> %d  //  %d <-> %d  //  %p -> %p // CONT: %d\n",S->nome,name,S->val,valor,S->type,tipo,(void*)S,(void*)S->prox,cont);
		if ( (strcmp(name,S->nome) == 0) && (S->type == 0)){
			printf("Variavel citada na linha %d e do tipo program, qual seu problema?\n",linha);
			exit(0);
		}
		else
		if (strcmp(S->nome,name) == 0){ //PROCURA O NOME DA VARIAVEL
			if (S->type == tipo){
				if (valor == -1)
					S->val = S->val;
				else
					S->val = valor; //VERIFICAR COM SANYA SE EU TENHO QUE SALVAR OS VALORES PORQUE SE PRECISAR EU VOU TER QUE CRIAR UMA FUNCAO PRA PEGAR O VALOR DA VARIAVEL NO CASO DE ATRIBUIÇÃO DE X <- Y OU ALGO ASSIM
				cont = 0;
				return 0;
			}
			else{
				printf("Atribuicao de variaveis de tipos incorretos na linha %d ao atribuir a variavel %s a um tipo diferente.\n",linha,name);
				exit(0);
			}
		}else
			cont = checkVar(name,tipo,valor,S->prox,cont,linha);}
	if (cont==1){ //COMO A FUNCAO É RECURSIVA, ELA SÓ VAI PRINTAR ISSO SE NAO ENCONTRAR NENHUMA VARIAVEL
		printf("Nao foi encontrado nenhuma variavel com o nome %s na linha %d.\n",name,linha);
		exit(0);
	}
}

token getToken (Semantico* S,char* name){
	if (S != NULL)
		if (strcmp(S->nome,name) == 0) //PROCURA O NOME DA VARIAVEL
			return S->type;
		else
			return (getToken(S->prox,name));
}


void Sin1(Linhas* Line,Semantico* S) // Verifica a linha program
{
	Linhas* L = Line;
	token token1;
	token token2;
	token token3;
	Palavras* P = L->info; //Recebe a palavra da primeira linha
	char tmp_name[40]; //Isso aqui que vai guardar o nome da variavel.
	token tmp_tipo;
	int tmp_valor;
	

	token1 = conversor(P->tok); //primeira palavra
	P = P->prox;
	token2 = conversor(P->tok); //Segunda palavra
	strcpy(tmp_name,P->info);//Vai pegar o nome
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
					strcpy(S->nome,tmp_name);
					S->type = PROGRAM;
					S->val = 0;
					S->prox = NULL;
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
			Sin3(L->prox,S); //MANDA A LINHA ATUAL PARA SIN3 (A PARTIR DO BEGIN)
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
			Sin2(L->prox,S);
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

void Sin3(Linhas* L,Semantico* S){
	if (begins <= 0){
		printf("Foi encontrado informacao depois do ultimo END na linha %d",L->id);
		exit(0);
	}
	//printVar(S);
	Palavras* P = L->info; //Recebe a palavra da primeira linha
	token token1 = conversor(P->tok);
	token token2, token3, token4, token5, token6;
	char tmp_name[40],tmp_name_aux[40]; //Isso aqui que vai guardar o nome da variavel.
	token tmp_tipo,tmp_tipo_aux;
	switch (token1)
	{
	case END:
		begins--;
		if (L->prox != NULL)
			Sin3(L->prox,S);
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
			strcpy(tmp_name,P->info);
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				checkVar(tmp_name,INTEGER,-1,S,0,L->id);
				if (L->prox != NULL)
					Sin3(L->prox,S);
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
			strcpy(tmp_name,P->info);
			P = P->prox; //L->info = L->info->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				if (L->prox != NULL)
				{
					checkVar(tmp_name,INTEGER,-1,S,0,L->id); //COMO EU NAO SEI O QUE O USUARIO VAI DIGITAR, MANDEI INT MESMO
					begins++; //Como o loop precisa de um end, eu vou contar aqui.
					Sin3(L->prox,S);
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
			strcpy(tmp_name,P->info);
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				checkVar(tmp_name,getToken(S,tmp_name),-1,S,0,L->id);
				if (L->prox != NULL)
					Sin3(L->prox,S);
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
			strcpy(tmp_name,P->info);
			P = P->prox;
			token3 = conversor(P->tok);
			switch (token3)
			{
			case SEMICOLON:
				checkVar(tmp_name,getToken(S,tmp_name),-1,S,0,L->id);
				if (L->prox != NULL)
					Sin3(L->prox,S);
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
		tmp_tipo = getToken(S,P->info);
		strcpy(tmp_name,P->info);
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
					checkVar(tmp_name,getToken(S,tmp_name),0,S,0,L->id);
					if (L->prox != NULL)
						Sin3(L->prox,S);
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
				strcpy(tmp_name_aux,P->info);
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					checkVar(tmp_name_aux,tmp_tipo,-1,S,0,L->id);
					if (L->prox != NULL)
						Sin3(L->prox,S);
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
						checkVar(tmp_name_aux,tmp_tipo,1,S,0,L->id);
						P = P->prox; //L->info = L->info->prox;
						token6 = conversor(P->tok);
						switch (token6)
						{
						case SEMICOLON:
							if (L->prox != NULL)
								Sin3(L->prox,S);
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

void Sin2(Linhas* L,Semantico* S)
{
	Palavras* P = L->info;
	token token1 = conversor(P->tok);
	token token2;
	token token3;
	token token4;
	char tmp_name[40]; //Isso aqui que vai guardar o nome da variavel.
	token tmp_tipo;
	
	switch (token1)
	{
	case BEGIN:
		begins = 1; //Primeiro Begin
		Sin3(L->prox,S); //Já que no sin3 ele não reconhece begin, tem que mandar por aqui
		break;
	case NAME:
		strcpy(tmp_name,P->info);
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
				tmp_tipo = INTEGER;
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					addVar(tmp_name,INTEGER,S,P->line);
					if (L->prox != NULL){
						Sin2(L->prox,S);
					}
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
				tmp_tipo = REAL;
				P = P->prox; //L->info = L->info->prox;
				token4 = conversor(P->tok);
				switch (token4)
				{
				case SEMICOLON:
					addVar(tmp_name,REAL,S,P->line);
					if (L->prox != NULL){
						Sin2(L->prox,S);
					}
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
