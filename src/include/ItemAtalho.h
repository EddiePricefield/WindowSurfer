/**
 * @file ItemAtalho.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Item (Atalho).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo item (atalho).
 */
ItemAtalho *criarItemAtalho( Rectangle ret, Color cor );

/**
 * @brief Destroi um item (atalho).
 */
void destruirItemAtalho( ItemAtalho *item );

/**
 * @brief Atualiza um item (atalho).
 */
void atualizarItemAtalho( ItemAtalho *item, float delta );

/**
 * @brief Desenha um item (atalho).
 */
void desenharItemAtalho( ItemAtalho *item );

/**
 * @brief Obtém o quadro de animação atual de um item (atalho).
 */
QuadroAnimacao *getQuadroAnimacaoAtualItemAtalho( ItemAtalho *item );