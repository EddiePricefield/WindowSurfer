/**
 * @file BlocoInvisivel.c
 * @author @EddiePricefield & @rogerioccastro
 * @brief Implementação do Bloco Invisível.
 *
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#include "BlocoInvisivel.h"
#include "Tipos.h"

/**
 * @brief Cria um novo bloco invisível.
 */
BlocoInvisivel *criarBlocoInvisivel( Rectangle ret ) {

    BlocoInvisivel *novoBlocoInvisivel = (BlocoInvisivel*) malloc( sizeof( BlocoInvisivel ) );

    novoBlocoInvisivel->ret = ret;

    return novoBlocoInvisivel;

}

/**
 * @brief Destroi um bloco invisível.
 */
void destruirBlocoInvisivel( BlocoInvisivel *blocoInvis ) {
    free( blocoInvis );
}

/**
 * @brief Desenha um bloco invisível.
 */
void desenharBlocoInvisivel( BlocoInvisivel *blocoInvis ) {

    DrawRectanglePro(
        blocoInvis->ret,
        (Vector2) { 0 },
        0.0f,
        BLANK
    );

}