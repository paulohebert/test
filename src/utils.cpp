#include <GL/glut.h>
#include <stdlib.h>
#include <screen.h>
#include <texture.h>
#include <keyboard.h>
#include <physics.h>

int tempoRestante, t = 5, cura = 1;

#ifndef __EMSCRIPTEN__

// Função para desenhar texto na tela
void escreveTextoBitmap(float x, float y, void *fonte, const char *string)
{
    int comprimentoTexto = glutBitmapLength(fonte, (const unsigned char *)string);
    const char *c;
    glRasterPos2f(x - comprimentoTexto / 2, y);
    for (c = string; *c != '\0'; c++)
        glutBitmapCharacter(fonte, *c);
}

#endif

// Callback para a contagem regressiva
void atualizaTempo(int value)
{
    if (telaAtual == GAME_SCREEN && tempoRestante > 0)
    {
        if (tempoRestante % t == 0)
        {
            adicionaMosquito();
        }
        tempoRestante--;
        glutPostRedisplay();
        glutTimerFunc(1000, atualizaTempo, 0);
    }
}

void atualizaMovimento(int)
{
    if (telaAtual == GAME_SCREEN)
    {
        moveObjetos();
        glutPostRedisplay();
        glutTimerFunc(10, atualizaMovimento, 0);
    }
}

// Função para curar o player
void curaPlayer()
{
    if (cura && lives < 5)
    {
        cura--;
        lives++;
    }
}

/* Atualiza os frames das texturas da tela inicial */
void animateHomeScreenTextures(int)
{
    /* Evita que a animação continue quando trocar de tela */
    if (telaAtual == HOME_SCREEN || telaAtual == ABOUT_SCREEN)
    {
        // Altera para o próximo frame do plano de fundo da tela inicial
        currentBackgroundMenuFrame = (currentBackgroundMenuFrame + 1) % BACKGROUND_MENU_TOTAL_FRAMES;

        glutPostRedisplay();                             // Redesenha a tela
        glutTimerFunc(50, animateHomeScreenTextures, 0); // Loop
    }
}

/* Atualiza os frames das texturas da tela do jogo */
void animateGameScreenTextures(int)
{
    /* Evita que a animação continue quando trocar de tela */
    if (telaAtual == GAME_SCREEN)
    {
        // Altera para o próximo frame do plano de fundo da tela do jogo
        currentBackgroundMainFrame = (currentBackgroundMainFrame + 1) % BACKGROUND_MAIN_TOTAL_FRAMES;

        // Altera para o próximo frame do personagem do jogador
        if (!dead)
            currentPlayerFrame = (currentPlayerFrame + 1) % PLAYER_TOTAL_FRAMES;

        // Adiciona um delay na animação do banner para não ficar passando muito rápido
        static int delay = 4;
        if (delay-- == 0)
        {
            // Altera para o próximo frame do banner de combate à dengue
            currentBannerCombatInfoFrame = (currentBannerCombatInfoFrame + 1) % BANNER_COMBAT_INFO_TOTAL_FRAMES;
            delay = 4;
        }

        glutPostRedisplay();                              // Redesenha a tela
        glutTimerFunc(100, animateGameScreenTextures, 0); // Loop
    }
}

/* Atualiza os frames das texturas da tela de pause do jogo */
void animateGamePauseScreenTextures(int)
{
    /* Evita que a animação continue quando trocar de tela */
    if (telaAtual == GAME_PAUSE_SCREEN)
    {
        // Altera para o próximo frame do banner de combate à dengue
        currentBannerCombatInfoFrame = (currentBannerCombatInfoFrame + 1) % BANNER_COMBAT_INFO_TOTAL_FRAMES;

        glutPostRedisplay();                                   // Redesenha a tela
        glutTimerFunc(400, animateGamePauseScreenTextures, 0); // Loop
    }
}

/* Atualiza os frames das texturas da tela de fim de jogo */
void animateEndGameScreenTextures(int)
{
    /* Evita que a animação continue quando trocar de tela */
    if (telaAtual == END_GAME_SCREEN)
    {
        // Altera para o próximo frame do mosquito na tela de fim de jogo
        currentMosquitoGameOverFrame = (currentMosquitoGameOverFrame + 1) % MOSQUITO_GAME_OVER_TOTAL_FRAMES;

        glutPostRedisplay();                                // Redesenha a tela
        glutTimerFunc(50, animateEndGameScreenTextures, 0); // Loop
    }
}

// Anima os frames do jogador perdendo uma vida
void animatePlayerDead(int frame)
{
    if (telaAtual == GAME_SCREEN && frame < PLAYER_TOTAL_FRAMES)
    {
        // Altera para o próximo frame do personagem do jogador
        currentPlayerFrame = frame;

        glutPostRedisplay();                             // Redesenha a tela
        glutTimerFunc(50, animatePlayerDead, frame + 1); // Loop
    }
    else
    {
        dead = false;
    }
}