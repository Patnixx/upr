#include "../include/audio.h"

//params
Mix_Music* theme = NULL;
Mix_Chunk* lineSound = NULL;
Mix_Chunk* gameOverSound = NULL;

/**
 * @brief Inicializuje audio súbory
 * @return true, ak sa podarilo inicializovať audio
 * @return false ak nie
 */

bool initAudio(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }

    theme = Mix_LoadMUS("assets/audio/theme.mp3");
    lineSound = Mix_LoadWAV("assets/audio/line.mp3");
    gameOverSound = Mix_LoadWAV("assets/audio/gameover.mp3");

    return true;
}

/**
 * @brief Prehrá hudbu v pozadí mimo hru * 
 */
void playTheme(void) {
    if (theme != NULL) {
        Mix_PlayMusic(theme, -1);
    }
}

/** 
 * @brief Prehrá zvuk pri zlikvidovaní riadku
*/
void playLineSound(void) {
    if (lineSound != NULL) {
        Mix_PlayChannel(-1, lineSound, 0);
    }
}
/** 
 * @brief Prehrá zvuk pri konci hry
*/
void playGameOverSound(void) {
    stopTheme();

    if (gameOverSound != NULL) {
        Mix_PlayChannel(-1, gameOverSound, 0);
    }
}


/**
 * @brief Zastaví hudbu v pozadí
*/
void stopTheme(void) {
    Mix_HaltMusic();
}

/**
 * @brief Uvoľní audio súbory z pamäte
*/
void cleanUpAudio(void) {
    if (theme != NULL) {
        Mix_FreeMusic(theme);
        theme = NULL;
    }
    if (lineSound != NULL) {
        Mix_FreeChunk(lineSound);
        lineSound = NULL;
    }
    if (gameOverSound != NULL) {
        Mix_FreeChunk(gameOverSound);
        gameOverSound = NULL;
    }
    Mix_CloseAudio();
}