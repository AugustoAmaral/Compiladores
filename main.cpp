#include "funcarquivos.cpp"

int main() {
	//char arq_nome[50];
	//printf("digite o nome do arquivo: ");
	//scanf("%s",arq_nome);
	char arq_nome[] = "teste.txt";
	pegarLinhas(arq_nome);
	return 0;
}

