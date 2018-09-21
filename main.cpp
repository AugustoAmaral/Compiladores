#include "funcarquivos.cpp"
//#include "structure.cpp"

int main() {
	//char arq_nome[50];
	//printf("digite o nome do arquivo: ");
	//scanf("%s",arq_nome);
	char arq_nome[] = "teste.txt";
	Linhas* l = pegarLinhas(arq_nome);
	while (l->prox != NULL){
		identificarPalavrasReservadas(l->info,l->id);
		l = l->prox;
	}
		
	return 0;
}

