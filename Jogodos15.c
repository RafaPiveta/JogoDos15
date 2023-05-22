// JOGO DOS 15 NA LINGUAGEM C

// Aluno: Rafael Olivare Piveta
// Curso: Engenharia da Computação (4 Periodo)



///////////////////////////////////////////////////// BIBLIOTECAS /////////////////////////////////////////////////////

#include <stdio.h> // Bilioteca padrao
#include <conio.h> // Biblioteca para captar os botoes do teclado
#include <stdlib.h> // Biblioteca para a funcao rand
#include <time.h> // Biblioteca para garantir o random toda vez

#define linha 4
#define coluna 4



////////////////////////////////////////////////// IMPRIME A MATRIZ ///////////////////////////////////////////////////

void printMatriz(int matriz[linha][coluna]) {
	int i, j;
	// Printa a matriz na tela				
	for (i = 0; i < linha; i++){
		for (j = 0; j < coluna; j++){
			if (matriz[i][j] != 0) {
				printf("[ %2d ]", matriz[i][j]);
			} else {
				printf("\033[31m[  0 ]\033[0m"); // Pinta o 0 de vermelho para melhorar a visualizacao
			}
		}
		printf("\n");
	}
	printf("\n");
}



/////////////////////////////////////////////////// LIMPA A TELA //////////////////////////////////////////////////////

void limpaTela() {
    #ifdef _WIN32
        system("cls"); // Limpa  o terminal em Windows
    #else
        system("clear"); // Limpa o terminal em Linux
    #endif
}



///////////////////////////////////////////////// SORTEIO DA MATRIZ //////////////////////////////////////////////////

void sorteiaMatriz(int matriz[linha][coluna], int *linha_vazia, int *coluna_vazia, int dificuldade) {
	int i, j;
    	int aleatorio, auxiliar, num_embaralhamento, contador;
	int ultimo_X, ultimo_Y;

	srand(time(NULL));
    
    	switch (dificuldade) {
		case 1:
		    num_embaralhamento = 25; //Nível fácil
		    break;
		case 2: 
		    num_embaralhamento = 50; //Nível médio
		    break;
		case 3:
		    num_embaralhamento = 75; //Nível díficil
		    break;
		default:
		    num_embaralhamento = 1; //Por padrao nao embaralha (precisa escolher uma dificuldade)
		    printf("Escolha uma dificuldade!");
		    break;
	    }

    	for (contador = 0; contador < num_embaralhamento; contador++) {
		aleatorio = rand() % 4;
		switch (aleatorio) {
			case 0: // W
				if (i == ultimo_X && j == ultimo_Y) { // Checa se o zero esta voltando para a ultima posicao para garantir a dificuldade
					contador--;
				} else if (i > 0) {			
					i = *linha_vazia - 1;
					j = *coluna_vazia;
					ultimo_X = *linha_vazia;
					ultimo_Y = *coluna_vazia;
				} 
				break;
			
			case 1: // A
				if (i == ultimo_X && j == ultimo_Y) { // Checa se o zero esta voltando para a ultima posicao para garantir a dificuldade
					contador--;
				} else if (j > 0) {
					i =*linha_vazia ;
					j = *coluna_vazia- 1;
					ultimo_X = *linha_vazia;
					ultimo_Y = *coluna_vazia;
				} 
				break;

			case 2: // S
				if (i == ultimo_X && j == ultimo_Y) { // Checa se o zero esta voltando para a ultima posicao para garantir a dificuldade
					contador--;
				} else if (i < 3) {
					i = *linha_vazia + 1;
					j = *coluna_vazia;
					ultimo_X = *linha_vazia;
					ultimo_Y = *coluna_vazia;
				} 
				break;

			case 3: // D
				if (i == ultimo_X && j == ultimo_Y) { // Checa se o zero esta voltando para a ultima posicao para garantir a dificuldade
					contador--;
				} else if (j < 3) {
					i = *linha_vazia;
					j = *coluna_vazia + 1;
					ultimo_X = *linha_vazia;
					ultimo_Y = *coluna_vazia;
				} 
				break;

			default:
				continue;
		}

        auxiliar = matriz[i][j]; // Realiza a troca de posicao por uma variavel auxiliar
        matriz[i][j] = matriz[*linha_vazia][*coluna_vazia];
        matriz[*linha_vazia][*coluna_vazia] = auxiliar;
        *linha_vazia = i;
        *coluna_vazia = j;
	printMatriz(matriz);
        limpaTela(); // Limpa a tela durante o embaralhamento para causar sensação de movimento
    }
}
	


											 //////////////////////
/////////////////////////////////////////////// MOVIMENTA O ZERO /////////////////////////////////////////////////////
											 //////////////////////

int movimentaMatriz (int matriz[linha][coluna], char movimento) {
	int i, j, x, y;
    	for (i = 0; i < linha; i++) {
		for (j = 0; j < coluna; j++) {
	    		if (matriz[i][j] == 0) { // Acha onde está localizado o 0 na matriz embaralhada
				x = i;
				y = j;
			break;
	   		}
		}
    	}

	switch (movimento) {
		case 'w': 
			if (x > 0) { //Checa se o jogador pode mover para cima
				matriz[x][y] = matriz[x - 1][y];
				matriz[x - 1][y] = 0;
			} 
			break;

		case 'a': 
			if (y > 0) { //Checa se o jogador pode mover para esquerda
				matriz[x][y] = matriz[x][y - 1];
				matriz[x][y - 1] = 0;
			} 
			break;

		case 's': 
			if (x < 3) { //Checa se o jogador pode mover para baixo
				matriz[x][y] = matriz[x + 1][y];
				matriz[x + 1][y] = 0;
			} 
			break;

		case 'd': 
			if (y < 3) { //Checa se o jogador pode mover para direita
				matriz[x][y] = matriz[x][y + 1];
				matriz[x][y + 1] = 0;
			} 
			break;
	
		default:
			break;
	}
	return 0;
}



///////////////////////////////////////////////// VERIFICA SE GANHOU /////////////////////////////////////////////////									

int verificaMatriz(int matriz[linha][coluna]) {
	// Verifica se o jogador ganhou
	int i, j;
	int matriz_solucao[4][4] = {{ 1,  2,  3,  4},
				    { 5,  6,  7,  8},
				    { 9, 10, 11, 12},
				    {13, 14, 15,  0}};
	
	for (i = 0; i < 4; i++){
		for (j = 0; j < 4; j++){
			if (matriz_solucao[i][j] != matriz[i][j]) {
				return 0;
			}
		}
	}
	return 1;
}



////////////////////////////////////////////////// FUNCAO PRINCIPAL //////////////////////////////////////////////////

int main() {
	int matriz[linha][coluna] = {{ 1,  2,  3,  4},
				     { 5,  6,  7,  8},
				     { 9, 10, 11, 12},
				     {13, 14, 15,  0}};

	int dificuldade;
	int linha_vazia = 3, coluna_vazia = 3; // Posicao inicial do zero
	char movimento, contador; // Contador de movimentos
	int vitoria = 0, desistir = 0; // Condicoes para aparecer mensagens na tela quando o jogo acabar
	

	printf("Ola, seja bem vindo ao jogo dos 15! Irei explicar as regras do jogo: \n\n");
	printf("- O jogo ira comecar com o quadro a seguir, decore-o: \n");
	printMatriz(matriz);
	printf("- Apos escolher uma dificuldade, o quadro sera embaralhado e o seu objetivo e voltar ao quadro original... \n");
	printf("- Os numeros devem ficar em ordem crescente e voce ira mover a casa em vermelho, boa sorte!\n\n");
	printf("Para comecarmos, digite um numero de 1 a 3 para escolher a dificuldade: \n");
	printf("1 - Facil \n2 - Medio \n3 - Dificil \n");
	scanf("%d", &dificuldade);
	sorteiaMatriz(matriz, &linha_vazia, &coluna_vazia, dificuldade);

    	limpaTela();
    	printMatriz(matriz);

	// Enquanto nao fechar, jogue o jogo
	int fechar = 0;
	while (!fechar){
		printf("Resolva a matriz sorteada! Para se mover utilize: \n");
		printf("   W - Cima \n   A - Esquerda \n   S - Baixo \n   D - Direita \n\n");
		printf("Deixe o quadrado em ordem crescente de cima para baixo, boa sorte!\n");
		printf("------------------------------------------------------------------\n");
		printf("Aperte ESC para sair\n");
		movimento = getch();
		if (movimento == 27) { //Codigo do botao ESC na tabela ASCII
			fechar = 1;
			desistir = 1;
		} else {
			if (movimentaMatriz(matriz, movimento)) {
				fechar = 0;
			} else if (verificaMatriz(matriz)) {
				printf("Parabens, voce ganhou o jogo");
				fechar = 1;
				vitoria = 1;
			}
		}
		contador++;
		limpaTela();
		printMatriz(matriz);
	}

	if (vitoria) {
		printf("Parabens, voce ganhou o jogo dos 15 em %d movimentos!!", contador);
	}

	if (desistir) {
		limpaTela();
		printf("Jogo fechando...");
	}

	return 1;
}
