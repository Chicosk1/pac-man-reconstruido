#ifndef MAPA_H
#define MAPA_H
#include "entidades.h"

// Structure
struct mapa {
    char** matriz;
    int linhas, colunas;
};

typedef struct mapa MAPA;

struct posicao {
    int x, y;
};

typedef struct posicao LOCALIZACAO;

extern MAPA m;
extern LOCALIZACAO jogador;

// Header Files
void copiaMapa(MAPA* destino, MAPA* origem);
int acabou();
int direcaoValida(char direcao);
int validacaoDeLimites(MAPA* m, int x, int y);
int validaDirecaoVazia(MAPA* m, int x, int y);
void locomoverNoMapa(MAPA* m, int xorigem, int yorigem, int xDestino, int yDestino);
void alocarMemoria(MAPA* m);
void liberarMemoriaAlocada(MAPA* m);
void lerMapa(MAPA* m);
void imprimirMapa(MAPA* m);
int encontrarPosicaoMapa(MAPA* m, LOCALIZACAO* jogador, char c);

#endif