/**
 * @file ItemSystem32.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Item (System32).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo item (system32).
 */
ItemSystem32 *criarItemSystem32( Rectangle ret, Color cor );

/**
 * @brief Destroi um item (system32).
 */
void destruirItemSystem32( ItemSystem32 *item );

/**
 * @brief Atualiza um item (system32).
 */
void atualizarItemSystem32( ItemSystem32 *item, float delta );

/**
 * @brief Desenha um item (system32).
 */
void desenharItemSystem32( ItemSystem32 *item );

/**
 * @brief Obtém o quadro de animação atual de um item (system32).
 */
QuadroAnimacao *getQuadroAnimacaoAtualItemSystem32( ItemSystem32 *item );