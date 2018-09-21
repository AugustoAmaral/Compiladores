#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.cpp"
#define tam_palavras_reservadas 16
const char* const palavras_reservadas[] = {"program","integer","real","begin","end","goto","loop","read","write","var","<-",";","+","0","1",":"}; //13 palavras reservadas


void identificarPalavrasReservadas(Palavras* linha) {
	Palavras* p = linha;
	while (p != NULL) {
		for (int i = 0; i<tam_palavras_reservadas; i++) //VERIFICA SE A PALAVRA ATUAL ï¿½ RESERVADA
			if (strcmp(p->info, palavras_reservadas[i]) == 0)
				printf("palavra reservada encontrada: %s \n", p->info);
		//printf("Palavra: %s ",p->info); DEBUG ONLY
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
	
	char* palavra = strtok(linha, "\t; ()\n");
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
		palavra = strtok(NULL, "\t; ()");
	}
	
	return palavra_retornada;
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
			
			l->info = (Palavras*) malloc (sizeof(Palavras)); // ALOCA ESPAÃ‡O PARA A INFO DA LINHA
			l->info = pegarPalavras(strtok(linha,"\n"));
			//l->info = strtok(linha,"\n"); //&l->info = linha; //ARMAZENA A LINHA
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
