//Guilherme Bastos de Oliveira
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variáveis globais
FILE *fp;
int linhas = 0;
unsigned char **palavras;

//Função de comparação para qsort e bsearch
int compara(const void *a, const void *b){
	return strcmp(*(const char **) a, *(const char **) b);
}

//Função para verificar se um char é uma letra
int letra(unsigned char ch){
	if( (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 192 && ch <= 196) || (ch >= 199 && ch <= 207) || (ch >= 210 && ch <= 214) || (ch >= 217 && ch <= 220) || (ch >= 224 && ch <= 228) || (ch >= 231 && ch <= 239) || (ch >= 242 && ch <= 246) || (ch >= 249 && ch <= 252)){
		return 1;
	}
	return 0;
}

//Função que retorna o char em letra minúscula
int minusc(unsigned char ch){
	if((ch >= 65 && ch <= 90) || (ch >= 192 && ch <= 196) || (ch >= 199 && ch <= 207) || (ch >= 210 && ch <= 214) || (ch >= 217 && ch <= 220)){
		ch+=32;
	}
	return ch;
}

int main(){
	//Variáveis utilizadas dentro do main
	int sizein, cont = 0;
	unsigned char ch, input[100], *copia;

	fp = fopen("/usr/share/dict/brazilian", "r");

	//Conta a quantidade de linhas(palavras) no arquivo
	while(!feof(fp)){
		fscanf(fp, "%s", input);
		linhas++;
	}

	//Aloca espaço para o vetor de ponteiros para as strings das palavras
	palavras = (unsigned char **) malloc (linhas*sizeof(unsigned char *));

	//Retorna para o início do arquivo
	rewind(fp);

	//Guarda as palavras do dicionário na memória
	for(int i = 0; i < linhas-1; i++){
		fscanf(fp, "%s", input);
		sizein = strlen((const char*)input);
		//Aloca memória para a palavra lida
		palavras[i] = (unsigned char *) malloc (sizein*sizeof(unsigned char));
		//Armazena a palavra já em letras minúsculas
		for(int j = 0; j < sizein; j++){
			palavras[i][j] = minusc(input[j]);
		}
	}

	//Ordena o vetor das palavras
	qsort(&palavras[0], linhas-1, sizeof(unsigned char *), compara);


	//lê o primeiro char do arquivo
	ch = fgetc(stdin);
	//Lê todos os char restantes
	while (!feof(stdin)) {
		//Enquanto não for uma letra, imprime o char
		while(!letra(ch) && !feof(stdin)){
			printf("%c", ch);
			ch = fgetc(stdin);
		}

		//Váriaveis utilizadas no while a seguir
		cont = 0;
		unsigned char palavra[100];

		//Enquanto o char for uma letra, armazena em uma string
		while(letra(ch) && !feof(stdin)){
			palavra[cont] = ch;
			ch = fgetc(stdin);
			cont++;
		}

		//Salva o char de final de string na primeira posição após as letras da palavra
		palavra[cont] = '\0';

		//Aloca memória para cópia da string de letras
		copia = (unsigned char *) malloc (strlen((const char *)palavra)*sizeof(unsigned char));

		//Salva a cópia com letras minúsculas
		for(int i = 0; i <= cont; i++){
			copia[i] = minusc(palavra[i]);
		}


		//Se foi lida uma palavra verifica se ela existe no dicionário, caso sim, imprime normal
		//caso contrário imprime entre colchetes
		if(cont){
			if((int *)bsearch(&copia, palavras, linhas-1, sizeof(unsigned char *), compara)){
				printf("%s", palavra);
			} else {
				printf("[%s]", palavra);
			}
		}
	}

	return 0;
}
