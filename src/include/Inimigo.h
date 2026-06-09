/**
 * @file Obstaculo.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief Declarações das funções do Inimigo.
 *
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Tipos.h"

/**
 * @brief Cria um novo inimigo.
 */
Inimigo *criarInimigo( TipoInimigo tipo );

/**
 * @brief Destroi um inimigo.
 */
void destruirInimigo( Inimigo *inimigo );

/**
 * @brief Atualiza um inimigo.
 */
void atualizarInimigo( Inimigo *inimigo, GameWorld *gw, float delta );

/**
 * @brief Desenha um inimigo.
 */
void desenharInimigo( Inimigo *inimigo );

/**
 * @brief Resolve colisões do inimigo com o mapa no eixo X.
 */
void resolverColisaoInimigoObstaculosMapaX( Inimigo *inimigo, Mapa *mapa );

/**
 * @brief Resolve colisões do inimigo com o mapa no eixo Y.
 */
void resolverColisaoInimigoObstaculosMapaY( Inimigo *inimigo, Mapa *mapa );

/**
 * @brief Resolve colisões do inimigo com o bloco invisivel no eixo X.
 */
void resolverColisaoInimigoBlocoInvisivelMapaX( Inimigo *inimigo, Mapa *mapa );

/**
 * @brief Resolve colisões do inimigo com o bloco invisivel no eixo Y.
 */
void resolverColisaoInimigoBlocoInvisivelMapaY( Inimigo *inimigo, Mapa *mapa );