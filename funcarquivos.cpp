#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void pegarLinhas(char* nome_do_arquivo) {
	char linha[200];
	FILE *arq;
	arq = fopen(nome_do_arquivo, "r");
	if (arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo.\n");
	else
		while ((fgets(linha, sizeof(linha), arq)) != NULL)//VAI GUARDAR AS LINHAS DO CODIGO EM UM VETOR DE LINHAS
			identificarPalavrasReservadas(linha);
	fclose(arq);
}

