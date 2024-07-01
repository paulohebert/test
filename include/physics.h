#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdbool.h>
#include <GL/glut.h>
#include <vector> 
#define MAX_MOSQUITOS 10

extern bool playerNoChao;
extern GLfloat gravity;
extern GLfloat playerVelocity;
extern GLfloat movePlayerX;
extern GLfloat movePlayerY;
extern GLfloat jumpStrength;
extern bool isJumping;
extern GLfloat jumpVelocity;
extern GLfloat jumpHeight; 
extern bool leftPressed;
extern bool rightPressed;
struct disparo {
    GLfloat x, y;
    GLfloat largura = 20, altura = 10;
    GLfloat velocity;
    bool direita;
};
extern std::vector<disparo> disparos;
extern bool direcaoDisparo;
struct Mosquito {
    GLfloat x, y;
    GLfloat largura, altura;
    GLfloat velocity;
    bool ativo;
};
extern std::vector<Mosquito> mosquitos;

// Quantidade de Vidas do Jogador
extern int lives;

// Variável que vai contabilizar pontos após sobreviver 10s ou eliminar um mosquito
extern int score;

// Variável que vai controlar a velocidade dos mosquitos por nível
extern int v;

// Verifica se o jogador acabou de perder uma vida
extern bool dead;

bool verificaColisaoEsquerda();
bool verificaColisaoDireita();
bool verificaColisaoEmbaixo();
bool verificaColisaoCima();
bool applyGravity();
void moveObjetos();
void jump(int value);
void startJump();;
void disparar();
void moveDisparos();
void adicionaMosquito();
void moveMosquitos();
void desenhaMosquito();
bool isCollision(GLfloat x1, GLfloat y1, GLfloat width1, GLfloat height1, GLfloat x2, GLfloat y2, GLfloat width2, GLfloat height2);
void removeMosquito(int index);
void colideMosquitos();


#endif // PHYSICS_H