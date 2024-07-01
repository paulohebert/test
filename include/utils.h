#ifndef UTILS_H
#define UTILS_H

extern int tempoRestante, t, cura;

void escreveTextoBitmap(float x, float y, void *font, const char *string);

void atualizaTempo(int valor);
void atualizaMovimento(int);
void curaPlayer ();

/* Anima as texturas */
void animateHomeScreenTextures(int);
void animateGameScreenTextures(int);
void animateGamePauseScreenTextures(int);
void animateEndGameScreenTextures(int);
void animatePlayerDead(int);

#endif