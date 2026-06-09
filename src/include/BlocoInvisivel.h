/**
 * @file BlocoInvisivel.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Bloco Invisível.
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "raylib/raylib.h"

#include "Tipos.h"

/**
 * @brief Cria um novo bloco invisível.
 */
BlocoInvisivel *criarBlocoInvisivel( Rectangle ret );

/**
 * @brief Destroi um bloco invisível.
 */
void destruirBlocoInvisivel( BlocoInvisivel *blocoInvis );

/**
 * @brief Desenha um bloco invisível.
 */
void desenharBlocoInvisivel( BlocoInvisivel *blocoInvis );