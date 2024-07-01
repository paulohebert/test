#ifndef POSITION_H
#define POSITION_H

#include <GL/glut.h>

// --------------------------------------------------------------- //
// Tela de Início

// Posição da Logo do Jogo Aedes Attack
extern GLfloat xAedesAttack, yAedesAttack, wAedesAttack, hAedesAttack;

// Posição da Logo da Univasf
extern GLfloat xUnivasf, yUnivasf, wUnivasf, hUnivasf;

// Posição da Placa de Proibido Mosquito
extern GLfloat xMosquitoProhibited, yMosquitoProhibited, wMosquitoProhibited, hMosquitoProhibited;

// Posição do Botão de Iniciar do Jogo
extern GLfloat xButtonStart, yButtonStart, wButtonStart, hButtonStart;

// Posição do Botão de Sobre
extern GLfloat xButtonAbout, yButtonAbout, wButtonAbout, hButtonAbout;

// --------------------------------------------------------------- //
// Tela de Sobre

// Posição do Banner de Sobre
extern GLfloat xAbout, yAbout, wAbout, hAbout;

// Posição do Botão de Fechar o banner de Sobre
extern GLfloat xButtonCloseAbout, yButtonCloseAbout, wButtonCloseAbout, hButtonCloseAbout;

// --------------------------------------------------------------- //
// Tela do Jogo

// Posição do Botão de Pause do Jogo
extern GLfloat xButtonPause, yButtonPause, wButtonPause, hButtonPause;

// Posição do Banner de Combate à Dengue
extern GLfloat xBannerDengue, yBannerDengue, wBannerDengue, hBannerDengue;

// Posição do Jogador
extern GLfloat xPlayer, yPlayer, wPlayer, hPlayer;

// Posição do Mosquito
extern GLfloat xMosquito, yMosquito, wMosquito, hMosquito;

// Posição da Plataforma de Piso do Chão
extern GLfloat xPlatformFloor, yPlatformFloor, wPlatformFloor, hPlatformFloor;

// Posição da Plataforma Suspensa 1
extern GLfloat xPlatform1, yPlatform1, wPlatform1, hPlatform1;

// Posição da Plataforma Suspensa 2
extern GLfloat xPlatform2, yPlatform2, wPlatform2, hPlatform2;

// Posição da Plataforma Suspensa 3
extern GLfloat xPlatform3, yPlatform3, wPlatform3, hPlatform3;

// Posição da Plataforma Suspensa 4
extern GLfloat xPlatform4, yPlatform4, wPlatform4, hPlatform4;

// Posição da Plataforma Suspensa 5
extern GLfloat xPlatform5, yPlatform5, wPlatform5, hPlatform5;

// Posição das Vidas
extern GLfloat xHeart, yHeart, wHeart, hHeart, offsetHeart;

// Posição da Pontuação
extern GLfloat xScore, yScore, wScore, hScore;

// Posição do Timer
extern GLfloat xTimer, yTimer, wTimer, hTimer;

// Posição do Nível Atual
extern GLfloat xLevel, yLevel, wLevel, hLevel;

// --------------------------------------------------------------- //
// Tela de Pause

// Posição do Botão de Volta para o Jogo
extern GLfloat xButtonContinue, yButtonContinue, wButtonContinue, hButtonContinue;

// Posição do Botão de Sair do Jogo
extern GLfloat xButtonExit, yButtonExit, wButtonExit, hButtonExit;

// Posição do Banner de Combate à Dengue
extern GLfloat xBannerDengueCenter, yBannerDengueCenter, wBannerDengueCenter, hBannerDengueCenter;

// --------------------------------------------------------------- //
// Tela de Fim de Jogo

// Posição do Botão de Reiniciar o Jogo
extern GLfloat xButtonRestart, yButtonRestart, wButtonRestart, hButtonRestart;

// Posição do Botão de Sair do Jogo
extern GLfloat xButtonEndGameExit, yButtonEndGameExit, wButtonEndGameExit, hButtonEndGameExit;

// Posição do Mosquito de Game Over
extern GLfloat xMosquitoGameOver, yMosquitoGameOver, wMosquitoGameOver, hMosquitoGameOver;

// Posição da Pontuação Final
extern GLfloat xEndScore, yEndScore, wEndScore, hEndScore;

// --------------------------------------------------------------- //

// Tela de Fim

// Posição do Botão de Volta para o Jogo
extern GLfloat xButtonRestart, yButtonRestart, wButtonRestart, hButtonRestart;

// --------------------------------------------------------------- //

void updatePosition();

#endif