#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

bool initAudio(void);
void playTheme(void);
void playLineSound(void);
void playGameOverSound(void);
void cleanUpAudio(void);
void stopTheme(void);

#endif