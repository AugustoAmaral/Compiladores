#include "sintatico.cpp"
#include <windows.h>
//#include "structure.cpp"

int main() {
	//char arq_nome[50];
	//printf("digite o nome do arquivo: ");
	//scanf("%s",arq_nome);
	char arq_nome[] = "teste.txt";
	Linhas* l = pegarLinhas(arq_nome);
	Linhas* line = l;
	while (l->prox != NULL){
		identificarPalavrasReservadas(l->info,l->id);
		//printarLinha(l->info);
		l = l->prox;
	}
	l = line;
	//printf("TOKEN %s",conversor(2));
	Sin1(l);
	//sintatico
	/*char testa[] = {"PALAVRATESTE"};
	char tests[] = {"palavrateste"};
	char testd[] = {"PaLaVrAtEsTe"};
	printf("1:%d | 0:%d | 0:%d",verificarId(testa),verificarId(tests),verificarId(testd));*/
	system("PAUSE");
		
	return 0;
}

