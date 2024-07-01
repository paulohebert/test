#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <screen.h>
#include <utils.h>
#include <texture.h>
#include <keyboard.h>
#include <physics.h>
#include <position.h>
#include <audio.h>

// Variáveis globais para armazenar as dimensões da janela
int larguraJanela, alturaJanela;

// Variável global para armazenar a pontuação do jogador
char scoreText[20];

int nivelAtual;

char level[20];

// Variáveis globais para controlar a tela
int telaAtual; // Define a variável que controla a tela atual

// Variável que vai ficar verificando o tempo para contabilizar nos pontos
int ultimoTempoAtualizado;

float x, y;
float largura, altura, retXinic, retYinic, retXcont, retYcont, retXexit, retYexit;

// Reseta as variáveis para o início do jogo
void resetGame()
{
    // Define 5 Vidas quando o jogador iniciar o jogo
    lives = 5;

    // Reset na posição do jogador
    translateX = translateY = 0;

    // Reset a variável que inverte o lado do jogador está virado
    flip = false;

    // Resetar o tempo do jogo
    tempoRestante = 60.0;

    // Define o nível 1 como primeiro nível
    nivelAtual = 1;

    // Remove todos os mosquitos
    mosquitos.clear();

    // Remove todos os tiros
    disparos.clear();

    // Reseta a velocidade e o tempo de respawn dos mosquitos para o inicial
    t = 5;
    v = 1;

    // Inicializa o tempo
    ultimoTempoAtualizado = glutGet(GLUT_ELAPSED_TIME) / 1000;

    // Reseta os pontos ao reiniciar o jogo
    score = 0;

    // Reseta a cura
    cura = 1;
}

// Muda a tela atual e faz que só as animações presente na tela executem
void changeScreen(int screenId)
{
    telaAtual = screenId; // Altera o ID da tela atual
    switch (screenId)
    {
    case HOME_SCREEN:
        // Muda para a tela de início
        glutDisplayFunc(telaInicial);

        // Começa a animação das texturas da tela inicial
        glutTimerFunc(50, animateHomeScreenTextures, 0);

        // Toca a música de abertura
        playSound(OPENING);

        // Configura as variáveis para o começo do jogo
        resetGame();
        break;
    case GAME_SCREEN:
        // Para de tocar o loop da música de abertura
        stopSoundLoop(OPENING);

        // Muda para a tela do jogo
        glutDisplayFunc(telaJogo);

        // Começa a animação das texturas da tela do jogo
        glutTimerFunc(100, animateGameScreenTextures, 0);

        // Inicia a contagem regressiva
        glutTimerFunc(1000, atualizaTempo, 0);

        // Registra a função callback que será chamada a cada intervalo de tempo para mover objetos na tela
        glutTimerFunc(0, atualizaMovimento, 0);

        playSound(RAIN); // Toca o som de fundo
        break;
    case GAME_PAUSE_SCREEN:
        // Tira o loop do som do jogo ao pausar a partida
        stopSoundLoop(RAIN);

        // Redefine o banner de combate à dengue para o início da animação
        currentBannerCombatInfoFrame = 0;

        // Muda para a tela de pause
        glutDisplayFunc(telaPause);

        // Começa a animação das texturas da tela de pause
        glutTimerFunc(400, animateGamePauseScreenTextures, 0);
        break;
    case END_GAME_SCREEN:
        // Tira o loop do som do jogo ao terminar a partida
        stopSoundLoop(RAIN);

        // Muda para a tela de fim de jogo
        glutDisplayFunc(telaFim);

        // Começa a animação das texturas da tela de fim de jogo
        glutTimerFunc(50, animateEndGameScreenTextures, 0);

        // Toca o som de game over
        playSound(LOSE);
        break;
    case LOADING_SCREEN:
        // Muda para a tela de carregamento
        glutDisplayFunc(loadingScreen);
        break;
    }
}

void loadingScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);

#ifndef __EMSCRIPTEN__
    // Escreve o texto na tela
    glColor3f(0.0f, 0.0f, 0.0f);
    escreveTextoBitmap(larguraJanela / 2, alturaJanela / 2, GLUT_BITMAP_HELVETICA_18, "Carregando...");
#endif
    glutSwapBuffers();
}

void nextLevel()
{
    tempoRestante = 60.0;
    cura = 1;
}

void telaInicial()
{
    // Limpa o buffer de cor e profundidade
    glClear(GL_COLOR_BUFFER_BIT);

    // Define a matriz de modelagem para coordenadas de objeto
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicia a aplicação de texturas
    glEnable(GL_TEXTURE_2D);

    // Desenha o plano de fundo
    drawFrame(BACKGROUND_MENU, currentBackgroundMenuFrame, 10, 10, 0, 0, larguraJanela, alturaJanela);

    // Desenha a logo Aedes Attack
    draw(LOGO, xAedesAttack, yAedesAttack, wAedesAttack, hAedesAttack);

    // Desenha a logo da Univasf
    draw(UNIVASF, xUnivasf, yUnivasf, wUnivasf, hUnivasf);

    // Desenha a placa de mosquito
    draw(MOSQUITO_PROHIBITED, xMosquitoProhibited, yMosquitoProhibited, wMosquitoProhibited, hMosquitoProhibited);

    // Desenha o botão de iniciar
    draw(BUTTON_START, xButtonStart, yButtonStart, wButtonStart, hButtonStart);

    // Desenha o botão de Sobre
    draw(BUTTON_ABOUT, xButtonAbout, yButtonAbout, wButtonAbout, hButtonAbout);

    // Desenha o modal de sobre
    if (telaAtual == ABOUT_SCREEN)
    {
        draw(ABOUT, xAbout, yAbout, wAbout, hAbout);
        draw(BUTTON_X, xButtonCloseAbout, yButtonCloseAbout, wButtonCloseAbout, hButtonCloseAbout);
    }

    // Desativa a aplicação de texturas
    glDisable(GL_TEXTURE_2D);

    // Atualiza a tela
    glutSwapBuffers();
}

void telaJogo()
{
    int tempoAtual = glutGet(GLUT_ELAPSED_TIME) / 1000; // Obtém o tempo atual em segundos

    if (!tempoRestante)
    {
        nivelAtual++;
        v += 2;
        if (t >= 2)
            t--;
        nextLevel();
    }

    // Limpa o buffer de cor e profundidade
    glClear(GL_COLOR_BUFFER_BIT);

    // Define a matriz de modelagem para coordenadas de objeto
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicia a aplicação de texturas
    glEnable(GL_TEXTURE_2D);

    // Desenha o plano de fundo
    drawFrame(BACKGROUND_MAIN, currentBackgroundMainFrame, 4, 4, 0, 0, larguraJanela, alturaJanela);

    // Desenha informações de combate ao mosquito
    drawFrame(BANNER_COMBAT_INFO, currentBannerCombatInfoFrame, 8, 8, xBannerDengue, yBannerDengue, wBannerDengue, hBannerDengue);

    // Desenha o botão de Pause
    draw(BUTTON_PAUSE, xButtonPause, yButtonPause, wButtonPause, hButtonPause);

    // Desenha a quantidade de Vida que o jogador tem
    for (int totalHeart = lives; totalHeart; totalHeart--)
    {
        draw(HEART, xHeart + (wHeart * totalHeart) + (totalHeart * offsetHeart), yHeart, wHeart, hHeart);
    }

    // Desenha a plataforma de piso
    draw(PLATFORM, xPlatformFloor, yPlatformFloor, wPlatformFloor, hPlatformFloor);

    // Desenha a plataforma 1
    draw(PLATFORM, xPlatform1, yPlatform1, wPlatform1, hPlatform1);

    // Desenha a plataforma 2
    draw(PLATFORM, xPlatform2, yPlatform2, wPlatform2, hPlatform2);

    // Desenha a plataforma 3
    draw(PLATFORM, xPlatform3, yPlatform3, wPlatform3, hPlatform3);

    // Desenha a plataforma 4
    draw(PLATFORM, xPlatform4, yPlatform4, wPlatform4, hPlatform4);

    // Desenha a plataforma 5
    draw(PLATFORM, xPlatform5, yPlatform5, wPlatform5, hPlatform5);

    // Atualiza o tempo e a pontuação
    tempoAtual = glutGet(GLUT_ELAPSED_TIME) / 1000; // Obtém o tempo atual em segundos
    if (tempoRestante && (tempoAtual - ultimoTempoAtualizado >= 10))
    {
        ultimoTempoAtualizado = tempoAtual;
        score += 10; // Incrementa 10 pontos a cada 10 segundos de sobrevivência
    }

    // Move o Jogador
    glPushMatrix();
    glTranslatef(translateX, translateY, 0.0);
    if (flip)
    {
        glTranslatef(larguraJanela / 4.0, 0.0f, 0.0f); // Ajustar a posição para evitar que a imagem saia da tela
        glScalef(-1.0f, 1.0f, 1.0f);                   // Aplicar transformação negativa no eixo X para inverter horizontalmente
    }

    // Desenha o player
    if (dead) // Verifica se mostra o jogador perdendo uma vida
        drawFrame(PLAYER_DEAD, currentPlayerFrame, 4, 4, xPlayer, yPlayer, wPlayer * 2.0, hPlayer);
    else if (isJumping) // Verifica se o jogador está pulando
        drawFrame(PLAYER_JUMP, currentPlayerFrame, 4, 4, xPlayer, yPlayer, wPlayer * 1.2, hPlayer);
    else if (leftPressed || rightPressed) // Verifica se o jogador está correndo
        drawFrame(PLAYER_RUN, currentPlayerFrame, 4, 4, xPlayer, yPlayer, wPlayer * 1.2, hPlayer);
    else
    {
        // Desenha o jogador parado
        drawFrame(PLAYER, currentPlayerFrame, 4, 4, xPlayer, yPlayer, wPlayer, hPlayer);
    }

    draw(SHOTGUN, xPlayer, yPlayer * 1.5, wPlayer * 1.25, hPlayer / 3);

    glPopMatrix();

    // Desenha o Disparo
    disparar();

    // Desenha o Mosquito
    desenhaMosquito();

    // Desenha o plano de fundo da pontuação
    draw(SCORE, xScore, yScore, wScore, hScore);

    // Desenha o plano de fundo do timer
    draw(TIMER, xTimer, yTimer, wTimer, hTimer);

    // Desenha o plano de fundo do nível atual
    draw(LEVEL, xLevel, yLevel, wLevel, hLevel);

    glDisable(GL_TEXTURE_2D);

#ifndef __EMSCRIPTEN__
    // Escreve a pontuação
    glColor3f(0.0f, 0.0f, 0.0f);
    snprintf(scoreText, sizeof(scoreText), "%d", score);
    escreveTextoBitmap(xScore + wScore / 2, yScore + hScore / 2, GLUT_BITMAP_HELVETICA_18, scoreText);

    // Desenha a contagem regressiva
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Tempo restante: %02d:%02d", tempoRestante / 60, tempoRestante % 60);
    glColor3f(0.0f, 0.0f, 0.0f);
    escreveTextoBitmap(xTimer + wTimer / 1.8, yTimer + hTimer / 2.1, GLUT_BITMAP_HELVETICA_18, buffer);

    // Desenha a contagem regressiva
    glColor3f(0.0f, 0.0f, 0.0f);
    snprintf(level, sizeof(level), "Nivel atual: %d", nivelAtual);
    escreveTextoBitmap(xLevel + wLevel / 2, yLevel + hLevel / 2.1, GLUT_BITMAP_HELVETICA_18, level);
#endif

    glutSwapBuffers();
}

void telaPause()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Matriz de modelagem
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicia a aplicação de texturas
    glEnable(GL_TEXTURE_2D);

    // Desenha o plano de fundo
    draw(BACKGROUND_PAUSE, 0, 0, larguraJanela, alturaJanela);

    // Desenha as informações de combate ao mosquito
    drawFrame(BANNER_COMBAT_INFO, currentBannerCombatInfoFrame, 8, 8, xBannerDengueCenter, yBannerDengueCenter, wBannerDengueCenter, hBannerDengueCenter);

    // Desenha o botão de "continue"
    draw(BUTTON_PLAY, xButtonContinue, yButtonContinue, wButtonContinue, hButtonContinue);

    // Desenha o botão de "exit"
    draw(BUTTON_EXIT, xButtonExit, yButtonExit, wButtonExit, hButtonExit);

    glDisable(GL_TEXTURE_2D);

#ifndef __EMSCRIPTEN__
    // Desenha o texto centralizado
    glColor3f(0.0f, 0.0f, 0.0f);
    escreveTextoBitmap(larguraJanela / 2, alturaJanela * 0.9f, GLUT_BITMAP_HELVETICA_18, "JOGO PAUSADO");

    // Desenha o texto centralizado
    escreveTextoBitmap(larguraJanela / 2, alturaJanela * 0.9f - 20, GLUT_BITMAP_HELVETICA_12, "Selecione uma das caixas ou aperte ENTER para retomar o jogo");
#endif

    glutSwapBuffers();
}

void telaFim()
{
    glClearColor(0.8f, 0.2f, 0.2f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Matriz de modelagem
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Inicia a aplicação de texturas
    glEnable(GL_TEXTURE_2D);

    // Desenha o plano de fundo
    draw(BACKGROUND_PAUSE, 0, 0, larguraJanela, alturaJanela);

    // Desenha o botão de "recomeçar"
    draw(BUTTON_RESTART, xButtonRestart, yButtonRestart, wButtonRestart, hButtonRestart);

    // Desenha o botão de "exit"
    draw(BUTTON_EXIT, xButtonEndGameExit, yButtonEndGameExit, wButtonEndGameExit, hButtonEndGameExit);

    // Desenha o mosquito
    drawFrame(MOSQUITO_GAME_OVER, currentMosquitoGameOverFrame, 3, 10, xMosquitoGameOver, yMosquitoGameOver, wMosquitoGameOver, hMosquitoGameOver);

    // Desenha o plano de fundo da pontuação final
    draw(SCORE, xEndScore, yEndScore, wEndScore, hEndScore);

    glDisable(GL_TEXTURE_2D);

#ifndef __EMSCRIPTEN__
    // Escreve a pontuação alcançada pelo jogador
    glColor3f(0.0f, 0.0f, 0.0f);
    snprintf(scoreText, sizeof(scoreText), "%d", score);
    escreveTextoBitmap(xEndScore + wEndScore / 2, yEndScore + hEndScore / 2, GLUT_BITMAP_TIMES_ROMAN_24, scoreText);

    // Desenha o texto centralizado
    escreveTextoBitmap(larguraJanela / 2, alturaJanela * 0.9f, GLUT_BITMAP_HELVETICA_18, "FIM DE JOGO");

    // Desenha o texto centralizado
    escreveTextoBitmap(larguraJanela / 2, alturaJanela * 0.9f - 20, GLUT_BITMAP_HELVETICA_12, "Selecione uma das caixas");
#endif

    // Atualiza a tela
    glutSwapBuffers();
}