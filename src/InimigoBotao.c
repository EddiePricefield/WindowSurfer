/**
 * @file InimigoBotao.c
 * @author @EddiePricefield & @rogerioccastro
 * @brief Implementação do Inimigo (Botao).
 *
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"

#include "Animacao.h"
#include "Inimigo.h"
#include "InimigoBotao.h"
#include "Macros.h"
#include "ResourceManager.h"
#include "Tipos.h"
#include "GameWorld.h"

static void desenharQuadroAnimacaoInimigoBotao( InimigoBotao *inimigo, QuadroAnimacao *qa, Color tonalidade );
static void desenharQuadroAnimacaoInimigoBotaoMorrendo( InimigoBotao *inimigo, QuadroAnimacao *qa, float escala, Color tonalidade );
static Animacao *getAnimacaoAtualInimigoBotao( InimigoBotao *inimigo );

extern bool debug;

/**
 * @brief Cria um novo Inimigo (botao).
 */
InimigoBotao *criarInimigoBotao( Rectangle ret, Color cor ) {

    InimigoBotao *novoInimigo = (InimigoBotao*) malloc( sizeof( InimigoBotao ) );

    novoInimigo->ret = ret;
    novoInimigo->vel = (Vector2) { 0 };
    novoInimigo->cor = cor;

    novoInimigo->velAndando = 100;
    novoInimigo->velMaxQueda = 600;

    novoInimigo->estado = ESTADO_INIMIGO_BOTAO_ANDANDO;
    novoInimigo->ativo = true;
    novoInimigo->olhandoParaDireita = false;

    int quantidadeAnimacoes = 0;

    novoInimigo->animacaoAndando.quantidadeQuadros = 1;
    novoInimigo->animacaoAndando.quadroAtual = 0;
    novoInimigo->animacaoAndando.contadorTempoQuadro = 0.0f;
    novoInimigo->animacaoAndando.pararNoUltimoQuadro = false;
    novoInimigo->animacaoAndando.executarUmaVez = false;
    novoInimigo->animacaoAndando.finalizada = false;
    criarQuadrosAnimacao( &novoInimigo->animacaoAndando, novoInimigo->animacaoAndando.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoInimigo->animacaoAndando.quadros,
        novoInimigo->animacaoAndando.quantidadeQuadros,
        250,             // duração padrão para todos os quadros
        2, 107,            // início
        32, 28,          // dimensões
        2,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            0, 33, 60, 17
        }
    );

    novoInimigo->animacaoMorrendo.quantidadeQuadros = 1;
    novoInimigo->animacaoMorrendo.quadroAtual = 0;
    novoInimigo->animacaoMorrendo.contadorTempoQuadro = 0.0f;
    novoInimigo->animacaoMorrendo.pararNoUltimoQuadro = false;
    novoInimigo->animacaoMorrendo.executarUmaVez = false;
    novoInimigo->animacaoMorrendo.finalizada = false;
    criarQuadrosAnimacao( &novoInimigo->animacaoMorrendo, novoInimigo->animacaoMorrendo.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoInimigo->animacaoMorrendo.quadros,
        novoInimigo->animacaoMorrendo.quantidadeQuadros,
        100,              // duração padrão para todos os quadros
        38, 107,           // início
        32, 28,           // dimensões
        2,                // separação
        false,            // de trás para frente
        (Rectangle) { 0 } // retângulo de colisão padrão para cada quadro
    );

    novoInimigo->animacoes[ESTADO_INIMIGO_BOTAO_ANDANDO] = &novoInimigo->animacaoAndando; quantidadeAnimacoes++;
    novoInimigo->animacoes[ESTADO_INIMIGO_BOTAO_MORRENDO] = &novoInimigo->animacaoMorrendo; quantidadeAnimacoes++;
    novoInimigo->quantidadeAnimacoes = quantidadeAnimacoes;

    return novoInimigo;

}

/**
 * @brief Destroi um inimigo (botao).
 */
void destruirInimigoBotao( InimigoBotao *inimigo ) {
    if ( inimigo != NULL ) {
        for ( int i = 0; i < inimigo->quantidadeAnimacoes; i++ ) {
            destruirQuadrosAnimacao( inimigo->animacoes[i] );
        }
        free( inimigo );
    }
}

/**
 * @brief Atualiza um inimigo (botao).
 */
void atualizarInimigoBotao( InimigoBotao *inimigo, GameWorld *gw, float delta ) {

    if ( inimigo->ativo ) {

        if ( inimigo->estado == ESTADO_INIMIGO_BOTAO_ANDANDO ) {

            Animacao *animacaoAtual = getAnimacaoAtualInimigoBotao( inimigo );
            atualizarAnimacao( animacaoAtual, delta );

            Inimigo ini = {
                .objeto = inimigo,
                .tipo = TIPO_INIMIGO_BOTAO
            };

            inimigo->vel.x = 0;
            inimigo->vel.y = 0;

            // fase X
            inimigo->ret.x += inimigo->vel.x * delta;

            // fase Y
            inimigo->ret.y += inimigo->vel.y * delta;

        } else if ( inimigo->estado == ESTADO_INIMIGO_BOTAO_MORRENDO ) {

            atualizarAnimacao( &inimigo->animacaoMorrendo, delta );
            alterarEstadoJogo( ESTADO_JOGO_VITORIA );

            if ( inimigo->animacaoMorrendo.finalizada ) {
                inimigo->ativo = false;
            }

        }

    }

}

/**
 * @brief Desenha um inimigo (botao).
 */
void desenharInimigoBotao( InimigoBotao *inimigo ) {

    if ( inimigo->ativo ) {

        if ( inimigo->estado == ESTADO_INIMIGO_BOTAO_ANDANDO ) {
            QuadroAnimacao *qa = getQuadroAnimacaoAtualInimigoBotao( inimigo );
            desenharQuadroAnimacaoInimigoBotao( inimigo, qa, WHITE );
        } else if ( inimigo->estado == ESTADO_INIMIGO_BOTAO_MORRENDO ) {
            desenharQuadroAnimacaoInimigoBotaoMorrendo( inimigo, getQuadroAtualAnimacao( &inimigo->animacaoMorrendo ), 2.0f, WHITE );
        }

        if ( debug ) {
            DrawRectangleRec( inimigo->ret, Fade( inimigo->cor, 0.5f ) );
            DrawRectangleLines( inimigo->ret.x, inimigo->ret.y, inimigo->ret.width, inimigo->ret.height, BLACK );
        }

    }

}

/**
 * @brief Obtém o quadro de animação atual de um inimigo (botao).
 */
QuadroAnimacao *getQuadroAnimacaoAtualInimigoBotao( InimigoBotao *inimigo ) {
    return getQuadroAtualAnimacao( getAnimacaoAtualInimigoBotao( inimigo ) );
}

static void desenharQuadroAnimacaoInimigoBotao( InimigoBotao *inimigo, QuadroAnimacao *qa, Color tonalidade ) {

    if ( qa != NULL ) {
        
        DrawTexturePro(
            rm.texturaItens,
            (Rectangle) {
                qa->fonte.x,
                qa->fonte.y,
                inimigo->olhandoParaDireita ? -qa->fonte.width : qa->fonte.width,
                qa->fonte.height
            },
            inimigo->ret,
            (Vector2) { 0 },
            0.0f,
            tonalidade
        );

        if ( debug ) {
            float xDesenho = inimigo->olhandoParaDireita
                ? inimigo->ret.x + inimigo->ret.width - qa->retColisao.x - qa->retColisao.width
                : inimigo->ret.x + qa->retColisao.x;
            float yDesenho = inimigo->ret.y + qa->retColisao.y;
            DrawRectangle( xDesenho, yDesenho, qa->retColisao.width, qa->retColisao.height, Fade( GREEN, 0.5f ) );
        }

    }

}

static void desenharQuadroAnimacaoInimigoBotaoMorrendo( InimigoBotao *inimigo, QuadroAnimacao *qa, float escala, Color tonalidade ) {

    if ( qa != NULL ) {
        
        DrawTexturePro(
            rm.texturaItens,
            qa->fonte,
            (Rectangle) {
                inimigo->ret.x,
                inimigo->ret.y,
                qa->fonte.width * escala,
                qa->fonte.height * escala
            },
            (Vector2) { 0 },
            0.0f,
            tonalidade
        );

    }

}

static Animacao *getAnimacaoAtualInimigoBotao( InimigoBotao *inimigo ) {
    return inimigo->animacoes[inimigo->estado];
}