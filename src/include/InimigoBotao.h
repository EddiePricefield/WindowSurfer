/**
 * @file Obstaculo.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Inimigo (Botao).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo inimigo (botao).
 */
InimigoBotao *criarInimigoBotao( Rectangle ret, Color cor );

/**
 * @brief Destroi um inimigo (botao).
 */
void destruirInimigoBotao( InimigoBotao *inimigo );

/**
 * @brief Atualiza um inimigo (botao).
 */
void atualizarInimigoBotao( InimigoBotao *inimigo, GameWorld *gw,float delta );

/**
 * @brief Desenha um inimigo (botao).
 */
void desenharInimigoBotao( InimigoBotao *inimigo );

/**
 * @brief Obtém o quadro de animação atual de um inimigo (botao).
 */
QuadroAnimacao *getQuadroAnimacaoAtualInimigoBotao( InimigoBotao *inimigo );