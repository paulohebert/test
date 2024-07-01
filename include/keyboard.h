#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GL/glut.h>

extern GLfloat translateX, translateY;

extern bool flip;

void teclado(unsigned char, int, int);

void teclasEspeciais(int, int, int);
void specialKeysUp(int tecla, int x, int y);

#endif