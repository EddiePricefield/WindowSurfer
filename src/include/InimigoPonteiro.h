/**
 * @file Inimigoponteiro.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Inimigo (Ponteiro).
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo inimigo (ponteiro).
 */
InimigoPonteiro *criarInimigoPonteiro( Rectangle ret, Color cor );

/**
 * @brief Destroi um inimigo (ponteiro).
 */
void destruirInimigoPonteiro( InimigoPonteiro *inimigo );

/**
 * @brief Atualiza um inimigo (ponteiro).
 */
void atualizarInimigoPonteiro( InimigoPonteiro *inimigo, GameWorld *gw,float delta );

/**
 * @brief Desenha um inimigo (ponteiro).
 */
void desenharInimigoPonteiro( InimigoPonteiro *inimigo );

/**
 * @brief Obtém o quadro de animação atual de um inimigo (ponteiro).
 */
QuadroAnimacao *getQuadroAnimacaoAtualInimigoPonteiro( InimigoPonteiro *inimigo );