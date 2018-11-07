#include "structure.cpp"


void identificarPalavrasReservadas(Palavras* linha,int num_lin) {
	Palavras* p = linha;
	int is_token = 0; //Vai servir pra identificar palavras maiusculas
	int i = 0; //CONTADOR
	while (p->prox != NULL) {
		for (i = 0; i<(tam_palavras_reservadas-1); i++) //VERIFICA SE A PALAVRA ATUAL ï¿½ RESERVADA
			if (strcmp(p->info, lexemas_reservadas[i]) == 0){
				is_token = 1;
				p->tok = i;
				/* //sintático
				verificadorSintatico(p->info, num_lin, sin);
				*/
				if (i>=12) // ADICIONA O ATRIBUTO, CASO POSSA TER, IMPORTANTE LEMBRAR QUE O ATRIBUTO SÓ ESTÁ SENDO FEITO DESSA FORMA PORQUE ELE ESTÁ ORGANIZADO DESSE JEITO
					p->attr = i-12;
				else
					p->attr = 3;
			}
		if ((verificarId(p->info) == 1) and (is_token == 0)){
			p->tok = 16;
			p->attr = 4;
		}
		p->line = num_lin;
		p = p->prox;
		is_token = 0;
	}
	//printarLinha(linha);
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
			l->info = pegarPalavras(linha); //PEGA A LINHA E TRANSFORMA EM UMA ESTRUTURA DE PALAVRAS
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
