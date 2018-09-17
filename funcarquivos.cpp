#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.cpp"
#define tam_palavras_reservadas 12
const char* const palavras_reservadas[] = { "+","-","*","/","<-","loop","end","goto","read","write","begin","int" }; //13 palavras reservadas


void identificarPalavrasReservadas(char* linha) {
	printf("\n");
	char* palavra = strtok(linha, "\t; ()\n");
	while (palavra != NULL) {
		for (int i = 0; i<tam_palavras_reservadas; i++) //VERIFICA SE A PALAVRA ATUAL � RESERVADA
			if (strcmp(palavra, palavras_reservadas[i]) == 0)
				printf("palavra reservada encontrada: %s \n", palavra);
				
		palavra = strtok(NULL, "\t; ()\n");
	}

}

Linhas* pegarLinhas(char* nome_do_arquivo) {
	char linha[200];

	//INICIANDO A ESTRUTURA DE LINHAS
	Linhas* l = (Linhas*) malloc (sizeof(Linhas));
	l->ant=l->prox= NULL;
	l->info=NULL;
	l->id=1;
	Linhas* linha_retornada = l;
	int contador=1;
	
	FILE *arq;
	arq = fopen(nome_do_arquivo, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo.\n");
	else
		while ((fgets(linha, sizeof(linha), arq)) != NULL){//VAI GUARDAR AS LINHAS DO CODIGO EM UM VETOR DE LINHAS
			
			l->info = (char*) malloc (sizeof(linha)); // ALOCA ESPAÇO PARA A INFO DA LINHA
			strcpy(l->info,linha); //&l->info = linha; //ARMAZENA A LINHA
			l->id = contador; // DEFINE A LINHA DO PROGRAMA

						
			l->prox = (Linhas*) malloc (sizeof(Linhas)); // CRIA UMA NOVA ESTRUTURA PARA UMA NOVA LINHA
			Linhas* temp = l; // SALVA O ENDEREÇO DA LINHA ATUAL
			l= l->prox; // DEFINE A PROXIMA LINHA COMO LINHA ATUAL
			l->ant = temp; //APONTA PARA A LINHA ANTERIOR
			l->prox = NULL; // PROXIMO VAI APONTAR PRA NULL
			contador++; // CONTINUA CONTADOR
			//identificarPalavrasReservadas(linha);
			printf("\n");
		}
	fclose(arq);
	
	return linha_retornada;
}

void reescreverLinha(char* linha) {

}
