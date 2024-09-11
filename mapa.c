#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entidades.h"
#include "mapa.h"

// Função para alocar memória para o mapa
void alocarMemoria(MAPA* m) {

    m->matriz = malloc(sizeof(char*) * m->linhas);

    for(int i = 0; i < m->linhas; i++) {

        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));

    }
}

// Função para liberar a memória alocada do mapa
void liberarMemoriaAlocada(MAPA* m) {

    for(int i = 0; i < m->linhas; i++) {

        free(m->matriz[i]);

    }

    free(m->matriz);

}

// Função para ler o mapa de um arquivo
void lerMapa(MAPA* m) {
    // Abrindo mapa.txt
    FILE* arquivo = fopen("mapa.txt", "r");
    if(arquivo == 0) {
        printf("Erro na leitura do arquivo do mapa!\n");
        exit(1);
    }

    fscanf(arquivo, "%d %d", &(m->linhas), &(m->colunas));  // Lê as dimensões do mapa
    alocarMemoria(m);

    for(int i = 0; i < m->linhas; i++) {
        fscanf(arquivo, "%s", m->matriz[i]);  // Lê cada linha do mapa
    }

    // Fechando mapa.txt
    fclose(arquivo);

}

// Função para imprimir o mapa na tela
void imprimirMapa(MAPA* m) {

    for(int i = 0; i < m->linhas; i++) {

        printf("%s\n", m->matriz[i]);

    }

}

// Função para encontrar a posição do jogador no mapa
int encontrarPosicaoMapa(MAPA* m, LOCALIZACAO* jogador, char c) {

    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j < m->colunas; j++) {

            if(m->matriz[i][j] == c) {

                jogador->x = i;
                jogador->y = j;
                return 1;

            }
        }
    }

    return 0;

}

// Função para copiar o mapa
void copiaMapa(MAPA* destino, MAPA* origem) {

    // Copiando o mapa de origem 
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocarMemoria(destino);

    // Loop para percorrer as linhas do mapa
    for(int i = 0; i < origem->linhas; i++) {

        // Função que copia as Strings do mapa origem
        strcpy(destino->matriz[i], origem->matriz[i]);

    }
}

// Função que verifica se o jogo acabou ou não
int acabou() {

    int encontrarJogador = encontrarPosicaoMapa(&m, &jogador, '@');

    return !encontrarJogador;

}

// Função que verifica se a direção é válida ou não
int direcaoValida(char direcao) {

    return direcao == 'a' || direcao == 'w' || 
           direcao == 's' || direcao == 'd'   ;

}

// Função que verifica os limites do mapa
int validacaoDeLimites(MAPA* m, int x, int y) {

    if(x >= m->linhas) {
        return 0;
    }
    if(y >= m->colunas){
        return 0;
    } 

    return 1; 

}

// Função que verifica se a direção é vazia ou não
int validaDirecaoVazia(MAPA* m, int x, int y) {

    return m->matriz[x][y] == '.';

}

// Função para se mover no mapa
void locomoverNoMapa(MAPA* m, int xorigem, int yorigem, int xDestino, int yDestino) {

    char personagem = m->matriz[xorigem][yorigem];

    m->matriz[xDestino][yDestino] = personagem;
    m->matriz[xorigem][yorigem] = '.';

}