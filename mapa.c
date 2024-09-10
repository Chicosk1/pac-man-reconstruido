#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include "jogador.h"

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

    fclose(arquivo);
}

// Função para imprimir o mapa na tela
void imprimirMapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        printf("%s\n", m->matriz[i]);
    }
}

// Função para encontrar a posição do jogador no mapa
void encontrarPosicaoMapa(MAPA* m, LOCALIZACAO* jogador, char c) {
    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j < m->colunas; j++) {
            if(m->matriz[i][j] == c) {
                jogador->x = i;
                jogador->y = j;
                return;
            }
        }
    }
}