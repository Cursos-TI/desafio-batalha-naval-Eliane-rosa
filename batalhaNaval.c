#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define NAVIOS 3
#define TENTATIVAS 7

// Função para inicializar o tabuleiro do jogador
void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

// Função para posicionar navios aleatoriamente
void posicionarNavios(int navios_linha[NAVIOS], int navios_col[NAVIOS]) {
    int count = 0;
    while (count < NAVIOS) {
        int linha = rand() % TAM;
        int col = rand() % TAM;
        int ocupado = 0;
        for (int i = 0; i < count; i++) {
            if (navios_linha[i] == linha && navios_col[i] == col) {
                ocupado = 1;
                break;
            }
        }
        if (!ocupado) {
            navios_linha[count] = linha;
            navios_col[count] = col;
            count++;
        }
    }
}

// Função para mostrar o tabuleiro
void mostrarTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("  0 1 2 3 4\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char tabuleiro[TAM][TAM];
    int navios_linha[NAVIOS], navios_col[NAVIOS];
    int acertos = 0, tentativas = 0;

    srand(time(NULL));
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(navios_linha, navios_col);

    printf("Bem-vindo ao Batalha Naval!\n");

    while (tentativas < TENTATIVAS && acertos < NAVIOS) {
        mostrarTabuleiro(tabuleiro);

        int linha, col;
        printf("Digite linha (0-4): ");
        scanf("%d", &linha);
        printf("Digite coluna (0-4): ");
        scanf("%d", &col);

        int acertou = 0;
        for (int i = 0; i < NAVIOS; i++) {
            if (navios_linha[i] == linha && navios_col[i] == col) {
                acertou = 1;
                break;
            }
        }
        if (acertou && tabuleiro[linha][col] != 'X') {
            printf("Acertou um navio!\n");
            tabuleiro[linha][col] = 'X';
            acertos++;
        } else if (tabuleiro[linha][col] == '~' || tabuleiro[linha][col] == 'X') {
            printf("Você já atirou aqui!\n");
        } else {
            printf("Água!\n");
            tabuleiro[linha][col] = '~';
        }
        tentativas++;
    }

    mostrarTabuleiro(tabuleiro);

    if (acertos == NAVIOS) {
        printf("Parabéns! Você afundou todos os navios!\n");
    } else {
        printf("Você perdeu! Os navios estavam nas posições:\n");
        for (int i = 0; i < NAVIOS; i++) {
            printf("Navio %d: Linha %d, Coluna %d\n", i + 1, navios_linha[i], navios_col[i]);
        }
    }

    return 0;
}
