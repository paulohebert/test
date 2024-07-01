#ifndef AUDIO_H
#define AUDIO_H

/* Quantidade de Áudios */
#define NUM_AUDIOS 7
/* Áudios */
#define SHOT 0       /* Índice do Áudio da Espingarda */
#define RAIN 1       /* Índice do Áudio de Fundo com a Chuva */
#define GAME_START 2 /* Índice do Áudio de Iniciar o Jogo */
#define FALL 3       /* Índice do Áudio do Jogador Atingido pelo Mosquito */
#define LOSE 4       /* Índice do Áudio de Game Over */
#define DESTROY 5    /* Índice do Áudio de destruir o inimigo */
#define OPENING 6    /* Índice do Áudio da Abertura do Jogo */

// Inicializa o som na memória
void initAudios();

// Aumenta o Volume de todos os áudios
void upVolume();

// Diminui o Volume de todos os áudios
void downVolume();

// Libera o som da memória
void freeAudios();

// Toca o som
void playSound(int audioID);

// Desabilita o som em loop
void stopSoundLoop(int audioID);

#endif