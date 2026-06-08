/**
 * @file ItemAtalho.c
 * @author @EddiePricefield & @rogerioccastro
 * @brief Implementação do Item (Atalho).
 *
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#include "Animacao.h"
#include "ItemAtalho.h"
#include "Macros.h"
#include "ResourceManager.h"
#include "Tipos.h"
#include "GameWorld.h"

static void desenharQuadroAnimacaoItemAtalho( ItemAtalho *item, QuadroAnimacao *qa, Color tonalidade );
static Animacao *getAnimacaoAtualItemAtalho( ItemAtalho *item );

static const bool MOSTRAR_RETANGULOS = false;

/**
 * @brief Cria um novo Item (atalho).
 */
ItemAtalho *criarItemAtalho( Rectangle ret, Color cor ) {

    ItemAtalho *novoItem = (ItemAtalho*) malloc( sizeof( ItemAtalho ) );

    novoItem->ret = ret;
    novoItem->cor = cor;
    novoItem->estado = ESTADO_ITEM_ATALHO_PARADO;
    novoItem->ativo = true;

    int quantidadeAnimacoes = 0;

    novoItem->animacaoParado.quantidadeQuadros = 6;
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
        2, 50,           // início
        32, 27,          // dimensões
        2,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            0, 3, 62, 51
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
        1, 52,            // início
        16, 16,           // dimensões
        1,                // separação
        false,            // de trás para frente
        (Rectangle) { 0 } // retângulo de colisão padrão para cada quadro
    );

    novoItem->animacoes[ESTADO_ITEM_ATALHO_PARADO] = &novoItem->animacaoParado; quantidadeAnimacoes++;
    novoItem->animacoes[ESTADO_ITEM_ATALHO_COLETADO] = &novoItem->animacaoColetando; quantidadeAnimacoes++;
    novoItem->quantidadeAnimacoes = quantidadeAnimacoes;

    return novoItem;

}

/**
 * @brief Destroi um item (atalho).
 */
void destruirItemAtalho( ItemAtalho *item ) {
    if ( item != NULL ) {
        for ( int i = 0; i < item->quantidadeAnimacoes; i++ ) {
            destruirQuadrosAnimacao( item->animacoes[i] );
        }
        free( item );
    }
}

/**
 * @brief Atualiza um item (atalho).
 */
void atualizarItemAtalho( ItemAtalho *item, float delta ) {
    if ( item->ativo ) {
        Animacao *animacaoAtual = getAnimacaoAtualItemAtalho( item );
        atualizarAnimacao( animacaoAtual, delta );
        if ( item->estado == ESTADO_ITEM_ATALHO_COLETADO && animacaoAtual->finalizada ) {
            item->ativo = false;
            alterarEstadoJogo( ESTADO_JOGO_MAPA2 );
            return;
        }
    }
}

/**
 * @brief Desenha um item (atalho).
 */
void desenharItemAtalho( ItemAtalho *item ) {
    if ( item->ativo ) {
        QuadroAnimacao *qa = getQuadroAnimacaoAtualItemAtalho( item );
        desenharQuadroAnimacaoItemAtalho( item, qa, WHITE );
        if ( MOSTRAR_RETANGULOS ) {
            DrawRectangleRec( item->ret, Fade( item->cor, 0.5f ) );
            DrawRectangleLines( item->ret.x, item->ret.y, item->ret.width, item->ret.height, BLACK );
        }
    }
}

/**
 * @brief Obtém o quadro de animação atual de um item (atalho).
 */
QuadroAnimacao *getQuadroAnimacaoAtualItemAtalho( ItemAtalho *item ) {
    return getQuadroAtualAnimacao( getAnimacaoAtualItemAtalho( item ) );
}

static void desenharQuadroAnimacaoItemAtalho( ItemAtalho *item, QuadroAnimacao *qa, Color tonalidade ) {

    if ( qa != NULL ) {

        DrawTexturePro(
            rm.texturaItens,
            qa->fonte,
            item->ret,
            (Vector2) { 0 },
            0.0f,
            tonalidade
        );

        if ( MOSTRAR_RETANGULOS ) {
            float xDesenho = item->ret.x + qa->retColisao.x;
            float yDesenho = item->ret.y + qa->retColisao.y;
            DrawRectangle( xDesenho, yDesenho, qa->retColisao.width, qa->retColisao.height, Fade( GREEN, 0.5f ) );
        }

    }

}

static Animacao *getAnimacaoAtualItemAtalho( ItemAtalho *item ) {
    return item->animacoes[item->estado];
}