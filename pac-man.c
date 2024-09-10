#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "jogador.h"

// Declaração de Váriaveis Globais
MAPA m;
LOCALIZACAO jogador;

void inimigos() {

    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++) {
        for(int j = 0; j < m.colunas; j++) {
            if(copia.matriz[i][j] == FANTASMA) {

                int xdestino;
                int ydestino;

                int encontrou = direcionamentoInimigos(i, j, &xdestino, &ydestino);

                if(encontrou) {
                    andanomapa(&m, i, j, xdestino, ydestino);
                }
            }

        }
    }

    liberarMemoriaAlocada(&copia);

}

int direcionamentoInimigos(int xatual, int yatual, int* xdestino, int* ydestino) {

    int opcoes[4][2] = { 
        { xatual   , yatual+1 }, 
        { xatual+1 , yatual   },  
        { xatual   , yatual-1 }, 
        { xatual-1 , yatual   }
    };

    srand(time(0));

    for(int i = 0; i < 10; i++) {

        int posicao = rand() % 4;

        if(validacaoDeLimites(&m, opcoes[posicao][0], opcoes[posicao][1]) && validaDirecaoVazia(&m, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }

    return 0;
}

void copiaMapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;
    alocarMemoria(destino);
    for(int i = 0; i < origem->linhas; i++) {
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

int acabou() {
    return 0;
}

int direcaoValida(char direcao) {
    return direcao == 'a' || direcao == 'w' || direcao == 's' || direcao == 'd';
}

int validacaoDeLimites(MAPA* m, int x, int y) {
    if(x >= m->linhas) {
        return 0;
    }
    if(y >= m->colunas){
        return 0;
    } 

    return 1;    
}

int validaDirecaoVazia(MAPA* m, int x, int y) {
    return m->matriz[x][y] == '.';
}

void locomoverNoMapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino) {

    char personagem = m->matriz[xorigem][yorigem];
    m->matriz[xdestino][ydestino] = personagem;
    m->matriz[xorigem][yorigem] = '.';

}

void moverJogador(char direcao) {

    // Validação para verificar se é uma direção valida
    if(!direcaoValida(direcao)){
        return;
    }

    int validaX = jogador.x;
    int validaY = jogador.y;

    // Switch case para mover o Jogador
    switch(direcao) {
        case 'a': // Esquerda
            validaY--;
            break;
        case 'w': // Cima
            validaX--;
            break;
        case 's': // Baixo
            validaX++;
            break;
        case 'd': // Direita
            validaY++;
            break;
    }

    // Validação para verificar se o jogador está nos limites do mapa
    if(!validacaoDeLimites(&m, validaX, validaY)){
        return;
    }

    locomoverNoMapa(&m, jogador.x, jogador.y, validaX, validaY);

}

int main() {

    char comando;

    lerMapa(&m);
    encontrarPosicaoMapa(&m, &jogador, '@');
    do{

        imprimirMapa(&m);
        scanf(" %c", &comando);
        moverJogador(comando);
        inimigos();

    }while(!acabou());

    liberarMemoriaAlocada(&m);

}