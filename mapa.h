#ifndef MAPA_H
#define MAPA_H
#include "jogador.h"

// Structures
struct mapa {
    char** matriz;
    int linhas, colunas;
};

typedef struct mapa MAPA;

// Header Files
void liberarMemoriaAlocada(MAPA* m);
void alocarMemoria(MAPA* m);
void lerMapa(MAPA* m);
void imprimirMapa(MAPA* m);
void encontrarPosicaoMapa(MAPA* m, LOCALIZACAO* jogador, char c);
int direcaoValida(char direcao);
int validacaoDeLimites(MAPA* m, int x, int y);
int validaDirecaoVazia(MAPA* m, int x, int y);
void locomoverNoMapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
#endif