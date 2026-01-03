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

typedef struct {
    InputMethod input;
    Theme theme;
} Settings;

extern Settings settings;

void loadSettings(Settings* settings, const char* filename);
void saveSettings(Settings* settings, const char* filename);

#endif