/**
 * @file InimigoBoss.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Inimigo (Boss).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo inimigo (boss).
 */
InimigoBoss *criarInimigoBoss( Rectangle ret, Color cor );

/**
 * @brief Destroi um inimigo (boss).
 */
void destruirInimigoBoss( InimigoBoss *inimigo );

/**
 * @brief Atualiza um inimigo (boss).
 */
void atualizarInimigoBoss( InimigoBoss *inimigo, GameWorld *gw,float delta );

/**
 * @brief Desenha um inimigo (boss).
 */
void desenharInimigoBoss( InimigoBoss *inimigo );

/**
 * @brief Obtém o quadro de animação atual de um inimigo (boss).
 */
QuadroAnimacao *getQuadroAnimacaoAtualInimigoBoss( InimigoBoss *inimigo );