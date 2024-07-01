#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include <audio.h>

/* Carrega a engine de áudio */
ma_engine engine;
/* Armazena todos os áudios */
ma_sound *audios;

int volume = 5; // Volume inicial (50%)

void loadAudio(ma_sound *sound, const char *filename)
{
    if (ma_sound_init_from_file(&engine, filename, 0, NULL, NULL, sound) != MA_SUCCESS)
    {
        fprintf(stderr, "Falha ao carregar o som %s.\n", filename);
        exit(EXIT_FAILURE);
    }
}

// Atualiza o volume do som
void setVolume()
{
    // Muda o volume dos áudios
    ma_sound_set_volume(&audios[SHOT], volume * 0.05f);
    ma_sound_set_volume(&audios[RAIN], volume * 0.005f);
    ma_sound_set_volume(&audios[GAME_START], volume * 0.05f);
    ma_sound_set_volume(&audios[FALL], volume * 0.025f);
    ma_sound_set_volume(&audios[LOSE], volume * 0.05f);
    ma_sound_set_volume(&audios[DESTROY], volume * 0.04f);
    ma_sound_set_volume(&audios[OPENING], volume * 0.025f);
}

// Aumenta o Volume de todos os áudios
void upVolume()
{
    if (volume < 10)
    {
        volume++; // +10%

        // Atualiza o volume com o novo valor
        setVolume();
    }
}

// Diminui o Volume de todos os áudios
void downVolume()
{
    if (volume > 0)
    {
        volume--; // -10%

        // Atualiza o volume com o novo valor
        setVolume();
    }
}

// Inicializa os áudios
void initAudios()
{
    // Inicia a engine de áudio e verifica se teve sucesso
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS)
    {
        fprintf(stderr, "Falha ao inicializar o motor de audio.\n");
        exit(EXIT_FAILURE);
    }
    // Aloca espaço para todos os áudios
    audios = (ma_sound *)malloc(sizeof(ma_sound) * NUM_AUDIOS);
    if (!audios)
    {
        fprintf(stderr, "Erro ao inicializar os audios\n");
        exit(EXIT_FAILURE);
    }

    // Carrega todos os áudios usados no Jogo
    loadAudio(&audios[SHOT], "../assets/shot.mp3");
    loadAudio(&audios[RAIN], "../assets/rain.mp3");
    loadAudio(&audios[GAME_START], "../assets/start.mp3");
    loadAudio(&audios[FALL], "../assets/fall.mp3");
    loadAudio(&audios[LOSE], "../assets/lose.mp3");
    loadAudio(&audios[DESTROY], "../assets/destroy-mosquito.mp3");
    loadAudio(&audios[OPENING], "../assets/opening.mp3");

    // Define os áudios que ficaram em loop
    ma_sound_set_looping(&audios[RAIN], true);
    ma_sound_set_looping(&audios[OPENING], true);

    // Define o volume inicial
    setVolume();
}

// Libera os áudios
void freeAudios()
{
    for (int i = 0; i < NUM_AUDIOS; i++)
    {
        ma_sound_uninit(&audios[i]); // Libera cada áudio da memória
    }
    ma_engine_uninit(&engine); // Libera a engine de áudio
}

// Toca o som
void playSound(int audioID)
{
    ma_sound_start(&audios[audioID]);
}

// Desliga o som em loop
void stopSoundLoop(int audioID)
{
    // Verifica se é um áudio em loop
    if (ma_sound_is_looping(&audios[audioID]))
    {
        // Desliga o áudio
        ma_sound_stop(&audios[audioID]);
    }
}