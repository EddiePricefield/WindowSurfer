/**
 * @file ResourceManager.h
 * @author @EddiePricefield & @rogerioccastro
 * @brief ResourceManager struct and function declarations.
 * 
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "raylib/raylib.h"

typedef struct ResourceManager {

    Image imagemCutsceneVitoria;
    Texture2D texturaCutsceneVitoria;
    int animFrames;
    int frameAtual;
    int frameDelay;
    int frameCounter;

    Texture2D texturaJanela1;
    Texture2D texturaJanela;
    
    Texture2D texturaJogador;
    Texture2D texturaJogadorParado;
    Texture2D texturaInimigos;
    Texture2D texturaItens;
    Texture2D texturaMorte;

    Texture2D texturaBoss;

    Texture2D texturaTerreno;
    Texture2D texturaFundo;
    Texture2D texturaCeu;

    Texture2D texturaHud;
    Texture2D texturaHP;

    Texture2D texturaPopUp;
    Texture2D texturaMenuInicial;
    Texture2D texturaMenuPausa;
    Texture2D texturaMenuGuia;
    Texture2D texturaMenuOpcoes;
    Texture2D texturaSystem32;

    Texture2D texturaTelaMorte;

    Sound somColeta;
    Sound somFrenagem;
    Sound somHit;
    Sound somHitInimigo;
    Sound somMorte;
    Sound somPulo;
    Sound somClick;
    Sound somGameOver;
    Sound somBossRisada;
    Sound somVitoria;

    Sound somAbrirMenu;
    Sound somFecharMenu;

    Music musicaFase01;
    Music musicaFase02;

} ResourceManager;

/**
 * @brief Global ResourceManager instance.
 */
extern ResourceManager rm;

/**
 * @brief Load global game resources, linking them in the global instance of
 * ResourceManager called rm.
 */
void loadResourcesResourceManager( void );

/**
 * @brief Unload global game resources.
 */
void unloadResourcesResourceManager( void );