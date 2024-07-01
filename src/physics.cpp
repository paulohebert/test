#include <GL/glut.h>
#include <keyboard.h>
#include <screen.h>
#include <position.h>
#include <texture.h>
#include <utils.h>
#include <vector>
#include <cmath>
#include <time.h>
#include <audio.h>

#define MAX_MOSQUITOS 5

bool playerNoChao;
GLfloat playerVelocity = 5;
GLfloat movePlayerX;
GLfloat movePlayerY;
GLfloat gravity = 8.0;

// Defina uma variável global para controlar o estado do pulo
bool isJumping = false;
GLfloat jumpStrength = 230.0f; // Força do pulo
GLfloat jumpVelocity = 10.0f;  // Velocidade vertical do pulo
GLfloat jumpHeight = 0.0f;     // Altura atual do pulo

// Quantidade de Vidas do Jogador
int lives;

// Variável que vai contabilizar pontos após sobreviver 10s ou eliminar um mosquito
int score = 0;

// Variável que vai controlar a velocidade do mosquito por nível
int v = 1;

// Verifica se o jogador acabou de perder uma vida
bool dead = false;

// Define variável que verifica se há um botão de movimento horizontal pressionado
bool leftPressed = false;
bool rightPressed = false;

// Define variáveis de controle de disparo
struct disparo
{
    GLfloat x, y;
    GLfloat largura = 30, altura = 10;
    GLfloat velocity = 10;
    bool direita = true;
};
std::vector<disparo> disparos;
bool direcaoDisparo = true;

// Variáveis de controle dos mosquitos
struct Mosquito
{
    GLfloat x, y;
    GLfloat largura = wMosquito, altura = hMosquito;
    GLfloat velocity = v;
};
std::vector<Mosquito> mosquitos;

void updatePlayerLife()
{
    if (lives > 1)
    {
        lives--; // Reduz uma vida do jogador

        // Mostra a animação do jogador perdendo uma vida
        dead = true;                            // Define para mudar a animação
        glutTimerFunc(0, animatePlayerDead, 0); // Loop
    }
    else
    {
        changeScreen(END_GAME_SCREEN);
    }
}

bool verificaColisaoEsquerda()
{
    if (!(translateX < xPlatform1 + wPlatform1 / 2 + jumpVelocity &&                            // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform1 - wPlatform1 / 2 - wPlayer + playerVelocity + jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform1 + hPlatform1 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform1 - hPlayer)                                                    // Verifica se a parte inferior do objeto1 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform2 + wPlatform2 / 2 + jumpVelocity &&                            // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform2 - wPlatform2 / 2 - wPlayer + playerVelocity + jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform2 + hPlatform2 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform2 - hPlayer)                                                    // Verifica se a parte inferior do objeto2 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform3 + wPlatform3 / 2 + jumpVelocity &&                            // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform3 - wPlatform3 / 2 - wPlayer + playerVelocity + jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform3 + hPlatform3 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform3 - hPlayer)                                                    // Verifica se a parte inferior do objeto4 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform4 + wPlatform4 / 2 + jumpVelocity &&                            // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform4 - wPlatform4 / 2 - wPlayer + playerVelocity + jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform4 + hPlatform4 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform4 - hPlayer)                                                    // Verifica se a parte inferior do objeto3 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform5 + wPlatform5 / 2 + jumpVelocity &&                            // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform5 - wPlatform5 / 2 - wPlayer + playerVelocity + jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform5 + hPlatform5 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform5 - hPlayer))                                                   // Verifica se a parte inferior do objeto5 em movimento está acima da parte inferior do objeto estático
    {
        return true;
    }
    return false;
}

bool verificaColisaoDireita()
{
    if (!(translateX < xPlatform1 + wPlatform1 / 2 - wPlayer - playerVelocity - jumpVelocity && // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform1 - wPlatform1 / 2 - wPlayer - jumpVelocity &&                  // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform1 + hPlatform1 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform1 - hPlayer)                                                    // Verifica se a parte inferior do objeto1 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform2 + wPlatform2 / 2 - wPlayer - playerVelocity - jumpVelocity && // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform2 - wPlatform2 / 2 - wPlayer - jumpVelocity &&                  // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform2 + hPlatform2 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform2 - hPlayer)                                                    // Verifica se a parte inferior do objeto2 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform3 + wPlatform3 / 2 - wPlayer - playerVelocity - jumpVelocity && // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform3 - wPlatform3 / 2 - wPlayer - jumpVelocity &&                  // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform3 + hPlatform3 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform3 - hPlayer)                                                    // Verifica se a parte inferior do objeto4 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform4 + wPlatform4 / 2 - wPlayer - playerVelocity - jumpVelocity && // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform4 - wPlatform4 / 2 - wPlayer - jumpVelocity &&                  // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform4 + hPlatform4 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform4 - hPlayer)                                                    // Verifica se a parte inferior do objeto3 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform5 + wPlatform5 / 2 - wPlayer - playerVelocity - jumpVelocity && // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform5 - wPlatform5 / 2 - wPlayer - jumpVelocity &&                  // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform5 + hPlatform5 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform5 - hPlayer))                                                   // Verifica se a parte inferior do objeto5 em movimento está acima da parte inferior do objeto estático
    {
        return true;
    }
    return false;
}

bool verificaColisaoEmbaixo()
{
    if (!(translateX < xPlatform1 + wPlatform1 / 2 - playerVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform1 - wPlatform1 / 2 - wPlayer + playerVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform1 + hPlatform1 / 2 &&                            // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform1 - hPlayer)                                     // Verifica se a parte inferior do objeto1 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform2 + wPlatform2 / 2 - playerVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform2 - wPlatform2 / 2 - wPlayer + playerVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform2 + hPlatform2 / 2 &&                            // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform2 - hPlayer)                                     // Verifica se a parte inferior do objeto2 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform3 + wPlatform3 / 2 - playerVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform3 - wPlatform3 / 2 - wPlayer + playerVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform3 + hPlatform3 / 2 &&                            // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform3 - hPlayer)                                     // Verifica se a parte inferior do objeto4 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform4 + wPlatform4 / 2 - playerVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform4 - wPlatform4 / 2 - wPlayer + playerVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform4 + hPlatform4 / 2 &&                            // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform4 - hPlayer)                                     // Verifica se a parte inferior do objeto3 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform5 + wPlatform5 / 2 - playerVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform5 - wPlatform5 / 2 - wPlayer + playerVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform5 + hPlatform5 / 2 &&                            // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform5 - hPlayer))                                    // Verifica se a parte inferior do objeto5 em movimento está acima da parte inferior do objeto estático
    {
        return true;
    }
    return false;
}

bool verificaColisaoCima()
{
    if (!(translateX < xPlatform1 + wPlatform1 / 2 - playerVelocity + jumpVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform1 - wPlatform1 / 2 - wPlayer + playerVelocity - jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform1 + hPlatform1 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform1 - hPlayer - jumpVelocity)                                     // Verifica se a parte inferior do objeto1 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform2 + wPlatform2 / 2 - playerVelocity + jumpVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform2 - wPlatform2 / 2 - wPlayer + playerVelocity - jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform2 + hPlatform2 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform2 - hPlayer - jumpVelocity)                                     // Verifica se a parte inferior do objeto2 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform3 + wPlatform3 / 2 - playerVelocity + jumpVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform3 - wPlatform3 / 2 - wPlayer + playerVelocity - jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform3 + hPlatform3 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform3 - hPlayer - jumpVelocity)                                     // Verifica se a parte inferior do objeto4 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform4 + wPlatform4 / 2 - playerVelocity + jumpVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform4 - wPlatform4 / 2 - wPlayer + playerVelocity - jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform4 + hPlatform4 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform4 - hPlayer - jumpVelocity)                                     // Verifica se a parte inferior do objeto3 em movimento está acima da parte inferior do objeto estático
        &&
        !(translateX < xPlatform5 + wPlatform5 / 2 - playerVelocity + jumpVelocity &&           // Verifica se o lado direito do objeto1 em movimento está à esquerda do lado direito do objeto estático
          translateX > xPlatform5 - wPlatform5 / 2 - wPlayer + playerVelocity - jumpVelocity && // Verifica se o lado esquerdo do objeto1 em movimento está à direita do lado esquerdo do objeto estático
          translateY < yPlatform5 + hPlatform5 / 2 - gravity &&                                 // Verifica se a parte superior do objeto1 em movimento está abaixo da parte superior do objeto estático
          translateY > yPlatform5 - hPlayer - jumpVelocity))                                    // Verifica se a parte inferior do objeto5 em movimento está acima da parte inferior do objeto estático
    {
        return true;
    }
    return false;
}

// Verifica se há colisão embaixo e se o jogador não está pulando para ativar a gravidade
bool applyGravity()
{
    if (translateY > alturaJanela * 0.05 - 40 && !isJumping && verificaColisaoEmbaixo())
    {
        return true; // Aplicar gravidade apenas se não houver colisão embaixo e o jogador não estiver pulando
    }
    else
    {
        return false;
    }
}

// Atualiza a posição dos disparos na tela fazendo se mover na horizontal
void moveDisparos()
{
    for (auto &disparo : disparos)
    {
        if (disparo.direita)
        {
            disparo.x += disparo.velocity;
        }
        else
        {
            disparo.x -= disparo.velocity;
        }
    }
}

// Função para controlar o pulo do jogador
void jump(int value)
{
    if (isJumping)
    {
        // Atualize a posição vertical do jogador
        jumpHeight += jumpVelocity;
        translateY += jumpVelocity;

        // Verifique se o jogador atingiu a altura máxima do pulo
        if (jumpHeight >= jumpStrength || !verificaColisaoCima())
        {
            isJumping = false;
            jumpHeight = 0.0f;
        }

        // Redesenhe a cena
        glutPostRedisplay();

        // Registre a função de salto novamente para o próximo quadro
        glutTimerFunc(10, jump, 0); // 16 ms para aproximadamente 60 FPS
    }
}

// Função para iniciar o pulo do jogador
void startJump()
{
    if (!isJumping)
    {
        isJumping = true;
        jumpHeight = 0.0f;
        glutTimerFunc(0, jump, 0); // Inicia o temporizador de salto
    }
}

// Desenhar os disparos na tela
void disparar()
{
    for (const auto &disparo : disparos)
    {
        draw(DISPARO_FRAME, disparo.x, disparo.y, disparo.largura, disparo.altura);
    }
}

// Desenha mosquitos na tela
void desenhaMosquito()
{
    for (const auto &mosquito : mosquitos)
    {        
        drawTexture(MOSQUITO_ENEMY, 0.0f, 0.0f, 0.5f, 0.5f, mosquito.x, mosquito.y, mosquito.largura, mosquito.altura);
    }
}

void adicionaMosquito()
{
    if (mosquitos.size() < MAX_MOSQUITOS)
    {
        Mosquito novoMosquito;
        int lado = rand() % 3; // Escolhe um dos lados da tela para gerar o mosquito

        switch (lado)
        {
        case 0: // Topo
            novoMosquito.x = rand() % larguraJanela;
            novoMosquito.y = alturaJanela + 100;
            break;
        case 1: // Esquerda
            novoMosquito.x = -100;
            novoMosquito.y = rand() % alturaJanela;            
            break;
        case 2: // Direita
            novoMosquito.x = larguraJanela + 100;
            novoMosquito.y = rand() % alturaJanela;            
            break;
        }
        mosquitos.push_back(novoMosquito);
    }
}

void moveMosquitos()
{
    for (auto &mosquito : mosquitos)
    {
        // Calcula a diferença de posição entre o mosquito e o personagem
        GLfloat deltaX = translateX + xPlayer - mosquito.x - wPlayer/2 + mosquito.largura/2;
        GLfloat deltaY = translateY + yPlayer - mosquito.y + mosquito.altura/2;

        // Calcula a distância
        GLfloat distance = sqrt(deltaX * deltaX + deltaY * deltaY);
        
        // Normaliza os vetores de movimento, evita divisão por zero
        if (distance != 0)
        {
            GLfloat normX = deltaX / distance;
            GLfloat normY = deltaY / distance;

            // Move o mosquito em direção ao personagem
            mosquito.x += normX * mosquito.velocity;
            mosquito.y += normY * mosquito.velocity;
        }
    }
}

// Função para detecção de colisão entre duas caixas (retângulos)
bool isCollision(GLfloat x1, GLfloat y1, GLfloat width1, GLfloat height1, GLfloat x2, GLfloat y2, GLfloat width2, GLfloat height2)
{
    return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

// Função para detectar colisões e atualizar o jogo
void colideMosquitos()
{
    auto mosquitoIt = mosquitos.begin();
    while(mosquitoIt < mosquitos.end())
    {
        Mosquito &mosquitoTemp = *mosquitoIt;

        // Verificar colisão entre o personagem e o mosquito
        if (isCollision(translateX + xPlayer, translateY + yPlayer, wPlayer/2, hPlayer/2,
                        mosquitoTemp.x, mosquitoTemp.y, mosquitoTemp.largura, mosquitoTemp.altura))
        {
            playSound(FALL);
            updatePlayerLife(); // Atualize a vida do jogador, se necessário
            mosquitoIt = mosquitos.erase(mosquitoIt);
            continue;
        }

        // Verificar colisão entre disparos e o mosquito
        auto disparoIt = disparos.begin();
        bool morreu = false;
        while(disparoIt < disparos.end())
        {
            disparo &disparoTemp = *disparoIt;
            if (isCollision(disparoTemp.x, disparoTemp.y, disparoTemp.largura, disparoTemp.altura,
                            mosquitoTemp.x, mosquitoTemp.y, mosquitoTemp.largura, mosquitoTemp.altura))
            {
                playSound(DESTROY);
                mosquitoIt = mosquitos.erase(mosquitoIt);
                score += 10;
                disparos.erase(disparoIt);
                morreu = true;
                break;
            }
            if(disparoTemp.x < 0 || disparoTemp.x > larguraJanela){
                disparoIt = disparos.erase(disparoIt);
            }else{
                disparoIt++;
            }

        }
        if(!morreu)
            mosquitoIt++;
    }
}

// Atualiza a posição de objetos na tela
void moveObjetos()
{
    if (applyGravity())
    {
        translateY -= gravity;
    }

    // Atualizar a velocidade horizontal com base nas teclas pressionadas
    if (leftPressed && translateX > -150 && verificaColisaoEsquerda())
    {
        movePlayerX = -playerVelocity;
    }
    else if (rightPressed && translateX < larguraJanela - 250 && verificaColisaoDireita())
    {
        movePlayerX = playerVelocity;
    }
    else
    {
        movePlayerX = 0.0;
    }

    // Chama a função que atualiza a posição dos disparos
    moveDisparos();

    // Chama a função que atualiza a posição dos disparos
    moveMosquitos();
    colideMosquitos();

    // Atualiza a posição do player
    translateX += movePlayerX;
    translateY += movePlayerY;
    movePlayerX = 0;
    movePlayerY = 0;
}
