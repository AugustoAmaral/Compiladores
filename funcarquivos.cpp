#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.cpp"
#define tam_palavras_reservadas 16
const char* const lexemas_reservadas[] = {"program","integer","real","begin","end","goto","loop","read","write","var","<-",";","+","0","1",":"}; //16 palavras reservadas
const char* const tokens_reservadas[] = {"start","type","type","delimiter","delimiter","goto","loop","read","write","var","attr","point","operator","zero","one","point"};
const char* const atributo_reservadas[] = {"SUM","0","1","-"};

void identificarPalavrasReservadas(Palavras* linha,int num_lin) {
	Palavras* p = linha;
	while (p->prox != NULL) {
		for (int i = 0; i<tam_palavras_reservadas; i++) //VERIFICA SE A PALAVRA ATUAL ï¿½ RESERVADA
			if (strcmp(p->info, lexemas_reservadas[i]) == 0){
				printf("|Lin: %d  \t|Col: %d  \t|Lex: %s  \t|Tok: %s\t|",num_lin,p->id,lexemas_reservadas[i],tokens_reservadas[i]);
				if (i>=12)
				printf("Attr: %s\t|\n",atributo_reservadas[i-12]);
				else
				printf("attr: -\t|\n");
			}
		p = p->prox;
	}

}

Palavras* pegarPalavras(char* linha){
	
	Palavras* p = (Palavras*) malloc (sizeof(Palavras));
	p->ant=p->prox=NULL; //inicia estrutura de palavras
	p->info=NULL;
	p->id=1;
	Palavras* palavra_retornada = p;
	int contador=1;
	
	char* palavra = strtok(linha, "\t ()\n");
	while (palavra != NULL) {
		//define a palavra e define a coluna
		p->info = (char*) malloc (sizeof(palavra));
		strcpy(p->info,palavra);
		//printf("%s ",p->info); //DEBUG ONLY
		p->id = contador;
		
		//aloca uma proxima palavra e avança a estrutura
		p->prox = (Palavras*) malloc (sizeof(Palavras));
		Palavras* temp = p;
		p=p->prox;
		p->ant=temp;
		p->prox=NULL;
		//passa para a proxima palavra
		palavra = strtok(NULL, "\t ()\n");
		contador++;
	}
	return (palavra_retornada);
}

Linhas* pegarLinhas(char* nome_do_arquivo) {
	char linha[200];

	//INICIANDO A ESTRUTURA DE LINHAS
	Linhas* l = (Linhas*) malloc (sizeof(Linhas)); // Cria uma estrutura de linhas genéricas
	l->ant=l->prox= NULL; //inicia a estrutura
	l->info=NULL; // mesma coisa
	l->id=1; // msm coisa
	Linhas* linha_retornada = l; // é o que retorna obviamente
	int contador=1;
	
	FILE *arq;
	arq = fopen(nome_do_arquivo, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo.\n");
	else
		while ((fgets(linha, sizeof(linha), arq)) != NULL){//VAI GUARDAR AS LINHAS DO CODIGO EM UM VETOR DE LINHAS
			
			//printf("\n %s \n",linha);
			l->info = pegarPalavras(linha);
			//printf("\n %s \n",linha);
			l->id = contador; // DEFINE A LINHA DO PROGRAMA
						
			l->prox = (Linhas*) malloc (sizeof(Linhas)); // CRIA UMA NOVA ESTRUTURA PARA UMA NOVA LINHA
			Linhas* temp = l; // SALVA O ENDEREÃ‡O DA LINHA ATUAL
			l= l->prox; // DEFINE A PROXIMA LINHA COMO LINHA ATUAL
			l->ant = temp; //APONTA PARA A LINHA ANTERIOR
			l->prox = NULL; // PROXIMO VAI APONTAR PRA NULL
			contador++; // CONTINUA CONTADOR
			//identificarPalavrasReservadas(linha);
			//printf("\n");
		}
	fclose(arq);
	
	return linha_retornada;
}

void reescreverLinha(char* linha) {

}
