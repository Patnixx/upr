#ifndef SETTINGS_H
#define SETTINGS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

typedef enum {
    ARROWS,
    WASD
} InputMethod;

typedef enum {
    DARK,
    LIGHT
} Theme;

typedef enum {
    SOUND_ON,
    SOUND_OFF
} SoundSetting;

typedef struct {
    InputMethod input;
    Theme theme;
    SoundSetting sound;
} Settings;

extern Settings settings;

void loadSettings(Settings* settings, const char* filename);
void saveSettings(Settings* settings, const char* filename);

#endif