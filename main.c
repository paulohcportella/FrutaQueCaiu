#include "cli-lib/screen.h"
#include "cli-lib/keyboard.h"
#include "cli-lib/timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CESTA_WIDTH 9
#define SCREEN_BOTTOM (MAXY - 2)
#define FRUTA_SYMBOLS 5
#define TEMPO_LIMITE 60
#define FRUTA_PROBABILIDADE 2
#define MAX_NAME 50
#define LEADERBOARD_FILE "leaderboard.txt"
#define MOVIMENTO_CESTA 2

typedef struct Fruta {
    char* simbolo;
    int cor;
    int pontos;
    int x, y;
    struct Fruta* prox;
} Fruta;

typedef struct {
    int x;
} Cesta;

char* simbolos_frutas[FRUTA_SYMBOLS] = {"🍎", "🍌", "🍇", "🥝", "🍊"};
int pontos_frutas[FRUTA_SYMBOLS] = {10, 20, 30, 50, 40};

Fruta* frutas = NULL;
int score = 0;
int tempo_decorrido = 0;

void usarBufferAlternativo() {
    printf("\033[?1049h");
}

void sairBufferAlternativo() {
    printf("\033[?1049l");
}

void desenharLimites() {
    for (int y = 1; y <= SCREEN_BOTTOM; y++) {
        screenSetColor(WHITE, BLACK);
        screenGotoxy(0, y);
        printf("|");
        screenGotoxy(MAXX - 1, y);
        printf("|");
    }
    for (int x = 0; x < MAXX; x++) {
        screenSetColor(WHITE, BLACK);
        screenGotoxy(x, SCREEN_BOTTOM + 1);
        printf("_");
    }
}

void desenharCesta(Cesta *cesta) {
    screenSetColor(BROWN, BLACK);
    for (int i = 0; i < CESTA_WIDTH; i++) {
        screenGotoxy(cesta->x + i, SCREEN_BOTTOM);
        printf("=");
    }
}

void desenharFrutas() {
    Fruta* atual = frutas;
    while (atual) {
        screenGotoxy(atual->x, atual->y);
        printf("  ");
        atual = atual->prox;
    }

    atual = frutas;
    while (atual) {
        screenSetColor(atual->cor, BLACK);
        screenGotoxy(atual->x, atual->y);
        printf("%s", atual->simbolo);
        atual = atual->prox;
    }
}

void adicionarFruta() {
    Fruta* nova = (Fruta*)malloc(sizeof(Fruta));
    int tipo = rand() % FRUTA_SYMBOLS;
    nova->simbolo = simbolos_frutas[tipo];
    nova->pontos = pontos_frutas[tipo];
    nova->cor = WHITE + tipo;
    nova->x = (rand() % (MAXX - 4)) + 2;
    nova->y = 2;
    nova->prox = frutas;
    frutas = nova;
}

void atualizarFrutas(Cesta* cesta) {
    Fruta* atual = frutas;
    Fruta* anterior = NULL;

    while (atual) {
        atual->y++;

        if (atual->y >= SCREEN_BOTTOM) {
            if (atual->x >= cesta->x && atual->x <= cesta->x + CESTA_WIDTH) {
                score += atual->pontos;
            }
            Fruta* temp = atual;
            if (anterior) anterior->prox = atual->prox;
            else frutas = atual->prox;
            atual = atual->prox;
            free(temp);
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

void destruirFrutas() {
    Fruta* atual = frutas;
    while (atual) {
        Fruta* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    frutas = NULL;
}

void salvarScore(int pontuacao) {
    FILE* f = fopen(LEADERBOARD_FILE, "a");
    if (f) {
        fprintf(f, "Player: %d pontos\n", pontuacao);
        fclose(f);
    }
}

void mostrarTopScore() {
    FILE* f = fopen(LEADERBOARD_FILE, "r");
    int max = -1;
    if (f) {
        char linha[100];
        while (fgets(linha, sizeof(linha), f)) {
            int p = 0;
            if (sscanf(linha, "Player: %d pontos", &p) == 1) {
                if (p > max) max = p;
            }
        }
        fclose(f);
    }

    screenClear();
    desenharLimites();
    screenGotoxy(10, 10);
    if (max == -1) {
        printf("Nenhum score registrado ainda.");
    } else {
        printf("Top score: %d pontos", max);
    }
    screenGotoxy(10, 12);
    printf("Pressione qualquer tecla para voltar ao menu...");
    screenUpdate();
    readch();
}

void desenharHUD(int tempo_restante) {
    screenSetColor(WHITE, BLACK);
    screenGotoxy(2, 1);
    printf("Pontos: %d", score);

    screenGotoxy(MAXX - 20, 1);
    printf("Tempo restante: %ds", tempo_restante);

    screenGotoxy((MAXX / 2) - 10, 1);
    printf("Fruta que Caiu 🍎🍌🍇🥝🍊");
}

void jogar() {
    int ch = 0;
    Cesta cesta;
    cesta.x = (MAXX - CESTA_WIDTH) / 2;
    time_t inicio = time(NULL);
    srand(time(NULL));
    score = 0;
    tempo_decorrido = 0;

    screenClear();
    timerInit(60);

    while (ch != 10 && (tempo_decorrido = (int)(time(NULL) - inicio)) < TEMPO_LIMITE) {
        if (keyhit()) {
            ch = readch();
            if (ch == 68 && cesta.x > 1) cesta.x -= MOVIMENTO_CESTA;
            if (ch == 67 && cesta.x + CESTA_WIDTH < MAXX - 1) cesta.x += MOVIMENTO_CESTA;
        }

        if (timerTimeOver()) {
            screenClear();
            desenharLimites();

            if (rand() % 10 < FRUTA_PROBABILIDADE) adicionarFruta();
            atualizarFrutas(&cesta);

            desenharFrutas();
            desenharCesta(&cesta);
            desenharHUD(TEMPO_LIMITE - tempo_decorrido);
            screenUpdate();
        }
    }

    destruirFrutas();
    salvarScore(score);

    screenClear();
    desenharLimites();
    screenGotoxy(10, 10);
    printf("Fim de jogo! Pontuação: %d\n", score);
    screenGotoxy(10, 12);
    mostrarTopScore();
    screenUpdate();
}

void menuPrincipal() {
    while (1) {
        screenClear();
        desenharLimites();

        screenGotoxy(10, 3);
        printf("--- Fruta que Caiu ---");
        screenGotoxy(10, 5);
        printf("Instruções:");
        screenGotoxy(10, 6);
        printf("- Use as setas esquerda e direita para mover a cesta.");
        screenGotoxy(10, 7);
        printf("- Pegue as frutas que caem para somar pontos.");
        screenGotoxy(10, 8);
        printf("- Pressione ENTER para encerrar a partida.");

        screenGotoxy(10, 10);
        printf("1. Jogar");
        screenGotoxy(10, 11);
        printf("2. Ver Top Score");
        screenGotoxy(10, 12);
        printf("3. Sair");
        screenGotoxy(10, 14);
        printf("Escolha uma opção: ");
        screenUpdate();

        char ch = readch();
        if (ch == '1') jogar();
        else if (ch == '2') mostrarTopScore();
        else if (ch == '3') break;
    }
}

int main() {
    usarBufferAlternativo();
    screenInit(1);
    keyboardInit();
    menuPrincipal();
    keyboardDestroy();
    screenDestroy();
    sairBufferAlternativo();
    return 0;
}
