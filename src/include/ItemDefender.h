/**
 * @file ItemDefender.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Item (Defender).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo item (defender).
 */
ItemDefender *criarItemDefender( Rectangle ret, Color cor );

/**
 * @brief Destroi um item (defender).
 */
void destruirItemDefender( ItemDefender *item );

/**
 * @brief Atualiza um item (defender).
 */
void atualizarItemDefender( ItemDefender *item, float delta );

/**
 * @brief Desenha um item (defender).
 */
void desenharItemDefender( ItemDefender *item );

/**
 * @brief Obtém o quadro de animação atual de um item (defender).
 */
QuadroAnimacao *getQuadroAnimacaoAtualItemDefender( ItemDefender *item );