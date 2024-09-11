#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mapa.h"
#include "entidades.h"

// Função que possui a inteligencia principal dos inimigos
void inimigos() {

    MAPA copia;

    copiaMapa(&copia, &m);
    
    // Loop para percorrer o mapa
    for(int i = 0; i < m.linhas; i++) {
        for(int j = 0; j < m.colunas; j++) {
            if(copia.matriz[i][j] == 'F') {

                int xDestino;
                int yDestino;
                
                // Determina a posição destino do inimigo
                int encontrou = direcionamentoInimigos(i, j, &xDestino, &yDestino);

                if(encontrou) {
                    locomoverNoMapa(&m, i, j, xDestino, yDestino);
                }
            }

        }
    }

    liberarMemoriaAlocada(&copia);

}

// Função que valida os direcionamento dos inimigos
int direcionamentoInimigos(int xAtual, int yAtual, int* xDestino, int* yDestino) {

    // Array que define as direções que o inimigo pode se mover
    int opcoes[4][2] = { 
        { xAtual   , yAtual+1 }, 
        { xAtual+1 , yAtual   },  
        { xAtual   , yAtual-1 }, 
        { xAtual-1 , yAtual   }
    };

    srand(time(0));
                    // opcoes.length() em C?
    for(int i = 0; i < 10; i++) {

        // Seleciona alguma direção aleatóriamente
        int posicao = rand() % 4;

        // Validação onde descobre se o inimigo pode andar ou não
        if(     validacaoDeLimites (&m, opcoes[posicao][0], opcoes[posicao][1]) &&   
                validaDirecaoVazia (&m, opcoes[posicao][0], opcoes[posicao][1])      ) {
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];

            // Encontrou uma posição valida
            return 1;
        }
    }
    // Não encontrou uma posição valida
    return 0;
}

// Função para mover o Jogador
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
