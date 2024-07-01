#include <GL/glut.h>
#include <screen.h>
#include <keyboard.h>
#include <position.h>
#include <utils.h>
#include <audio.h>
#include <texture.h>

int isHover(GLfloat xMouse, GLfloat yMouse, GLfloat xObj, GLfloat yObj, GLfloat wObj, GLfloat hObj)
{
    return (xMouse > xObj && xMouse < xObj + wObj && yMouse > yObj && yMouse < yObj + hObj);
}

void mouse(int button, int estado, int x, int y)
{
    int alturaMax = glutGet(GLUT_WINDOW_HEIGHT); // Armazena a altura máxima da tela

    // Converte a coordenada y do mouse para o sistema de coordenadas do OpenGL
    int yInvertido = alturaMax - y;

    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && telaAtual == HOME_SCREEN)
    {
        if (isHover(x, yInvertido, xButtonStart, yButtonStart, wButtonStart, hButtonStart)) // Verifica se "iniciar" foi selecionado
        {
            playSound(GAME_START);
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click
            changeScreen(GAME_SCREEN);          // Muda para a tela do jogo
        }
    }

    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && telaAtual == GAME_PAUSE_SCREEN)
    {
        if (isHover(x, yInvertido, xButtonContinue, yButtonContinue, wButtonContinue, hButtonContinue)) // Verifica se "continuar" foi selecionado
        {
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click
            changeScreen(GAME_SCREEN);          // Muda para a tela do jogo
        }
    }

    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && telaAtual == END_GAME_SCREEN)
    {
        if (isHover(x, yInvertido, xButtonRestart, yButtonRestart, wButtonRestart, hButtonRestart)) // Verifica se "recomeçar" foi selecionado
        {
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click
            changeScreen(HOME_SCREEN);          // Muda para a tela inicial
        }
    }

    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && (telaAtual == GAME_PAUSE_SCREEN || telaAtual == END_GAME_SCREEN))
    {
        if (isHover(x, yInvertido, xButtonExit, yButtonExit, wButtonExit, hButtonExit)) // Verifica se "sair" foi selecionado tanto na tela de pause, como na tela fim
        {
            exit(0); // Sai do jogo
        }
    }

    // Verifica se o botão "pause" foi clicado
    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && (telaAtual == GAME_SCREEN))
    {
        if (isHover(x, yInvertido, xButtonPause, yButtonPause, wButtonPause, hButtonPause)) // Verifica se "pause" foi selecionado
        {            
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click
            changeScreen(GAME_PAUSE_SCREEN);    // Muda para a tela de pause
        }
    }

    // Verifica se o botão "sobre" foi clicado
    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && (telaAtual == HOME_SCREEN))
    {
        if (isHover(x, yInvertido, xButtonAbout, yButtonAbout, wButtonAbout, hButtonAbout))
        {
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click

            // Mostra o modal de sobre
            telaAtual = ABOUT_SCREEN;
        }
    }

    // Verifica se o botão para fechar o banner de "sobre" foi clicado
    if (button == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && (telaAtual == ABOUT_SCREEN))
    {
        if (isHover(x, yInvertido, xButtonCloseAbout, yButtonCloseAbout, wButtonCloseAbout, hButtonCloseAbout))
        {
            glutSetCursor(GLUT_CURSOR_INHERIT); // Muda para cursor padrão após o click

            // Fecha o modal de sobre
            telaAtual = HOME_SCREEN;
        }
    }

    glutPostRedisplay();
}

// Verifica a cada movimento do mouse se ele está sobre algum botão para poder mudar o cursor
void passiveMouse(int x, int y)
{
    // Converte a coordenada Y para corresponder ao sistema de coordenadas do GLUT
    y = glutGet(GLUT_WINDOW_HEIGHT) - y;

    // Verifica se o mouse está sobre o botão "iniciar"
    if (isHover(x, y, xButtonStart, yButtonStart, wButtonStart, hButtonStart) && (telaAtual == HOME_SCREEN))
    {
        // Muda o cursor para quando estiver sobre o botão "iniciar"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    // Verifica se o mouse está sobre o botão "continuar"
    else if (isHover(x, y, xButtonContinue, yButtonContinue, wButtonContinue, hButtonContinue) && telaAtual == GAME_PAUSE_SCREEN)
    {
        // Muda o cursor para quando estiver sobre o botão "continuar"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    // Verifica se o mouse está sobre o botão "recomeçar"
    else if (isHover(x, y, xButtonRestart, yButtonRestart, wButtonRestart, hButtonRestart) && telaAtual == END_GAME_SCREEN)
    {
        // Muda o cursor para quando estiver sobre o botão "recomeçar"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    // Verifica se o mouse está sobre o botão "sair"
    else if (isHover(x, y, xButtonExit, yButtonExit, wButtonExit, hButtonExit) && (telaAtual == GAME_PAUSE_SCREEN || telaAtual == END_GAME_SCREEN))
    {
        // Muda o cursor para quando estiver sobre o botão "sair"
        glutSetCursor(GLUT_CURSOR_DESTROY);
    }
    // Verifica se o mouse está sobre o botão "pause"
    else if (isHover(x, y, xButtonPause, yButtonPause, wButtonPause, hButtonPause) && (telaAtual == GAME_SCREEN))
    {
        // Muda o cursor para quando estiver sobre o botão "pause"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    // Verifica se o mouse está sobre o botão "sobre"
    else if (isHover(x, y, xButtonAbout, yButtonAbout, wButtonAbout, hButtonAbout) && (telaAtual == HOME_SCREEN))
    {
        // Muda o cursor para quando estiver sobre o botão "sobre"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    // Verifica se o mouse está sobre o botão de fechar o "sobre"
    else if (isHover(x, y, xButtonCloseAbout, yButtonCloseAbout, wButtonCloseAbout, hButtonCloseAbout) && (telaAtual == ABOUT_SCREEN))
    {
        // Muda o cursor para quando estiver sobre o botão "sobre"
        glutSetCursor(GLUT_CURSOR_INFO);
    }
    else
    {
        // Caso contrário, volta para o cursor padrão
        glutSetCursor(GLUT_CURSOR_INHERIT);
    }
}