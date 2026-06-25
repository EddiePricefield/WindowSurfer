/**
 * @file InimigoBoss.c
 * @author @EddiePricefield & @rogerioccastro
 * @brief Implementação do Inimigo (Boss).
 *
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>

#include "raylib/raylib.h"
#include "math.h"

#include "Animacao.h"
#include "Inimigo.h"
#include "InimigoBoss.h"
#include "Macros.h"
#include "ResourceManager.h"
#include "Tipos.h"

static void desenharQuadroAnimacaoInimigoBoss( InimigoBoss *inimigo, QuadroAnimacao *qa, Color tonalidade );
static void desenharQuadroAnimacaoInimigoBossMorrendo( InimigoBoss *inimigo, QuadroAnimacao *qa, float escala, Color tonalidade );
static Animacao *getAnimacaoAtualInimigoBoss( InimigoBoss *inimigo );

float tempoCutscene = 0;
bool bossCutscene;

extern bool debug;
extern bool emCutscene;

/**
 * @brief Cria um novo Inimigo (boss).
 */
InimigoBoss *criarInimigoBoss( Rectangle ret, Color cor ) {

    InimigoBoss *novoInimigo = (InimigoBoss*) malloc( sizeof( InimigoBoss ) );

    novoInimigo->ret = ret;
    novoInimigo->vel = (Vector2) { 0 };
    novoInimigo->cor = cor;

    novoInimigo->velAndando = 300;
    novoInimigo->posYInicial = ret.y;
    novoInimigo->tempoOnda = 0;

    novoInimigo->estado = ESTADO_INIMIGO_BOSS_INICIO;
    novoInimigo->ativo = true;
    novoInimigo->olhandoParaDireita = false;

    int quantidadeAnimacoes = 0;

    novoInimigo->animacaoAndando.quantidadeQuadros = 2;
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
        1, 1,           // início
        281, 211,          // dimensões
        1,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            -1000, -1000, 1281, 2000
        }
    );

    novoInimigo->animacaoInicio.quantidadeQuadros = 1;
    novoInimigo->animacaoInicio.quadroAtual = 0;
    novoInimigo->animacaoInicio.contadorTempoQuadro = 0.0f;
    novoInimigo->animacaoInicio.pararNoUltimoQuadro = false;
    novoInimigo->animacaoInicio.executarUmaVez = false;
    novoInimigo->animacaoInicio.finalizada = false;
    criarQuadrosAnimacao( &novoInimigo->animacaoInicio, novoInimigo->animacaoInicio.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoInimigo->animacaoInicio.quadros,
        novoInimigo->animacaoInicio.quantidadeQuadros,
        250,             // duração padrão para todos os quadros
        1, 1,           // início
        281, 211,          // dimensões
        1,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            0
        }
    );

    novoInimigo->animacaoBravo.quantidadeQuadros = 2;
    novoInimigo->animacaoBravo.quadroAtual = 0;
    novoInimigo->animacaoBravo.contadorTempoQuadro = 0.0f;
    novoInimigo->animacaoBravo.pararNoUltimoQuadro = false;
    novoInimigo->animacaoBravo.executarUmaVez = false;
    novoInimigo->animacaoBravo.finalizada = false;
    criarQuadrosAnimacao( &novoInimigo->animacaoBravo, novoInimigo->animacaoBravo.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoInimigo->animacaoBravo.quadros,
        novoInimigo->animacaoBravo.quantidadeQuadros,
        100,             // duração padrão para todos os quadros
        1, 425,           // início
        281, 211,          // dimensões
        1,               // separação
        false,           // de trás para frente
        (Rectangle) {    // retângulo de colisão padrão para cada quadro
            0
        }
    );

    novoInimigo->animacaoMorrendo.quantidadeQuadros = 2;
    novoInimigo->animacaoMorrendo.quadroAtual = 0;
    novoInimigo->animacaoMorrendo.contadorTempoQuadro = 0.0f;
    novoInimigo->animacaoMorrendo.pararNoUltimoQuadro = false;
    novoInimigo->animacaoMorrendo.executarUmaVez = false;
    novoInimigo->animacaoMorrendo.finalizada = false;
    criarQuadrosAnimacao( &novoInimigo->animacaoMorrendo, novoInimigo->animacaoMorrendo.quantidadeQuadros );
    inicializarQuadrosAnimacao( 
        novoInimigo->animacaoMorrendo.quadros,
        novoInimigo->animacaoMorrendo.quantidadeQuadros,
        250,              // duração padrão para todos os quadros
        1, 213,           // início
        281, 211,           // dimensões
        1,                // separação
        false,            // de trás para frente
        (Rectangle) { 0 } // retângulo de colisão padrão para cada quadro
    );

    novoInimigo->animacoes[ESTADO_INIMIGO_BOSS_ANDANDO] = &novoInimigo->animacaoAndando; quantidadeAnimacoes++;
    novoInimigo->animacoes[ESTADO_INIMIGO_BOSS_MORRENDO] = &novoInimigo->animacaoMorrendo; quantidadeAnimacoes++;
    novoInimigo->animacoes[ESTADO_INIMIGO_BOSS_INICIO] = &novoInimigo->animacaoInicio; quantidadeAnimacoes++;
    novoInimigo->animacoes[3] = &novoInimigo->animacaoBravo; quantidadeAnimacoes++;
    novoInimigo->quantidadeAnimacoes = quantidadeAnimacoes;

    return novoInimigo;

}

/**
 * @brief Destroi um inimigo (boss).
 */
void destruirInimigoBoss( InimigoBoss *inimigo ) {
    if ( inimigo != NULL ) {
        for ( int i = 0; i < inimigo->quantidadeAnimacoes; i++ ) {
            destruirQuadrosAnimacao( inimigo->animacoes[i] );
        }
        free( inimigo );
    }
}

/**
 * @brief Atualiza um inimigo (boss).
 */
void atualizarInimigoBoss( InimigoBoss *inimigo, GameWorld *gw, float delta ) {

    if ( inimigo->ativo ) {

        if  ( inimigo->estado == ESTADO_INIMIGO_BOSS_INICIO ){

            float distanciaDoJogadorX = inimigo->ret.x - gw->jogador->ret.x;
            if ( distanciaDoJogadorX <= -670 ){
                bossCutscene = true;
            }

            if ( bossCutscene ){

                atualizarAnimacao( &inimigo->animacaoInicio, delta );

                Inimigo ini = {
                .objeto = inimigo,
                .tipo = TIPO_INIMIGO_BOSS
                    };

                emCutscene = true;
                tempoCutscene += delta;

                if ( tempoCutscene >= 6.2){
                    emCutscene = false;
                    bossCutscene = false;
                    inimigo->estado = ESTADO_INIMIGO_BOSS_ANDANDO;
                    tempoCutscene = 0;
                } else if (tempoCutscene >= 4.7) {
                    atualizarAnimacao( &inimigo->animacaoInicio, delta );
                    inimigo->ret.x = inimigo->ret.x;
                }else if (tempoCutscene >= 2.7){
                    atualizarAnimacao( &inimigo->animacaoBravo, delta );
                    inimigo->tempoOnda += delta;
                    inimigo->ret.y = inimigo->posYInicial + sinf(inimigo->tempoOnda * 25) * 20;
                } else if (tempoCutscene >= 2.2){
                    inimigo->ret.x = inimigo->ret.x;
                } else{
                    inimigo->ret.x += 100 * delta;
                }
                
            }

        }

        if ( inimigo->estado == ESTADO_INIMIGO_BOSS_ANDANDO ) {

            atualizarAnimacao( &inimigo->animacaoAndando, delta );

            Inimigo ini = {
                .objeto = inimigo,
                .tipo = TIPO_INIMIGO_BOSS
                };

            if ( inimigo->olhandoParaDireita ) {
                inimigo->vel.x = -inimigo->velAndando;
            } else {
                inimigo->vel.x = inimigo->velAndando;
            }

            // fase X
            float distanciaDoJogadorX = inimigo->ret.x - gw->jogador->ret.x;

            printf("%f\n", distanciaDoJogadorX);

            if (distanciaDoJogadorX <= -670){
                inimigo->ret.x += 550 * delta;
            } else if (distanciaDoJogadorX <= -550) {
                inimigo->ret.x += 500 * delta;
            } else if (distanciaDoJogadorX <= -450) {
                inimigo->ret.x += 400 * delta;
            } else if (distanciaDoJogadorX <= -350) {
                inimigo->ret.x += 300 * delta;
            } else{
                inimigo->ret.x += 200 * delta;
            }
            
            resolverColisaoInimigoObstaculosMapaX( &ini, gw->mapa );
            resolverColisaoInimigoBlocoInvisivelMapaX( &ini, gw->mapa );

            // fase Y

            float distanciaDoJogadorY = inimigo->ret.y - gw->jogador->ret.y;
            if (distanciaDoJogadorY <= -50){
                inimigo->posYInicial += 300 * delta;
            } else if (distanciaDoJogadorY >= 50){
                inimigo->posYInicial -= 300 * delta;
            }

            printf("%f\n", distanciaDoJogadorY);

            inimigo->tempoOnda += delta;
            inimigo->ret.y = inimigo->posYInicial + sinf(inimigo->tempoOnda * 4) * 30;
            resolverColisaoInimigoObstaculosMapaY( &ini, gw->mapa );
            resolverColisaoInimigoBlocoInvisivelMapaY( &ini, gw->mapa );

        } else if ( inimigo->estado == ESTADO_INIMIGO_BOSS_MORRENDO ) {

            atualizarAnimacao( &inimigo->animacaoMorrendo, delta );

            if ( inimigo->animacaoMorrendo.finalizada ) {
                inimigo->ativo = false;
            }

        }

    }

}

/**
 * @brief Desenha um inimigo (boss).
 */
void desenharInimigoBoss( InimigoBoss *inimigo ) {

    if ( inimigo->ativo ) {

        if ( inimigo->estado == ESTADO_INIMIGO_BOSS_ANDANDO ) {
            QuadroAnimacao *qa = getQuadroAnimacaoAtualInimigoBoss( inimigo );
            desenharQuadroAnimacaoInimigoBoss( inimigo, qa, WHITE );
        } else if ( inimigo->estado == ESTADO_INIMIGO_BOSS_INICIO && emCutscene) {
            QuadroAnimacao *qa = getQuadroAnimacaoAtualInimigoBoss( inimigo );
            desenharQuadroAnimacaoInimigoBoss( inimigo, qa, WHITE );
        } else if ( inimigo->estado == ESTADO_INIMIGO_BOSS_MORRENDO ) {
            desenharQuadroAnimacaoInimigoBossMorrendo( inimigo, getQuadroAtualAnimacao( &inimigo->animacaoMorrendo ), 2.0f, WHITE );
        }

        if ( debug ) {
            DrawRectangleRec( inimigo->ret, Fade( inimigo->cor, 0.5f ) );
            DrawRectangleLines( inimigo->ret.x, inimigo->ret.y, inimigo->ret.width, inimigo->ret.height, BLACK );
        }

    }

}

/**
 * @brief Obtém o quadro de animação atual de um inimigo (boss).
 */
QuadroAnimacao *getQuadroAnimacaoAtualInimigoBoss( InimigoBoss *inimigo ) {
    return getQuadroAtualAnimacao( getAnimacaoAtualInimigoBoss( inimigo ) );
}

static void desenharQuadroAnimacaoInimigoBoss( InimigoBoss *inimigo, QuadroAnimacao *qa, Color tonalidade ) {

    if ( qa != NULL ) {
        
        DrawTexturePro(
            rm.texturaBoss,
            (Rectangle) {
                qa->fonte.x,
                qa->fonte.y,
                qa->fonte.width,
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

static void desenharQuadroAnimacaoInimigoBossMorrendo( InimigoBoss *inimigo, QuadroAnimacao *qa, float escala, Color tonalidade ) {

    if ( qa != NULL ) {
        
        DrawTexturePro(
            rm.texturaBoss,
            qa->fonte,
            (Rectangle) {
                inimigo->ret.x,
                inimigo->ret.y,
                qa->fonte.width,
                qa->fonte.height
            },
            (Vector2) { 0 },
            0.0f,
            tonalidade
        );

    }

}

static Animacao *getAnimacaoAtualInimigoBoss( InimigoBoss *inimigo ) {

    if (tempoCutscene >= 2.7 && tempoCutscene <= 4.7){
        return inimigo->animacoes[3];
    }else{
        return inimigo->animacoes[inimigo->estado];
    }
  
}