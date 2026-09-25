#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

/* Limpa o terminal no Windows (cls) e no Linux/macOS (clear) */
#ifdef _WIN32
#define limparTela() system("cls")
#else
#define limparTela() system("clear")
#endif

#define NUM_NAVIOS 3
#define TAM_TABULEIRO 5
#define TAM_MAX_PERSONALIZADO 15
#define TAM_MIN_PERSONALIZADO 2
#define TAM_MAX_PERSONALIZADO_MULT 10

#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void iniciarTabuleiroPersonalizadoMult(int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
    for (linha = 0; linha < qL; linha++) {
        for (coluna = 0; coluna < qC; coluna++) {
            tabuleiroPersonalizado[linha][coluna] = -1;
        }
    }
}

void iniciarShotPersonalizado(int shotPersonalizado[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
    for (linha = 0; linha < qL; linha++) {
        for (coluna = 0; coluna < qC; coluna++) {
            shotPersonalizado[linha][coluna] = -1;
        }
    }
}

void mostraTabuleiroPersonalizadoMult(int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int tabuleiroPersonalizado2[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
    printf("\n\t\t\tBATALHA "YEL "NAVAL\n\n" RESET);
    printf("          ");
    for (linha = 0; linha < qC; linha++) {
        if (linha <= 8) {
            printf("%d       ", linha + 1);
        } else {
            printf("%d     ", linha + 1);
        }
    }
    printf("||Player 1\n");

    for (linha = 0; linha < qL; linha++) {
        printf("%d", linha + 1);
        for (coluna = 0; coluna < qC; coluna++) {
            if (tabuleiroPersonalizado2[linha][coluna] == -1) {
            	printf("\t|");
                printf(BLU " ~ " RESET);
                printf("|");
            } else if (tabuleiroPersonalizado2[linha][coluna] == 0) {
                printf(RED "\t| * |" RESET);
            } else if (tabuleiroPersonalizado2[linha][coluna] == 1) {
                printf(GRN "\t| X |" RESET);
            }
        }
        printf("\n");
    }

    printf("\n");

    for (linha = 0; linha < qL; linha++) {
        printf("%d", linha + 1);
        for (coluna = 0; coluna < qC; coluna++) {
            if (tabuleiroPersonalizado[linha][coluna] == -1) {
                printf("\t|");
                printf(BLU " ~ " RESET);
                printf("|");
            } else if (tabuleiroPersonalizado[linha][coluna] == 0) {
                printf(RED "\t| * |" RESET);
            } else if (tabuleiroPersonalizado[linha][coluna] == 1) {
                printf(GRN "\t| X |" RESET);
            }
        }
        printf("\n");
    }
    printf("          ");
    for (linha = 0; linha < qC; linha++) {
        if (linha <= 8) {
            printf("%d       ", linha + 1);
        } else {
            printf("%d     ", linha + 1);
        }
    }
    printf("||Player 2\n");
}

void iniciaNaviosPersonalizadoMult(int navios[][2], int player, int qL, int qC) {
    int navio, linha, coluna, coordenadasRepetidas = 0, i;

    for (navio = 0; navio < NUM_NAVIOS; navio++) {
        printf("\n\n\n\t\t\t BATALHA " YEL "NAVAL\n\n" RESET);
        coordenadasRepetidas = 0;
        printf("|| Localizaï¿½ï¿½o dos navios %d do Player %d ||\n",navio+1 , player);
        printf("|| Linha (1 - %d): ", qL);

        char linhaInput[10];
        scanf("%9s", linhaInput);

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(linhaInput[0])) {
            printf("Entrada invalida. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        linha = atoi(linhaInput);

        if (linha < 1 || linha > qL) {
            printf("Numero de linha invalido. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }
        navios[navio][0] = linha;

        printf("|| Coluna (1 - %d): ", qC);

        char colunaInput[10];
        scanf("%9s", colunaInput);

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(colunaInput[0])) {
            printf("Entrada invalida. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        coluna = atoi(colunaInput);

        if (coluna < 1 || coluna > qC) {
            printf("Numero de coluna invalido. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }
        navios[navio][1] = coluna;

        for (i = 0; i < navio; i++) {
            if (navios[i][0] == linha && navios[i][1] == coluna) {
                coordenadasRepetidas = 1;
                break;
            }
        }

        if (coordenadasRepetidas == 1) {
            printf("Coordenadas jï¿½ foram usadas. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        sleep(2);
        limparTela();
    }
}

void darTiroPersonalizadoMult(int tiroPersonalizado[2], int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int tabuleiroPersonalizado2[][TAM_MAX_PERSONALIZADO], int score, int score2, int shotPersonalizado[][TAM_MAX_PERSONALIZADO], int shotPersonalizado2[][TAM_MAX_PERSONALIZADO], int qL, int qC, int player) {
    int foi = 0;

    while (foi == 0) {
    	mostraTabuleiroPersonalizadoMult(tabuleiroPersonalizado, tabuleiroPersonalizado2, qL, qC);
        printf("\n\nVez do Player %d", player);
        printf("\nLinha: ");

        char linhaInput[10];
        scanf("%9s", linhaInput);

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(linhaInput[0])) {
            printf("Entrada invalida. Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[0] = atoi(linhaInput);

        if (tiroPersonalizado[0] < 1 || tiroPersonalizado[0] > qL) {
            printf("Numero invalido. Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[0]--;

        printf("Coluna: ");

        char colunaInput[10];
        scanf("%9s", colunaInput);

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(colunaInput[0])) {
            printf("Entrada invalida. Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[1] = atoi(colunaInput);

        if (tiroPersonalizado[1] < 1 || tiroPersonalizado[1] > qC) {
            printf("Numero invalido. Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[1]--;

        if (player == 1) {
            if (shotPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] == 0) {
                printf("Jï¿½ atirou aqui. \n");
                sleep(2);
                limparTela();
                continue;
            }
            foi = 1;
        } else if (player == 2) {
            if (shotPersonalizado2[tiroPersonalizado[0]][tiroPersonalizado[1]] == 0) {
                printf("Jï¿½ atirou aqui. \n");
                sleep(2);
                limparTela();
                continue;
            }
            foi = 1;
        }
    }

    if (player == 1) {
        shotPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
    } else if (player == 2) {
        shotPersonalizado2[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
    }
}

int acertouPersonalizadoMult(int tiroPersonalizado[2], int naviosPersonalizado[][2], int naviosPersonalizado2[][2], int player) {
    int navio;
    int acerto = 0;
    
    if (player == 1) {
        for (navio = 0; navio < NUM_NAVIOS; navio++) { // Check all ships for player 1
            if (tiroPersonalizado[0] == naviosPersonalizado2[navio][0] && tiroPersonalizado[1] == naviosPersonalizado2[navio][1]) {
                printf("Player 1 "  "ACERTOU"  " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
                sleep(2);
                acerto = 1;
                break;
            }
        }
        if (acerto == 0) {
            printf("Player 1 " "ERROU" " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
            sleep(2);
        }
    } else if (player == 2) {
        for (navio = 0; navio < NUM_NAVIOS; navio++) { // Check all ships for player 2
            if (tiroPersonalizado[0] == naviosPersonalizado[navio][0] && tiroPersonalizado[1] == naviosPersonalizado[navio][1]) {
                printf("Player 2 "  "ACERTOU"  " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
                sleep(2);
                acerto = 1;
                break;
            }
        }
        if (acerto == 0) {
            printf("Player 2 " "ERROU" " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
            sleep(2);
        }
    }
    return acerto;
}

void alteraTabuleiroPersonalizadoMult(int tiroPersonalizado[2], int naviosPersonalizado[][2],int naviosPersonalizado2[][2], int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int tabuleiroPersonalizado2[][TAM_MAX_PERSONALIZADO], int player, int *score, int *score2, int *acertos1, int *acertos2) {
    if (acertouPersonalizadoMult(tiroPersonalizado, naviosPersonalizado, naviosPersonalizado2, player)) {
        if (player == 2) {
            tabuleiroPersonalizado2[tiroPersonalizado[0]][tiroPersonalizado[1]] = 1;
            *score2 += 100;
            *acertos2 += 1;
        } else if (player == 1) {
            tabuleiroPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 1;
            *score += 100;
            *acertos1 += 1;
        }
    } else {
        if (player == 2) {
            tabuleiroPersonalizado2[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
            if (*score2 == 0){
            	*score2 = *score;
			}else{
				*score2 -= 50;
			}
            
        } else if (player == 1) {
            tabuleiroPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
            if (*score == 0){
            	*score = *score;
			}else{
				*score -= 50;
			}
        }
    }
}

void inicializaTabuleiroPersonalizado(int tabuleiro[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
    for (linha = 0; linha < qL; linha++) {
        for (coluna = 0; coluna < qC; coluna++) {
            tabuleiro[linha][coluna] = -1;
        }
    }
}

void inicializaShotPersonalizado(int shot[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
    for (linha = 0; linha < qL; linha++) {
        for (coluna = 0; coluna < qC; coluna++) {
            shot[linha][coluna] = -1;
        }
    }
}

void mostraTabuleiroPersonalizado(int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int qL, int qC) {
    int linha, coluna;
  	printf("\n\t\t\tBATALHA "YEL "NAVAL\n\n" RESET);
    printf("      ");
    for (linha = 0; linha < qC; linha++) {
        if (linha <= 8) {
            printf("    %d", linha + 1);
        } else {
            printf("   %d", linha + 1);
        }
    }
    printf("\n");

    for(linha=0 ; linha < qL ; linha++ ){
        printf(YEL "%d\t" RESET,linha+1);
        for(coluna=0 ; coluna < qC ; coluna++ ){
            if (tabuleiroPersonalizado[linha][coluna] == -1) {
            	printf("|");
                printf(BLU " ~ " RESET);
                printf("|");
           	} else if (tabuleiroPersonalizado[linha][coluna] == 0) {
                printf(RED "| * |" RESET);
           	} else if (tabuleiroPersonalizado[linha][coluna] == 1) {
                printf(GRN "| X |" RESET);
           	}
        }
        printf("\n");
    }
    printf("\n");
}

void iniciaNaviosPersonalizado(int navios[][2], int qL, int qC) {
    srand(time(NULL));
    int navio, anterior;

    for (navio = 0; navio < NUM_NAVIOS; navio++) {
        navios[navio][0] = rand() % qL;
        navios[navio][1] = rand() % qC;

        // Verifica se a posiï¿½ï¿½o ja foi ocupada por outro navio
        for (anterior = 0; anterior < navio; anterior++) {
            while ((navios[navio][0] == navios[anterior][0]) && (navios[navio][1] == navios[anterior][1])) {
                navios[navio][0] = rand() % qL;
                navios[navio][1] = rand() % qC;
                anterior = 0;  // Reinicia a verificaï¿½ï¿½o desde o inicio
            }
        }
    }
}

void darTiroPersonalizado(int tiroPersonalizado[2], int shotPersonalizado[][TAM_MAX_PERSONALIZADO], int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int naviosPersonalizado[][2], int qL, int qC) {
    int foi = 0, i;
    while (foi == 0) {
        limparTela();
        mostraTabuleiroPersonalizado(tabuleiroPersonalizado, qL, qC);
        printf("Linha: ");
        char linhaInput[10];
        scanf("%9s", linhaInput);

        // Verifica se o input ï¿½ "777"
        if (strcmp(linhaInput, "777") == 0) {
            for (i = 0; i < NUM_NAVIOS; i++) {
                printf("Tiro (%d,%d)\n", naviosPersonalizado[i][0] + 1, naviosPersonalizado[i][1] + 1);
            }
            sleep(2);
            continue;
        }

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(linhaInput[0])) {
            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[0] = atoi(linhaInput);

        if (tiroPersonalizado[0] < 1 || tiroPersonalizado[0] > qL) {
            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[0]--;

        printf("Coluna: ");
        char colunaInput[10];
        scanf("%9s", colunaInput);

        // Verifica se o input contï¿½m apenas dï¿½gitos
        if (!isdigit(colunaInput[0])) {
            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[1] = atoi(colunaInput);

        if (tiroPersonalizado[1] < 1 || tiroPersonalizado[1] > qC) {
            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiroPersonalizado[1]--;

        if (shotPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] == 0) {
            // Jï¿½ atirou aqui
            printf("Ja atirou aqui.\n");
            sleep(2);
            limparTela();
            continue;
        }

        foi = 1;
    }
    shotPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
}

int acertouPersonalizado(int tiroPersonalizado[2], int naviosPersonalizado[][2]) {
    int navio;
    for (navio = 0; navio < NUM_NAVIOS; navio++) {
        if (tiroPersonalizado[0] == naviosPersonalizado[navio][0] && tiroPersonalizado[1] == naviosPersonalizado[navio][1]) {
            printf(GRN "ACERTOU" RESET " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
            return 1;
        }   
    }
    printf(RED "ERROU" RESET " o tiro (%d,%d)\n", tiroPersonalizado[0] + 1, tiroPersonalizado[1] + 1);
    return 0;  
}

void alteraTabuleiroPersonalizado(int tiroPersonalizado[2], int naviosPersonalizado[][2], int tabuleiroPersonalizado[][TAM_MAX_PERSONALIZADO], int *acertos1) {
    if (acertouPersonalizado(tiroPersonalizado, naviosPersonalizado)) {
        tabuleiroPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 1;
        *acertos1 += 1;
    } else {
        tabuleiroPersonalizado[tiroPersonalizado[0]][tiroPersonalizado[1]] = 0;
    }
}

void inicializaTabuleiro(int tabuleiro[][TAM_TABULEIRO]) {
    int linha, coluna;
    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            tabuleiro[linha][coluna] = -1;
        }
    }
}

void inicializaShot(int shot[][TAM_TABULEIRO]) {
    int linha, coluna;
    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            shot[linha][coluna] = -1;
        }
    }
}

void mostraTabuleiroSozinho(int tabuleiroSozinho[][TAM_TABULEIRO]){
    int linha, coluna;
    	printf("\n\t\t BATALHA "YEL "NAVAL\n\n" RESET);

        printf(YEL "\t    1    2    3    4    5" RESET);
        printf("\n");

        for(linha=0 ; linha < TAM_TABULEIRO ; linha++ ){
            printf(YEL "\t%d " RESET,linha+1);
            for(coluna=0 ; coluna < TAM_TABULEIRO ; coluna++ ){
                if (tabuleiroSozinho[linha][coluna] == -1) {
            	printf("|");
                printf(BLU " ~ " RESET);
                printf("|");
            	} else if (tabuleiroSozinho[linha][coluna] == 0) {
                printf(RED "| * |" RESET);
            	} else if (tabuleiroSozinho[linha][coluna] == 1) {
                printf(GRN "| X |" RESET);
            	}
            }
            printf("\n");
        }
        printf("\n");
    }

void mostraTabuleiro(int tabuleiro[][TAM_TABULEIRO], int tabuleiro2[][TAM_TABULEIRO], int score, int score2) {
    int linha, coluna;
    printf("\n\t\t\tBATALHA "YEL "NAVAL\n\n" RESET);
    printf("\t  1 \t  2 \t  3 \t  4 \t  5 \t||Player 1 \t||Score: " YEL "%03d" RESET, score);
    printf("\n");

    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%d", linha + 1);
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            if (tabuleiro2[linha][coluna] == -1) {
            	printf("\t|");
                printf(BLU " ~ " RESET);
                printf("|");
            } else if (tabuleiro2[linha][coluna] == 0) {
                printf(RED "\t| * |" RESET);
            } else if (tabuleiro2[linha][coluna] == 1) {
                printf(GRN "\t| X |" RESET);
            }
        }
        printf("\n");
    }

    printf("\n");

    for (linha = 0; linha < TAM_TABULEIRO; linha++) {
        printf("%d", linha + 1);
        for (coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            if (tabuleiro[linha][coluna] == -1) {
                printf("\t|");
                printf(BLU " ~ " RESET);
                printf("|");
            } else if (tabuleiro[linha][coluna] == 0) {
                printf(RED "\t| * |" RESET);
            } else if (tabuleiro[linha][coluna] == 1) {
                printf(GRN "\t| X |" RESET);
            }
        }
        printf("\n");
    }
    printf("\t  1 \t  2 \t  3 \t  4 \t  5 \t||Player 2 \t||Score: " YEL "%03d" RESET, score2);
}

void iniciaNavios(int navios[][2], int player) {
    int navio, linha, coluna, coordenadasRepetidas = 0, i, cont = 0;

    for (navio = 0; navio < NUM_NAVIOS; navio++) {
        coordenadasRepetidas = 0;
        char linhaInput[10], colunaInput[10];
        limparTela();
		printf("\n\t\t\tBATALHA "YEL "NAVAL\n\n" RESET);
        printf("|| Localizaï¿½ï¿½o do navio %d do Player %d ||\n", navio+1, player);
        printf("|| Linha (1 - 5): ");
        scanf("%9s", linhaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isLinhaDigit = 1;
        for (i = 0; linhaInput[i] != '\0'; i++) {
            if (!isdigit(linhaInput[i])) {
                isLinhaDigit = 0;
                break;
            }
        }

        if (!isLinhaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        linha = atoi(linhaInput);

        if (linha < 1 || linha > TAM_TABULEIRO) {
            printf("Nï¿½mero de linha " RED "invï¿½lido" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }
        navios[navio][0] = linha - 1;

        printf("|| Coluna (1 - 5): ");
        scanf("%9s", colunaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isColunaDigit = 1;
        for (i = 0; colunaInput[i] != '\0'; i++) {
            if (!isdigit(colunaInput[i])) {
                isColunaDigit = 0;
                break;
            }
        }

        if (!isColunaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        coluna = atoi(colunaInput);

        if (coluna < 1 || coluna > TAM_TABULEIRO) {
            printf("Nï¿½mero de coluna " RED "invï¿½lido" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }
        navios[navio][1] = coluna - 1;

        for (i = 0; i < navio; i++) {
            if (navios[i][0] == linha - 1 && navios[i][1] == coluna - 1) {
                coordenadasRepetidas = 1;
                break;
            }
        }

        if (coordenadasRepetidas == 1) {
            printf("Coordenadas jï¿½ foram usadas. Tente novamente.\n");
            sleep(2);
            limparTela();
            navio--;
            continue;
        }

        sleep(2);
        limparTela();
    }
}

void iniciaNaviosSozinho(int navios[][2]){
    srand(time(NULL));
    int navio, anterior;

    // Gerar posiÃ§Ãµes aleatÃ³rias para os navios
    for(navio = 0 ; navio < NUM_NAVIOS ; navio++){
        navios[navio][0]= rand()%5;
        navios[navio][1]= rand()%5;
    }

    // Verificar e corrigir colisÃµes
    for(navio = 0; navio < NUM_NAVIOS; navio++){
        for(anterior = 0; anterior < navio; anterior++){
            while((navios[navio][0] == navios[anterior][0]) && (navios[navio][1] == navios[anterior][1])){
                // Corrigir colisÃ£o gerando novas posiÃ§Ãµes
                navios[navio][0] = rand() % TAM_TABULEIRO;
                navios[navio][1] = rand() % TAM_TABULEIRO;
                // Reiniciar a verificaÃ§Ã£o com todos os navios anteriores
                anterior = 0;
            }
        }
    }
}

void darTiroSozinho(int tiro[2], int shot1[][TAM_TABULEIRO], int tabuleiroSozinho[][TAM_TABULEIRO], int navios[][2], int *tentativas) {
    int foi = 0, i;

    while (foi == 0) {
        char linhaInput[10], colunaInput[10];
		limparTela();
		mostraTabuleiroSozinho(tabuleiroSozinho);
        printf("Linha: ");
        scanf("%9s", linhaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isLinhaDigit = 1;
        for (i = 0; linhaInput[i] != '\0'; i++) {
            if (!isdigit(linhaInput[i])) {
                isLinhaDigit = 0;
                break;
            }
        }

        if (!isLinhaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiro[0] = atoi(linhaInput);

        if (tiro[0] == 777) {
            for (i = 0; i < NUM_NAVIOS; i++) {
                printf("Tiro (%d,%d)\n", navios[i][0] + 1, navios[i][1] + 1);
            }
            sleep(2);
            continue;
        }
		else if (tiro[0] < 1 || tiro[0] > TAM_TABULEIRO) {
            printf("Nï¿½mero " RED "INVï¿½LIDO" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }
        tiro[0]--;

        printf("Coluna: ");
        scanf("%9s", colunaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isColunaDigit = 1;
        for (i = 0; colunaInput[i] != '\0'; i++) {
            if (!isdigit(colunaInput[i])) {
                isColunaDigit = 0;
                break;
            }
        }

        if (!isColunaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            limparTela();
            continue;
        }

        tiro[1] = atoi(colunaInput);

        if (tiro[1] < 1 || tiro[1] > TAM_TABULEIRO) {
            printf("Nï¿½mero " RED "INVï¿½LIDO" RESET ". Tente novamente.\n");
            sleep(2);
            limparTela();
            continue;
        }
        tiro[1]--;

        if (shot1[tiro[0]][tiro[1]] == 0) {
            // jï¿½ atirou aqui
            printf("Jï¿½ atirou aqui.\n");
            sleep(2);
            limparTela();
            continue;
        }
        foi = 1;
    }

    shot1[tiro[0]][tiro[1]] = 0;
}
void darTiro(int tiro[2], int player, int tabuleiro[][TAM_TABULEIRO], int tabuleiro2[][TAM_TABULEIRO], int score, int score2, int shot1[][TAM_TABULEIRO], int shot2[][TAM_TABULEIRO]) {
    int foi = 0, i;

    while (foi == 0) {
        limparTela();
        mostraTabuleiro(tabuleiro, tabuleiro2, score, score2);
        printf("\n\nVez do Player %d\n", player);
        
        char linhaInput[10], colunaInput[10];

        printf("Linha: ");
        scanf("%9s", linhaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isLinhaDigit = 1;
        for (i = 0; linhaInput[i] != '\0'; i++) {
            if (!isdigit(linhaInput[i])) {
                isLinhaDigit = 0;
                break;
            }
        }

        if (!isLinhaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            continue;
        }

        tiro[0] = atoi(linhaInput);

        if (tiro[0] < 1 || tiro[0] > TAM_TABULEIRO) {
            printf("Nï¿½mero " RED "invï¿½lido" RESET ". Tente novamente.\n");
            sleep(2);
            continue;
        }
        tiro[0]--;

        printf("Coluna: ");
        scanf("%9s", colunaInput);

        // Verifica se a entrada contï¿½m apenas dï¿½gitos
        int isColunaDigit = 1;
        for (i = 0; colunaInput[i] != '\0'; i++) {
            if (!isdigit(colunaInput[i])) {
                isColunaDigit = 0;
                break;
            }
        }

        if (!isColunaDigit) {
            printf("Entrada invï¿½lida. Por favor, insira um nï¿½mero vï¿½lido.\n");
            sleep(2);
            continue;
        }

        tiro[1] = atoi(colunaInput);

        if (tiro[1] < 1 || tiro[1] > TAM_TABULEIRO) {
            printf("Nï¿½mero " RED "invï¿½lido" RESET ". Tente novamente.\n");
            sleep(2);
            continue;
        }
        tiro[1]--;

        if (player == 1) {
            if (shot1[tiro[0]][tiro[1]] == 0) {
                // jï¿½ atirou aqui
                printf("Jï¿½ atirou aqui.\n");
                sleep(2);
                continue;
            }
        } else {
            if (shot2[tiro[0]][tiro[1]] == 0) {
                // jï¿½ atirou aqui
                printf("Jï¿½ atirou aqui.\n");
                sleep(2);
                continue;
            }
        }

        foi = 1;
    }

    if (player == 1) {
        shot1[tiro[0]][tiro[1]] = 0;
    } else {
        shot2[tiro[0]][tiro[1]] = 0;
    }
}
int acertouSozinho(int tiro[2], int navios[][2], int *tentativas){
    int navio;

    for(navio = 0; navio < NUM_NAVIOS; navio++){
        if(tiro[0] == navios[navio][0] && tiro[1] == navios[navio][1]){
            printf(GRN "ACERTOU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
            sleep(1);
            return 1;  // Deve retornar 1 em caso de acerto
        }
    }
    
    printf(RED "ERROU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
    sleep(1);
    return 0;  // Deve retornar 0 em caso de erro
}
    
int acertou(int tiro[2], int navios[][2], int navios2[][2], int player) {
    int navio;
    int acerto = 0;

    if (player == 1) {
        for (navio = 0; navio < NUM_NAVIOS; navio++) { // Check all 3 ships for player 1
            if (tiro[0] == navios2[navio][0] && tiro[1] == navios2[navio][1]) {
                printf("Player 1 " GRN "ACERTOU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
                sleep(2);
                acerto = 1;
                break;
            }
        }
        if (acerto == 0) {
            printf("Player 1 " RED "ERROU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
            sleep(2);
        }
    } else if (player == 2) {
        for (navio = 0; navio < NUM_NAVIOS; navio++) { // Check all 3 ships for player 2
            if (tiro[0] == navios[navio][0] && tiro[1] == navios[navio][1]) {
                printf("Player 2 " GRN "ACERTOU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
                sleep(2);
                acerto = 1;
                break;
            }
        }
        if (acerto == 0) {
            printf("Player 2 " RED "ERROU" RESET " o tiro (%d,%d)\n", tiro[0] + 1, tiro[1] + 1);
            sleep(2);
        }
    }

    return acerto;
}

void alteraTabuleiroSozinho(int tiro[2], int navios[][2], int tabuleiroSozinho[][TAM_TABULEIRO], int *acertos1, int *tentativas){
    if(acertouSozinho(tiro,navios,tentativas)){
        tabuleiroSozinho[tiro[0]][tiro[1]] = 1;
        *acertos1 += 1;
    }else {
        tabuleiroSozinho[tiro[0]][tiro[1]] = 0;
   	}
}

void alteraTabuleiro(int tiro[2], int navios[][2],int navios2[][2], int tabuleiro[][TAM_TABULEIRO], int tabuleiro2[][TAM_TABULEIRO], int player, int *score, int *score2, int *acertos1, int *acertos2) {
    if (acertou(tiro, navios, navios2, player)) {
        if (player == 2) {
            tabuleiro2[tiro[0]][tiro[1]] = 1;
            *score2 += 100;
            *acertos2 += 1;
        } else if (player == 1) {
            tabuleiro[tiro[0]][tiro[1]] = 1;
            *score += 100;
            *acertos1 += 1;
        }
    } else {
        if (player == 2) {
            tabuleiro2[tiro[0]][tiro[1]] = 0;
            if (*score2 == 0){
            	*score2 = *score;
			}else{
				*score2 -= 20;
			}
            
        } else if (player == 1) {
            tabuleiro[tiro[0]][tiro[1]] = 0;
            if (*score == 0){
            	*score = *score;
			}else{
				*score -= 20;
			}
        }
    }
}

int main() {
	setlocale(LC_ALL,"Portuguese");
    int tabuleiroSozinho[TAM_TABULEIRO][TAM_TABULEIRO];
	int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], tabuleiro2[TAM_TABULEIRO][TAM_TABULEIRO];
    int shot1[TAM_TABULEIRO][TAM_TABULEIRO], shot2[TAM_TABULEIRO][TAM_TABULEIRO];
    int player = 1;
    int tiro[2], tiro2[2];
    int navios[3][2], navios2[3][2];
    int score = 100, score2 = 100, acertos1 = 0, acertos2 = 0, tentativas = 0;
    //variaveis do jogo personalisado 
    int tabuleiroPersonalizado[TAM_MAX_PERSONALIZADO][TAM_MAX_PERSONALIZADO];
    int tabuleiroPersonalizado2[TAM_MAX_PERSONALIZADO][TAM_MAX_PERSONALIZADO];
    int shotPersonalizado[TAM_MAX_PERSONALIZADO][TAM_MAX_PERSONALIZADO];
    int shotPersonalizado2[TAM_MAX_PERSONALIZADO][TAM_MAX_PERSONALIZADO];
    int naviosPersonalizado[3][2];
    int naviosPersonalizado2[3][2];
    int tiroPersonalizado[2];
    int tentativasPersonalizado = 0, acertosPersonalizado = 0;
    int qL, qC, lol = 1; //qL: Tamanho da linha | qC: Tamanho da coluna
    
    
    
    printf("\n\t\t\t" RED "GRUPO CADERNO" RESET " apresenta...");
    sleep(2);
    limparTela();
    printf("\n\t\t\tJOGO");
    sleep(1);
    printf(" DO ");
    sleep(1);
    printf(YEL "CADERNO" RESET);
    sleep(1);
    limparTela();
    int loop = 1;
    char op1 = ' ', op2 = ' ', op3 = ' ', op4 = ' ', op5 = ' ';
    
	while (loop == 1) {
		voltar:
		limparTela();
		op1 = ' ';
		printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
		printf("\n\n  1 - BATALHA NAVAL\n  2 - CRï¿½DITOS\n  3 - REGRAS\n  0 - " RED "SAIR" RESET "\n  ");
		scanf(" %c", &op1);
		if (op1 == '1' || op1 == '2' || op1 == '3' || op1 == '0') {
			switch (op1) {
				case '1': //MENU DO JOGO
					voltar3:
					while (loop == 1) {
						limparTela();
						op2 = ' ';
						printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
						printf("\n\n  1 - UM JOGADOR\n  2 - DOIS JOGADORES\n  3 - MODO PERSONALIZADO\n  0 - "RED"VOLTAR"RESET"\n  ");
						scanf(" %c", &op2);
	
						if (op2 != '1' && op2 != '2' && op2 != '3' && op2 != '0') {
							limparTela();
							printf(RED "Nï¿½mero Invï¿½lido" RESET);
							sleep(1);
							limparTela();
							continue;
						}
						switch (op2) {
							case '1': //MODO UM JOGADOR
								inicializaTabuleiro(tabuleiroSozinho);
								inicializaShot(shot1);
								iniciaNaviosSozinho(navios);
								while (acertos1 != 3){
									limparTela();
									mostraTabuleiroSozinho(tabuleiroSozinho);
									darTiroSozinho(tiro, shot1, tabuleiroSozinho, navios, &tentativas);
									alteraTabuleiroSozinho(tiro, navios, tabuleiroSozinho, &acertos1, &tentativas);
									tentativas++;
									sleep(2);
								}
								limparTela();
								mostraTabuleiroSozinho(tabuleiroSozinho);
								printf(YEL "\tPARABENS!!! Vitoria" RESET);
								printf("\nVoce acertou os 3 navios em" GRN " %d " RESET "tentativas\n", tentativas);
								system("pause");
								tentativas = 0;
								acertos1 = 0;
								break;
							case '2': //MODO DOIS JOGADORES
								acertos1 = 0;
		    					acertos2 = 0;
		    					limparTela();
		    					printf("\n\n\n\t\t\t BATALHA "YEL "NAVAL\n\n" RESET);
		    					inicializaTabuleiro(tabuleiro);
		    					inicializaShot(shot1);
		    					iniciaNavios(navios, player);
		    					limparTela();
		    					printf("\n\n\n\t\t\t BATALHA "YEL "NAVAL\n\n" RESET);
		    					player = (player == 1) ? 2 : 1;	
		    					inicializaTabuleiro(tabuleiro2);
		    					inicializaShot(shot2);
		    					iniciaNavios(navios2, player);
		    					player = (player == 1) ? 2 : 1;
		    					do {
		    						limparTela();
		    						printf("\n\n\n\t\t\t BATALHA "YEL "NAVAL\n\n" RESET);
		    						mostraTabuleiro(tabuleiro, tabuleiro2, score, score2);
		    						darTiro(tiro, player, tabuleiro, tabuleiro2, score, score2, shot1, shot2);
		    						alteraTabuleiro(tiro, navios, navios2, tabuleiro, tabuleiro2, player, &score, &score2, &acertos1, &acertos2);
		    						sleep(2);
		    						player = (player == 1) ? 2 : 1;
		    						if (acertos1 == 3) {
		    							limparTela();
		    							mostraTabuleiro(tabuleiro, tabuleiro2, score, score2);
		    							printf("\n\nPlayer 1 venceu!\n");
		    							printf("Score: "YEL"%d"RESET"\n", score);
		    							system("pause");
		    							limparTela();
		    							break;
		    						} else if (acertos2 == 3) {
		    							limparTela();
		    							mostraTabuleiro(tabuleiro, tabuleiro2, score, score2);
		    							printf("\n\nPlayer 2 venceu!\n");
		    							printf("Score: "YEL"%d"RESET"\n", score2);
		    							system("pause");
		    							limparTela();
		    							break;
		    						}
		    						limparTela();
		    					}while(1);
		    					score = 100;
		    					score2 = 100;
		    					acertos1 = 0;
		    					acertos2 = 0;
		    					player = 1;
		    					break;
							case '3':  //MENU DO PERSONALIZADO
								while (loop == 1) {
									limparTela();
									op2 = ' ';
									printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
									printf("\n\n  1 - UM JOGADOR\n  2 - DOIS JOGADORES\n  0 - "RED"VOLTAR"RESET"\n  ");
									scanf(" %c", &op4);
									switch(op4){
										case '1':  //PERSONALIZADO UM JOGADOR
											lol = 1;
			    							qL = 0;
										    qC = 0;
										    
			    							do {
			    								limparTela();
			    								printf("\n\n\n\t\t\t BATALHA "YEL "NAVAL\n\n" RESET);
												printf("Tamanho do tabuleiro (%d - %d)\n", TAM_MIN_PERSONALIZADO, TAM_MAX_PERSONALIZADO);
										        printf("Linhas: ");

										        char qLInput[10];
										        scanf("%9s", qLInput);

										        if (!isdigit(qLInput[0])) {
										            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
										            sleep(2);
										            limparTela();
										            continue;
										        }

										        qL = atoi(qLInput);

										        if (qL < TAM_MIN_PERSONALIZADO || qL > TAM_MAX_PERSONALIZADO) {
										            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
										            sleep(2);
										            limparTela();
										        } else {
										            break;
										        }
										    } while (1);

										    do {
										        printf("Colunas: ");

										        char qCInput[10];
										        scanf("%9s", qCInput);

										        if (!isdigit(qCInput[0])) {
										            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
										            sleep(2);
										            limparTela();
										            continue;
										        }

										        qC = atoi(qCInput);

										        if (qC < TAM_MIN_PERSONALIZADO || qC > TAM_MAX_PERSONALIZADO) {
										            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
										            sleep(2);
										            limparTela();
										        } else {
										            break;
										        }
											}while(1);
											
											inicializaTabuleiroPersonalizado(tabuleiroPersonalizado, qL, qC);
										    inicializaShotPersonalizado(shotPersonalizado, qL, qC);
										    iniciaNaviosPersonalizado(naviosPersonalizado, qL, qC);	
										    while (acertosPersonalizado != 3) {
										        limparTela();
										        mostraTabuleiroPersonalizado(tabuleiroPersonalizado, qL, qC);
										        darTiroPersonalizado(tiroPersonalizado, shotPersonalizado, tabuleiroPersonalizado, naviosPersonalizado, qL, qC);
										        alteraTabuleiroPersonalizado(tiroPersonalizado, naviosPersonalizado, tabuleiroPersonalizado, &acertosPersonalizado);
										        tentativasPersonalizado++;
										        sleep(2);
										    }
										
										    limparTela();
										    mostraTabuleiroPersonalizado(tabuleiroPersonalizado, qL, qC);
										    printf(YEL "Vitoria" RESET);
										    printf("\nVoce acertou os 3 navios em" GRN " %d " RESET "tentativas\n\n", tentativasPersonalizado);
										    system("pause");
										    tentativasPersonalizado = 0;
										    acertosPersonalizado = 0;
										    break;
										case '2':
											player = 1;
											acertos1 = 0;
											acertos2 = 0;
											lol = 1;
											qL = 0;
										    qC = 0;
										    while (lol == 1) {
										        limparTela();
										        printf("\n\n\n\t\t\t BATALHA " YEL "NAVAL\n\n" RESET);
										        printf("Tamanho do tabuleiro (%d - %d)\n", TAM_MIN_PERSONALIZADO, TAM_MAX_PERSONALIZADO_MULT);
										        printf("Linhas: ");
										
										        char linhaInput[10];
										        scanf("%9s", linhaInput);
										
										        // Verifica se o input contï¿½m apenas dï¿½gitos
										        if (!isdigit(linhaInput[0])) {
										            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
										            sleep(2);
										            continue;
										        }
										
										        qL = atoi(linhaInput);
										
										        if (qL < TAM_MIN_PERSONALIZADO || qL > TAM_MAX_PERSONALIZADO_MULT) {
										            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
										            sleep(2);
										            continue;
										        }
										
										        printf("Colunas: ");
										
										        char colunaInput[10];
										        scanf("%9s", colunaInput);
										
										        // Verifica se o input contï¿½m apenas dï¿½gitos
										        if (!isdigit(colunaInput[0])) {
										            printf("Entrada " RED "INVALIDA" RESET ". Tente novamente.\n");
										            sleep(2);
										            continue;
										        }
										
										        qC = atoi(colunaInput);
										
										        if (qC < TAM_MIN_PERSONALIZADO || qC > TAM_MAX_PERSONALIZADO_MULT) {
										            printf("Numero " RED "INVALIDO" RESET ". Tente novamente.\n");
										            sleep(2);
										            continue;
										        }
										
										        lol = 0;
										    }
											limparTela();
											iniciarTabuleiroPersonalizadoMult(tabuleiroPersonalizado, qL, qC);
										    iniciarShotPersonalizado(shotPersonalizado, qL, qC);
										    iniciaNaviosPersonalizadoMult(naviosPersonalizado, player, qL, qC);
										    player = (player == 1) ? 2 : 1;
										    limparTela();
										    iniciarTabuleiroPersonalizadoMult(tabuleiroPersonalizado2, qL, qC);
										    iniciarShotPersonalizado(shotPersonalizado2, qL, qC);
										    iniciaNaviosPersonalizadoMult(naviosPersonalizado2, player, qL, qC);
										    player = (player == 1) ? 2 : 1;
										    limparTela();
										    do {
										        darTiroPersonalizadoMult(tiroPersonalizado, tabuleiroPersonalizado, tabuleiroPersonalizado2, score, score2, shotPersonalizado, shotPersonalizado2, qL, qC, player);
												alteraTabuleiroPersonalizadoMult(tiroPersonalizado, naviosPersonalizado, naviosPersonalizado2, tabuleiroPersonalizado, tabuleiroPersonalizado2, player, &score, &score2, &acertos1, &acertos2);
												player = (player == 1) ? 2 : 1;
												if(acertos1 == 3){
													limparTela();
													mostraTabuleiroPersonalizadoMult(tabuleiroPersonalizado, tabuleiroPersonalizado2, qL, qC);
													printf("\nPlayer 1 Venceu!\n");
													sleep(2);
													limparTela();
													break;
												} else if(acertos2 == 3){
													limparTela();
													mostraTabuleiroPersonalizadoMult(tabuleiroPersonalizado, tabuleiroPersonalizado2, qL, qC);
													printf("\nPlayer 2 Venceu!\n");
													sleep(2);
													limparTela();
													break;
												}
												limparTela();
										    } while (1);
											score = 100;
											score2 = 100;
											acertos1 = 0;
											acertos2 = 0;
											player = 1;
											break;
										case '0':
											op4 = ' ';
											goto voltar3;
									}
								}
							case '0':
								op2 = ' ';
								goto voltar;
						}
					}
				case '2':  //CREDITOS 
					voltar2:
					limparTela();
					printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
					printf("\n\t\t\t" YEL "CRï¿½DITOS" RESET);
					sleep(2);	
					printf("\n\nDesenvolvimento:\n\n");
					sleep(1);
					printf("   [Jorge Luis] - Desenvolvedor\n");
					sleep(1);
					printf("   [Vitor Ferreira] - Desenvolvedor\n");
					sleep(1);
					printf("   [ï¿½ris Lins] - Desenvolvedor\n");
					sleep(1);
					printf("   [Rafael Queiroz] - Desenvolvedor de Testes\n\n");
					sleep(2);
					printf("Documentaï¿½ï¿½o:\n\n");
					sleep(1);
					printf("   [ï¿½ris Lins] - Especialista em Documentaï¿½ï¿½o\n");
					sleep(1);
					printf("   Sim, a que mais escreve errado kk");
					sleep(2);
					limparTela();
					printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
					printf("\n\t\t\t" YEL "CRï¿½DITOS" RESET);	
					printf("\n\nDesenvolvimento:\n\n");
					printf("   [Jorge Luis] - Desenvolvedor\n");
					printf("   [Vitor Ferreira] - Desenvolvedor\n");
					printf("   [ï¿½ris Lins] - Desenvolvedor\n");
					printf("   [Rafael Queiroz] - Desenvolvedor de Testes\n\n");
					printf("Documentaï¿½ï¿½o:\n\n");
					printf("   [ï¿½ris Lins] - Especialista em Documentaï¿½ï¿½o\n\n");
					sleep(2);
					printf("Equipe de Projeto:\n\n");
					sleep(1);
					printf("   [Jorge Luis] - Project Manager\n");
					sleep(1);
					printf("   [Vitor Ferreira] - Lï¿½der Tï¿½cnico\n");
					sleep(1);
					printf("   [ï¿½ris Lins] - Especialista em Documentaï¿½ï¿½o\n\n");
					sleep(2);
					printf("Agradecimentos Especiais:\n\n");
					sleep(1);
					printf("   [Leonardo Souto] - Mestre Supremo de League of Legends\n\n\n");
					
					sleep(1);
					printf("0 - VOLTAR\n");
					scanf(" %c", &op3);
					if (op3 != '0') {
						printf(RED "Nï¿½mero Invï¿½lido" RESET);
						sleep(1);
						limparTela();
						op3 = ' ';
						goto voltar2;
					}
					goto voltar;
					
				case '3': //REGRAS
					voltarMenuRegras:
					limparTela();
					printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
					printf("\n\t\t\t"YEL "REGRAS" RESET);
					printf("\n\n  1 - MODO SOLITï¿½RIO\n  2 - DOIS JOGADORES\n  3 - MODO PERSONALIZADO\n  0 - "RED"VOLTAR"RESET"\n  ");
					scanf(" %c", &op5);
						switch(op5){
							case '1':
								voltarRegras1:
								limparTela();
								printf("\n\t\t\tJOGO DO "YEL "CADERNO" RESET);
								printf("\n\t\t\t"YEL "REGRAS\n\n" RESET);
								printf("Batalha Naval - Modo Solitï¿½rio:\n\n");
								printf("  Objetivo:\n");
								printf("Encontrar e afundar os 3 navios no menor nï¿½mero possï¿½vel de tentativas.\n\n");
								printf("  Tabuleiro:\n");
								printf("O tabuleiro ï¿½ uma grade 5x5, numerado de 1 a 5 em ambas as linhas e colunas.\n\n");
								printf("  Navios:\n");
								printf("Hï¿½ 3 navios no tabuleiro, cada um ocupando uma ï¿½nica cï¿½lula.\n\n");
								printf("  Pontuaï¿½ï¿½o:\n");
								printf("Cada acerto ganha 100 pontos.\n");
								printf("Cada erro resulta em uma penalidade de 20 pontos.\n");
								printf("O jogo continua atï¿½ que todos os 3 navios sejam encontrados.\n\n");
								printf("  Jogabilidade:\n");	
								printf("O jogador escolhe uma posiï¿½ï¿½o no formato linha e coluna (por exemplo, 3 4).\n");
								printf("O jogo verifica se hï¿½ um navio nessa posiï¿½ï¿½o.\n");
								printf("Se acertar, o jogador ganha 100 pontos e ï¿½ informado sobre o acerto.\n");
								printf("Se errar, o jogador perde 20 pontos e ï¿½ informado sobre o erro.\n");
								printf("O jogador continua a escolher posiï¿½ï¿½es atï¿½ encontrar todos os 3 navios.\n");
								printf("O jogo termina quando todos os navios forem encontrados.\n\n");
								printf("  Regras Adicionais:\n");
								printf("A posiï¿½ï¿½o escolhida deve ser um nï¿½mero de 1 a 5 em ambas as coordenadas.\n\n");
								printf("0 - VOLTAR\n");
								scanf(" %c", &op5);
								if (op5 != '0') {
									printf(RED "Nï¿½mero Invï¿½lido" RESET);
									sleep(1);
									limparTela();
									op3 = ' ';
									goto voltarRegras1;
								}
								goto voltarMenuRegras;
							case '2':
								voltarRegras3:
								limparTela();
								printf("Batalha Naval - Modo Dois Jogadores:\n\n");
								printf("  Objetivo:\n");
								printf("Cada jogador tenta afundar os navios do oponente antes de ter seus prï¿½prios navios afundados.\n\n");
								printf("  Preparaï¿½ï¿½o:\n");
								printf("Cada jogador escolhe as posiï¿½ï¿½es para seus 3 navios no tabuleiro 5x5, sem que o oponente saiba.\n\n");
								printf("  Tabuleiro:\n");
								printf("O tabuleiro ï¿½ uma grade 5x5, numerado de 1 a 5 em ambas as linhas e colunas.\n\n");
								printf("  Navios:\n");
								printf("Cada jogador possui 3 navios. A posiï¿½ï¿½o de cada navio ï¿½ escolhida pelo jogador no inï¿½cio do jogo.\n\n");
								printf("  Pontuaï¿½ï¿½o:\n");
								printf("Cada acerto ganha 100 pontos.\n");
								printf("Cada erro resulta em uma penalidade de 20 pontos.\n");
								printf("O jogo continua atï¿½ que todos os navios de um jogador sejam afundados.\n\n");
								printf("  Jogabilidade:\n");
								printf("Os jogadores alternam entre escolher uma cï¿½lula no formato linha e coluna (por exemplo, 3 4) para atacar o oponente.\n");
								printf("O jogo verifica se hï¿½ um navio na cï¿½lula escolhida do oponente.\n");
								printf("Se acertar, o jogador ganha 100 pontos e ï¿½ informado sobre o acerto.\n");
								printf("Se errar, o jogador perde 20 pontos e ï¿½ informado sobre o erro.\n");
								printf("Os jogadores continuam alternando entre escolher cï¿½lulas atï¿½ que todos os navios de um jogador sejam afundados.\n");
								printf("O jogo termina quando todos os navios de um jogador forem afundados.\n\n");
								printf("  Regras Adicionais:\n");
								printf("A cï¿½lula escolhida deve ser um nï¿½mero de 1 a 5 em ambas as coordenadas.\n\n");
								printf("  Exemplo de Feedback:\n");
								printf("Acertou! +100 pontos.\n");
								printf("Errou! -20 pontos. Tente novamente.\n\n");
								printf("0 - VOLTAR\n");
								scanf(" %c", &op5);
								if (op5 != '0') {
									printf(RED "Nï¿½mero Invï¿½lido" RESET);
									sleep(1);
									limparTela();
									op3 = ' ';
									goto voltarRegras2;
								}
								goto voltarMenuRegras;
							case '3':
								voltarRegras2:
								limparTela();
								printf("Batalha Naval - Modo Personalizado:\n\n");
								printf("  Objetivo:\n");
								printf("Os jogadores (ou jogador solitï¿½rio) tentam afundar os navios do oponente (ou do prï¿½prio no modo solitï¿½rio) antes de ter seus prï¿½prios navios afundados.\n\n");
								printf("  Configuraï¿½ï¿½o:\n");
								printf("Escolha o modo de jogo:\n");
								printf("Solitï¿½rio: O jogador define o tamanho do tabuleiro (de 2 a 15) e\n as posiï¿½ï¿½es dos 3 navios sï¿½o automï¿½tica.\n");
								printf("Dois Jogadores: Cada jogador define o tamanho do tabuleiro (de 2 a 10) \ne escolhe as posiï¿½ï¿½es para seus 3 navios.\n\n");
								printf("  Tabuleiro:\n");
								printf("O tabuleiro ï¿½ uma grade de tamanho definido pelo jogador, numerado de 1 atï¿½ o tamanho do tabuleiro em ambas as linhas e colunas.\n\n");
								printf("  Navios:\n");
								printf("Cada jogador possui 3 navios. As posiï¿½ï¿½es de cada navio sï¿½o escolhidas pelo(s) jogador(es) no inï¿½cio do jogo,\nou configuradas automaticamente no modo solitï¿½rio.\n\n");
								printf("  Jogabilidade:\n");
								printf("Os jogadores (ou jogador solitï¿½rio) alternam entre escolher uma cï¿½lula no formato linha e coluna (por exemplo, 3 4) para atacar o oponente.\n");
								printf("O jogo verifica se hï¿½ um navio na cï¿½lula escolhida do oponente (ou do prï¿½prio no modo solitï¿½rio).\n");
								printf("Se acertar, o jogador ï¿½ informado sobre o acerto.\n");
								printf("Se errar, o jogador ï¿½ informado sobre o erro.\n");
								printf("Os jogadores continuam alternando entre escolher cï¿½lulas atï¿½ que todos os navios de um jogador sejam afundados.\n");
								printf("O jogo termina quando todos os navios de um jogador forem afundados.\n\n");
								printf("  Regras Adicionais:\n");
								printf("A cï¿½lula escolhida deve ser um nï¿½mero de 1 atï¿½ o tamanho do tabuleiro em ambas as coordenadas.\n");
								printf("Nï¿½o hï¿½ sistema de pontuaï¿½ï¿½o; o objetivo ï¿½ simplesmente afundar todos os navios.\n");
								printf("Se um jogador atingir o objetivo antes do outro, ou se o jogador solitï¿½rio afundar os navios, o jogo termina.\n\n");
								printf("0 - VOLTAR\n");
								scanf(" %c", &op5);
								if (op5 != '0') {
									printf(RED "Nï¿½mero Invï¿½lido" RESET);
									sleep(1);
									limparTela();
									op3 = ' ';
									goto voltarRegras3;
								}
								goto voltarMenuRegras;
							case '0':
								goto voltar;		
						}
				case '0':  //SAIR DO JOGO
					op1 = ' ';
					return 0;
				default:
					continue;
				}
		} else {
			printf(RED "\nNï¿½mero Invï¿½lido" RESET);
			sleep(1);
			limparTela();
			continue;
		}
	}
}

