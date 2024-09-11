#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mapa.h"
#include "entidades.h"

// Declaração de Structures
MAPA m;
LOCALIZACAO jogador;

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

    return 0;

}