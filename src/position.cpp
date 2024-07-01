#include <GL/glut.h>
#include <screen.h>

// --------------------------------------------------------------- //
// Tela de Início

// Posição da Logo do Jogo Aedes Attack
GLfloat xAedesAttack; // Posição X do Canto Inferior Esquerdo
GLfloat yAedesAttack; // Posição Y do Canto Inferior Esquerdo
GLfloat wAedesAttack; // Largura
GLfloat hAedesAttack; // Altura

// Posição da Logo da Univasf
GLfloat xUnivasf; // Posição X do Canto Inferior Esquerdo
GLfloat yUnivasf; // Posição Y do Canto Inferior Esquerdo
GLfloat wUnivasf; // Largura
GLfloat hUnivasf; // Altura

// Posição da Placa de Proibido Mosquito
GLfloat xMosquitoProhibited; // Posição X do Canto Inferior Esquerdo
GLfloat yMosquitoProhibited; // Posição Y do Canto Inferior Esquerdo
GLfloat wMosquitoProhibited; // Largura
GLfloat hMosquitoProhibited; // Altura

// Posição do Botão de Iniciar do Jogo
GLfloat xButtonStart; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonStart; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonStart; // Largura
GLfloat hButtonStart; // Altura

// Posição do Botão de Sobre
GLfloat xButtonAbout; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonAbout; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonAbout; // Largura
GLfloat hButtonAbout; // Altura

// --------------------------------------------------------------- //
// Tela de Sobre

// Posição do Banner de Sobre
GLfloat xAbout; // Posição X do Canto Inferior Esquerdo
GLfloat yAbout; // Posição Y do Canto Inferior Esquerdo
GLfloat wAbout; // Largura
GLfloat hAbout; // Altura

// Posição do Botão de Fechar o banner de Sobre
GLfloat xButtonCloseAbout; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonCloseAbout; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonCloseAbout; // Largura
GLfloat hButtonCloseAbout; // Altura

// --------------------------------------------------------------- //
// Tela do Jogo

// Posição do Botão de Pause do Jogo
GLfloat xButtonPause; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonPause; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonPause; // Largura
GLfloat hButtonPause; // Altura

// Posição do Banner de Combate à Dengue
GLfloat xBannerDengue; // Posição X do Canto Inferior Esquerdo
GLfloat yBannerDengue; // Posição Y do Canto Inferior Esquerdo
GLfloat wBannerDengue; // Largura
GLfloat hBannerDengue; // Altura

// Posição do Jogador
GLfloat xPlayer; // Posição X do Canto Inferior Esquerdo
GLfloat yPlayer; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlayer; // Largura
GLfloat hPlayer; // Altura

// Posição do Mosquito
GLfloat xMosquito; // Posição X do Canto Inferior Esquerdo
GLfloat yMosquito; // Posição Y do Canto Inferior Esquerdo
GLfloat wMosquito; // Largura
GLfloat hMosquito; // Altura

// Posição da Plataforma de Piso do Chão
GLfloat xPlatformFloor; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatformFloor; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatformFloor; // Largura
GLfloat hPlatformFloor; // Altura

// Posição da Plataforma Suspensa 1
GLfloat xPlatform1; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatform1; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatform1; // Largura
GLfloat hPlatform1; // Altura

// Posição da Plataforma Suspensa 2
GLfloat xPlatform2; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatform2; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatform2; // Largura
GLfloat hPlatform2; // Altura

// Posição da Plataforma Suspensa 3
GLfloat xPlatform3; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatform3; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatform3; // Largura
GLfloat hPlatform3; // Altura

// Posição da Plataforma Suspensa 4
GLfloat xPlatform4; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatform4; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatform4; // Largura
GLfloat hPlatform4; // Altura

// Posição da Plataforma Suspensa 5
GLfloat xPlatform5; // Posição X do Canto Inferior Esquerdo
GLfloat yPlatform5; // Posição Y do Canto Inferior Esquerdo
GLfloat wPlatform5; // Largura
GLfloat hPlatform5; // Altura

// Posição das Vidas
GLfloat xHeart;      // Posição X do Canto Inferior Esquerdo
GLfloat yHeart;      // Posição Y do Canto Inferior Esquerdo
GLfloat wHeart;      // Largura
GLfloat hHeart;      // Altura
GLfloat offsetHeart; // Distância entre cada Vida

// Posição da Pontuação
GLfloat xScore; // Posição X do Canto Inferior Esquerdo
GLfloat yScore; // Posição Y do Canto Inferior Esquerdo
GLfloat wScore; // Largura
GLfloat hScore; // Altura

// Posição do Timer
GLfloat xTimer; // Posição X do Canto Inferior Esquerdo
GLfloat yTimer; // Posição Y do Canto Inferior Esquerdo
GLfloat wTimer; // Largura
GLfloat hTimer; // Altura

// Posição do Nível Atual
GLfloat xLevel; // Posição X do Canto Inferior Esquerdo
GLfloat yLevel; // Posição Y do Canto Inferior Esquerdo
GLfloat wLevel; // Largura
GLfloat hLevel; // Altura

// --------------------------------------------------------------- //
// Tela de Pause

// Posição do Botão de Volta para o Jogo
GLfloat xButtonContinue; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonContinue; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonContinue; // Largura
GLfloat hButtonContinue; // Altura

// Posição do Botão de Sair do Jogo
GLfloat xButtonExit; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonExit; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonExit; // Largura
GLfloat hButtonExit; // Altura

// Posição do Banner de Combate à Dengue
GLfloat xBannerDengueCenter; // Posição X do Canto Inferior Esquerdo
GLfloat yBannerDengueCenter; // Posição Y do Canto Inferior Esquerdo
GLfloat wBannerDengueCenter; // Largura
GLfloat hBannerDengueCenter; // Altura

// --------------------------------------------------------------- //
// Tela de Fim de Jogo

// Posição do Botão de Recomeçar o Jogo
GLfloat xButtonRestart; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonRestart; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonRestart; // Largura
GLfloat hButtonRestart; // Altura

// Posição do Botão de Sair do Jogo
GLfloat xButtonEndGameExit; // Posição X do Canto Inferior Esquerdo
GLfloat yButtonEndGameExit; // Posição Y do Canto Inferior Esquerdo
GLfloat wButtonEndGameExit; // Largura
GLfloat hButtonEndGameExit; // Altura

// Posição do Mosquito de Game Over
GLfloat xMosquitoGameOver; // Posição X do Canto Inferior Esquerdo
GLfloat yMosquitoGameOver; // Posição Y do Canto Inferior Esquerdo
GLfloat wMosquitoGameOver; // Largura
GLfloat hMosquitoGameOver; // Altura

// Posição da Pontuação Final
GLfloat xEndScore; // Posição X do Canto Inferior Esquerdo
GLfloat yEndScore; // Posição Y do Canto Inferior Esquerdo
GLfloat wEndScore; // Largura
GLfloat hEndScore; // Altura

// --------------------------------------------------------------- //

// Centralizar o objeto em X ou Y
GLfloat centerPosition(GLfloat objSize, GLfloat windowSize)
{
    return (windowSize - objSize) / 2;
}

// Atualizar a Posição quando redimensionar a tela (Assim, não há a necessidade de ficar recalculando a cada atualização dos frames)
void updatePosition()
{

    // --------------------------------------------------------------- //
    // Tela de Início

    // Posição da Logo do Jogo Aedes Attack
    xAedesAttack = larguraJanela * 0.3; // Posição X do Canto Inferior Esquerdo
    yAedesAttack = alturaJanela * 0.7;  // Posição Y do Canto Inferior Esquerdo
    wAedesAttack = larguraJanela * 0.4; // Largura
    hAedesAttack = alturaJanela * 0.2;  // Altura

    // Posição da Logo da Univasf
    wUnivasf = larguraJanela * 0.14;            // Largura
    hUnivasf = wUnivasf * 0.26;                 // Altura
    xUnivasf = larguraJanela * 0.99 - wUnivasf; // Posição X do Canto Inferior Esquerdo
    yUnivasf = alturaJanela * 0.02;             // Posição Y do Canto Inferior Esquerdo

    // Posição da Placa de Proibido Mosquito
    xMosquitoProhibited = larguraJanela * 0.45; // Posição X do Canto Inferior Esquerdo
    yMosquitoProhibited = alturaJanela * 0.62;  // Posição Y do Canto Inferior Esquerdo
    wMosquitoProhibited = larguraJanela * 0.1;  // Largura
    hMosquitoProhibited = larguraJanela * 0.1;  // Altura

    // Posição do Botão de Iniciar do Jogo
    wButtonStart = larguraJanela * 0.2;                         // Largura
    hButtonStart = alturaJanela * 0.12;                         // Altura
    xButtonStart = centerPosition(wButtonStart, larguraJanela); // Posição X do Canto Inferior Esquerdo
    yButtonStart = centerPosition(hButtonStart, alturaJanela);  // Posição Y do Canto Inferior Esquerdo

    // Posição do Botão de Sobre
    wButtonAbout = wButtonStart;                                      // Largura
    hButtonAbout = hButtonStart;                                      // Altura
    xButtonAbout = xButtonStart;                                      // Posição X do Canto Inferior Esquerdo
    yButtonAbout = yButtonStart - hButtonAbout - alturaJanela * 0.02; // Posição Y do Canto Inferior Esquerdo

    // --------------------------------------------------------------- //
    // Tela de Sobre

    // Posição do Banner de Sobre
    wAbout = larguraJanela / 2; // Largura
    hAbout = alturaJanela / 2;  // Altura
    xAbout = larguraJanela / 4; // Posição X do Canto Inferior Esquerdo
    yAbout = alturaJanela / 4;  // Posição Y do Canto Inferior Esquerdo

    // Posição do Botão de Fechar o banner de Sobre

    wButtonCloseAbout = larguraJanela * 0.02;                      // Largura
    hButtonCloseAbout = wButtonCloseAbout;                         // Altura
    xButtonCloseAbout = xAbout + wAbout - wButtonCloseAbout * 1.4; // Posição X do Canto Inferior Esquerdo
    yButtonCloseAbout = yAbout + hAbout - hButtonCloseAbout * 1.4; // Posição Y do Canto Inferior Esquerdo

    // --------------------------------------------------------------- //
    // Tela do Jogo

    // Posição do Botão de Pause do Jogo
    wButtonPause = larguraJanela * 0.05;        // Largura
    hButtonPause = larguraJanela * 0.05;        // Altura
    xButtonPause = 0;                           // Posição X do Canto Inferior Esquerdo
    yButtonPause = alturaJanela - hButtonPause; // Posição Y do Canto Inferior Esquerdo

    // Posição do Banner de Combate à Dengue
    wBannerDengue = larguraJanela * 0.14;               // Largura
    hBannerDengue = alturaJanela * 0.3;                 // Altura
    xBannerDengue = larguraJanela - wBannerDengue - 10; // Posição X do Canto Inferior Esquerdo
    yBannerDengue = alturaJanela - hBannerDengue - 10;  // Posição Y do Canto Inferior Esquerdo

    // Posição da Plataforma de Piso do Chão
    xPlatformFloor = 0;                    // Posição X do Canto Inferior Esquerdo
    yPlatformFloor = alturaJanela * -0.01; // Posição Y do Canto Inferior Esquerdo
    wPlatformFloor = larguraJanela;        // Largura
    hPlatformFloor = alturaJanela * 0.05;  // Altura

    // Posição da Plataforma Suspensa 1
    xPlatform1 = larguraJanela * 0.1; // Posição X do Canto Inferior Esquerdo
    yPlatform1 = alturaJanela * 0.2;  // Posição Y do Canto Inferior Esquerdo
    wPlatform1 = larguraJanela * 0.2; // Largura
    hPlatform1 = alturaJanela * 0.05; // Altura

    // Posição da Plataforma Suspensa 2
    xPlatform2 = larguraJanela * 0.4; // Posição X do Canto Inferior Esquerdo
    yPlatform2 = alturaJanela * 0.4;  // Posição Y do Canto Inferior Esquerdo
    wPlatform2 = larguraJanela * 0.2; // Largura
    hPlatform2 = alturaJanela * 0.05; // Altura

    // Posição da Plataforma Suspensa 3
    xPlatform3 = larguraJanela * 0.7; // Posição X do Canto Inferior Esquerdo
    yPlatform3 = alturaJanela * 0.55; // Posição Y do Canto Inferior Esquerdo
    wPlatform3 = larguraJanela * 0.2; // Largura
    hPlatform3 = alturaJanela * 0.05; // Altura

    // Posição da Plataforma Suspensa 4
    xPlatform4 = larguraJanela * 0.07; // Posição X do Canto Inferior Esquerdo
    yPlatform4 = alturaJanela * 0.55;  // Posição Y do Canto Inferior Esquerdo
    wPlatform4 = larguraJanela * 0.2;  // Largura
    hPlatform4 = alturaJanela * 0.05;  // Altura

    // Posição da Plataforma Suspensa 5
    xPlatform5 = larguraJanela * 0.73; // Posição X do Canto Inferior Esquerdo
    yPlatform5 = alturaJanela * 0.25;  // Posição Y do Canto Inferior Esquerdo
    wPlatform5 = larguraJanela * 0.2;  // Largura
    hPlatform5 = alturaJanela * 0.05;  // Altura

    // Posição do Jogador
    xPlayer = larguraJanela * 0.1;                   // Posição X do Canto Inferior Esquerdo
    yPlayer = yPlatformFloor + hPlatformFloor * 0.8; // Posição Y do Canto Inferior Esquerdo
    wPlayer = alturaJanela * 0.1;                    // Largura
    hPlayer = alturaJanela * 0.16;                   // Altura

    // Posição do Mosquito
    xMosquito = larguraJanela * 0.45; // Posição X do Canto Inferior Esquerdo
    yMosquito = alturaJanela * 0.17;  // Posição Y do Canto Inferior Esquerdo
    wMosquito = alturaJanela * 0.1;   // Largura
    hMosquito = alturaJanela * 0.1;   // Altura

    // Posição das Vidas
    wHeart = larguraJanela * 0.035;                         // Largura
    hHeart = wHeart;                                        // Altura
    xHeart = larguraJanela * 0.05;                          // Posição X do Canto Inferior Esquerdo
    yHeart = alturaJanela - hHeart - (alturaJanela * 0.01); // Posição Y do Canto Inferior Esquerdo
    offsetHeart = larguraJanela / 50;                       // Distância entre cada Vida

    // Posição da Pontuação
    wScore = larguraJanela * 0.14;             // Largura
    hScore = wScore / 3;                       // Altura
    xScore = larguraJanela * 0.85 - wScore;     // Posição X do Canto Inferior Esquerdo
    yScore = alturaJanela * 0.95 - hScore / 2; // Posição Y do Canto Inferior Esquerdo

    // Posição do Timer
    wTimer = larguraJanela * 0.14;             // Largura
    hTimer = wTimer / 3;                       // Altura
    xTimer = larguraJanela * 0.7 - wTimer;     // Posição X do Canto Inferior Esquerdo
    yTimer = alturaJanela * 0.95 - hTimer / 2; // Posição Y do Canto Inferior Esquerdo

    // Posição do Nível Atual
    wLevel = larguraJanela * 0.14;             // Largura
    hLevel = wLevel / 3;                       // Altura
    xLevel = larguraJanela * 0.55 - wLevel;     // Posição X do Canto Inferior Esquerdo
    yLevel = alturaJanela * 0.95 - hLevel / 2; // Posição Y do Canto Inferior Esquerdo

    // --------------------------------------------------------------- //
    // Tela de Pause

    // Posição do Botão de Volta para o Jogo
    wButtonContinue = alturaJanela * 0.1;                      // Largura
    hButtonContinue = alturaJanela * 0.1;                      // Altura
    xButtonContinue = (larguraJanela - wButtonContinue) * 0.4; // Posição X do Canto Inferior Esquerdo
    yButtonContinue = (alturaJanela - hButtonContinue) * 0.75; // Posição Y do Canto Inferior Esquerdo

    // Posição do Botão de Sair do Jogo
    wButtonExit = wButtonContinue;                     // Largura
    hButtonExit = hButtonContinue;                     // Altura
    xButtonExit = (larguraJanela - wButtonExit) * 0.6; // Posição X do Canto Inferior Esquerdo
    yButtonExit = yButtonContinue;                     // Posição Y do Canto Inferior Esquerdo

    // Posição do Banner de Combate à Dengue
    hBannerDengueCenter = alturaJanela * 0.55;                                                         // Altura
    wBannerDengueCenter = hBannerDengueCenter * 0.9;                                                   // Largura
    xBannerDengueCenter = centerPosition(wBannerDengueCenter, larguraJanela);                          // Posição X do Canto Inferior Esquerdo
    yBannerDengueCenter = centerPosition(hBannerDengueCenter, alturaJanela) - hBannerDengueCenter / 3; // Posição Y do Canto Inferior Esquerdo

    // --------------------------------------------------------------- //
    // Tela de Fim de Jogo

    // Posição do Botão de Reiniciar o Jogo
    xButtonRestart = xButtonContinue; // Posição X do Canto Inferior Esquerdo
    yButtonRestart = yButtonContinue; // Posição Y do Canto Inferior Esquerdo
    wButtonRestart = wButtonContinue; // Largura
    hButtonRestart = hButtonContinue; // Altura

    // Posição do Botão de Sair do Jogo
    xButtonEndGameExit = xButtonExit; // Posição X do Canto Inferior Esquerdo
    yButtonEndGameExit = yButtonExit; // Posição Y do Canto Inferior Esquerdo
    wButtonEndGameExit = wButtonExit; // Largura
    hButtonEndGameExit = hButtonExit; // Altura

    // Posição do Mosquito de Game Over
    wMosquitoGameOver = larguraJanela * 0.2;                              // Largura
    hMosquitoGameOver = wMosquitoGameOver;                                // Altura
    xMosquitoGameOver = centerPosition(wMosquitoGameOver, larguraJanela); // Posição X do Canto Inferior Esquerdo
    yMosquitoGameOver = alturaJanela * 0.05;                              // Posição Y do Canto Inferior Esquerdo

    // Posição da Pontuação Final
    wEndScore = alturaJanela * 0.3;                          // Largura
    hEndScore = wEndScore / 3;                               // Altura
    xEndScore = centerPosition(wEndScore, larguraJanela);    // Posição X do Canto Inferior Esquerdo
    yEndScore = yMosquitoGameOver + hMosquitoGameOver * 1.2; // Posição Y do Canto Inferior Esquerdo

    // --------------------------------------------------------------- //
}