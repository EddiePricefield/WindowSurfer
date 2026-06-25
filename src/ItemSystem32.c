/**
 * @file ItemSystem32.c
 * @author @EddiePricefield & @rogerioccastro
 * @brief Implementação do Item (System32).
 *
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#include "Animacao.h"
#include "ItemSystem32.h"
#include "Macros.h"
#include "ResourceManager.h"
#include "Tipos.h"
#include "GameWorld.h"

static void desenharQuadroAnimacaoItemSystem32( ItemSystem32 *item, QuadroAnimacao *qa, Color tonalidade );
static Animacao *getAnimacaoAtualItemSystem32( ItemSystem32 *item );

extern bool debug;

/**
 * @brief Cria um novo Item (system32).
 */
ItemSystem32 *criarItemSystem32( Rectangle ret, Color cor ) {

    ItemSystem32 *novoItem = (ItemSystem32*) malloc( sizeof( ItemSystem32 ) );

    novoItem->ret = ret;
    novoItem->cor = cor;
    novoItem->estado = ESTADO_ITEM_SYSTEM32_PARADO;
    novoItem->ativo = true;

    int quantidadeAnimacoes = 0;

    novoItem->animacaoParado.quantidadeQuadros = 1;
    novoItem->animacaoParado.quadroAtual = 0;
    novoItem->animacaoParado.contadorTempoQuadro = 0.0f;
    novoItem->animacaoParado.pararNoUltimoQuadro = false;
    novoItem->animacaoParado.executarUmaVez = false;
    novoItem->animacaoParado.finalizada = false;
    criarQuadrosAnimacao( &novoItem->animacaoParado, novoItem->animacaoParado.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoItem->animacaoParado.quadros,
        novoItem->animacaoParado.quantidadeQuadros,
        250,             // duração padrão para todos os quadros
        1, 1,           // início
        450, 372,          // dimensões
        2,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            0
        }
    );

    novoItem->animacaoColetando.quantidadeQuadros = 4;
    novoItem->animacaoColetando.quadroAtual = 0;
    novoItem->animacaoColetando.contadorTempoQuadro = 0.0f;
    novoItem->animacaoColetando.pararNoUltimoQuadro = false;
    novoItem->animacaoColetando.executarUmaVez = true;
    novoItem->animacaoColetando.finalizada = false;
    criarQuadrosAnimacao( &novoItem->animacaoColetando, novoItem->animacaoColetando.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoItem->animacaoColetando.quadros,
        novoItem->animacaoColetando.quantidadeQuadros,
        80,               // duração padrão para todos os quadros
        1, 18,            // início
        16, 16,           // dimensões
        1,                // separação
        false,            // de trás para frente
        (Rectangle) { 0 } // retângulo de colisão padrão para cada quadro
    );

    novoItem->animacoes[ESTADO_ITEM_SYSTEM32_PARADO] = &novoItem->animacaoParado; quantidadeAnimacoes++;
    novoItem->animacoes[ESTADO_ITEM_SYSTEM32_COLETADO] = &novoItem->animacaoColetando; quantidadeAnimacoes++;
    novoItem->quantidadeAnimacoes = quantidadeAnimacoes;

    return novoItem;

}

/**
 * @brief Destroi um item (system32).
 */
void destruirItemSystem32( ItemSystem32 *item ) {
    if ( item != NULL ) {
        for ( int i = 0; i < item->quantidadeAnimacoes; i++ ) {
            destruirQuadrosAnimacao( item->animacoes[i] );
        }
        free( item );
    }
}

/**
 * @brief Atualiza um item (system32).
 */
void atualizarItemSystem32( ItemSystem32 *item, float delta ) {
    if ( item->ativo ) {
        Animacao *animacaoAtual = getAnimacaoAtualItemSystem32( item );
        atualizarAnimacao( animacaoAtual, delta );
        if ( item->estado == ESTADO_ITEM_SYSTEM32_COLETADO && animacaoAtual->finalizada ) {
            item->ativo = false;
            return;
        }
    }
}

/**
 * @brief Desenha um item (system32).
 */
void desenharItemSystem32( ItemSystem32 *item ) {
    if ( item->ativo ) {
        QuadroAnimacao *qa = getQuadroAnimacaoAtualItemSystem32( item );
        desenharQuadroAnimacaoItemSystem32( item, qa, WHITE );
        if ( debug ) {
            DrawRectangleRec( item->ret, Fade( item->cor, 0.5f ) );
            DrawRectangleLines( item->ret.x, item->ret.y, item->ret.width, item->ret.height, BLACK );
        }
    }
}

/**
 * @brief Obtém o quadro de animação atual de um item (system32).
 */
QuadroAnimacao *getQuadroAnimacaoAtualItemSystem32( ItemSystem32 *item ) {
    return getQuadroAtualAnimacao( getAnimacaoAtualItemSystem32( item ) );
}

static void desenharQuadroAnimacaoItemSystem32( ItemSystem32 *item, QuadroAnimacao *qa, Color tonalidade ) {

    if ( qa != NULL ) {

        DrawTexturePro(
            rm.texturaSystem32,
            qa->fonte,
            item->ret,
            (Vector2) { 0 },
            0.0f,
            tonalidade
        );

        if ( debug ) {
            float xDesenho = item->ret.x + qa->retColisao.x;
            float yDesenho = item->ret.y + qa->retColisao.y;
            DrawRectangle( xDesenho, yDesenho, qa->retColisao.width, qa->retColisao.height, Fade( GREEN, 0.5f ) );
        }

    }

}

static Animacao *getAnimacaoAtualItemSystem32( ItemSystem32 *item ) {
    return item->animacoes[item->estado];
}